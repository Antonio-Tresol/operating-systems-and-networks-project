#include "../../include/controller/ProxyHttpsController.hpp"
#include <regex>
#include <utility>

using std::exception;
using std::invalid_argument;
using std::istringstream;
using std::map;
using std::regex;
using std::regex_match;
using std::regex_search;
using std::runtime_error;
using std::shared_ptr;
using std::smatch;
using std::sregex_iterator;
using std::string;
using std::to_string;
using std::vector;
using Row = std::pair<std::string, int>;  // description, amount


// Client interaction
map<string, map<string, string>> ProxyHttpsController::parseHttpRequest(
    const string &request) {
  istringstream requestStream(request);
  string method, url, version;
  requestStream >> method >> url >> version;

  map<string, map<string, string>> result{
      {"Request-Line",
       {{"Method", method}, {"URL", url}, {"Version", version}}},
      {"Headers", parseHeaders(requestStream)}};

  return result;
}

map<string, string> ProxyHttpsController::parseHeaders(istringstream &stream) {
  map<string, string> headers;
  string line;
  while (getline(stream, line, '\n')) {  // Specify '\n' as the delimiter
    // Check if line is not just '\r'
    if (line.size() > 1) {
      // Remove the trailing '\r' if it exists
      if (line.back() == '\r') {
        line.pop_back();
      }
      auto colonPos = line.find(':');
      if (colonPos != string::npos) {
        string name = line.substr(0, colonPos);
        string value =
            line.substr(colonPos + 2);  // Skip the colon and the space after it
        headers[name] = value;
      }
    }
  }
  return headers;
}

bool ProxyHttpsController::validateUrlFormat(const string &url) {
  regex pathFormat{R"(/lego/\w+$)"};
  return std::regex_match(url, pathFormat);
}

string ProxyHttpsController::getLastPath(const string &url) {
  size_t pos = url.find_last_of('/');
  if (pos != string::npos) {
    return url.substr(pos + 1);  // Return the part after the last '/'
  }
  return url;  // Return the whole URL if there is no '/'
}

string ProxyHttpsController::generateHttpResponse(int statusCode,
                                               const string &body) {
  string statusMessage;
  switch (statusCode) {
    case 200:
      statusMessage = "OK";
      break;
    case 404:
      statusMessage = "Not Found";
      break;
    case 500:
      statusMessage = "Internal Error";
      break;
    default:
      throw invalid_argument("Unknown HTTP status code");
  }

  string response =
      "HTTP/1.1 " + to_string(statusCode) + " " + statusMessage + "\r\n";
  response += "Content-Type: text/html\r\n";
  response += "Content-Length: " + to_string(body.size()) + "\r\n";
  response += "Connection: close\r\n";
  response += "\r\n" + body;

  return response;
}

void ProxyHttpsController::sendHttpResponse(
    const shared_ptr<IPv4SslSocket> &client, int statusCode,
    const string &body) {
  string response = ProxyHttpsController::generateHttpResponse(statusCode, body);
  client->write(response);
}

void ProxyHttpsController::sendHttpsResponse(
    const shared_ptr<IPv4SslSocket> &client, int statusCode,
    const string &body) {
  string response = ProxyHttpsController::generateHttpResponse(statusCode, body);
  client->sslWrite(response);
}

void ProxyHttpsController::serveFigure(const shared_ptr<IPv4SslSocket> &client,
                                     const string &request) {
  try {
    // for a normal request: parse the request
    map<string, map<string, string>> parsedRequest{parseHttpRequest(request)};
    string url{parsedRequest["Request-Line"]["URL"]};
    // check if the url is valid
    if (!validateUrlFormat(url)) {
      Logger::info("Client request: \n" + request);
      Logger::info(
          "Sending 404 response to client (caused by invalid URL "
          "Format): " +
          to_string(client->getSocketFD()));
      sendHttpsResponse(client, 404, "");
      return;
    }
    // get the body of the figure
    //TODO CHECK:
    // string body{figureController.getFigureByName(getLastPath(url))};
    // prepare the headers
    string body{""};
    map<string, string> headers{parsedRequest["Headers"]};
    if (body.empty()) {  // if the body is empty, send a 404 response
      Logger::info("Client request: \n" + request);
      Logger::info(
          "Sending 404 response to client (caused by FigureNotFound): " +
          to_string(client->getSocketFD()));
      sendHttpsResponse(client, 404, body);
    } else {  // if the body is not empty, send the figure and 200 response
      Logger::info("Client request: \n" + request);
      Logger::info("Sending response to client: " +
                   to_string(client->getSocketFD()));
      sendHttpsResponse(client, 200, body);
    }
  } catch (exception &e) {
    Logger::error("Client error: ", e);
    Logger::error("Dropping client"); 
  }
  Logger::info("Handled connection with socket: " +
               to_string(client->getSocketFD()));
  return;
}