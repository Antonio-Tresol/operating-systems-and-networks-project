// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/FigureHttpsServer.hpp"

#include <string>

using ::Worker;

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

FigureHttpsServer::FigureHttpsServer(const string &certPath)
    : listener(certPath, certPath) {}

FigureHttpsServer::~FigureHttpsServer() { stop(); }
/**
 * @brief Starts the listener, creates the threads and starts them running.
 * Besides accepts incoming connections and puts them in the client queue.
 */
void FigureHttpsServer::start() {
  listener.bind(PORT);

  listener.listen(QUEUE);

  for (int i{0}; i < NUM_WORKERS; ++i) {
    this->workers.emplace_back(&FigureHttpsServer::handleRequests, this);
  }

  Logger::info("Listener certificates: \n" + listener.getCerts());

  Logger::info("Listening.");

  while (true) {
    try {
      auto client{listener.accept()};
      Logger::info("Accepted connection with socket: " +
                   to_string(client->getSocketFD()));
      this->clientQueue.enqueue(client);
    } catch (exception &e) {
      Logger::error("Listener error: ", e);
    }
  }
}

/**
 * @brief Stops the listener, closes the socket and threads.
 * @details send a nullptr to the client queue so that the threads are
 * stop and join the threads
 */
void FigureHttpsServer::stop() {
  for (auto &worker : workers) {
    clientQueue.enqueue(nullptr);
  }

  for (auto &handler : workers) {
    handler.join();
  }
}

void FigureHttpsServer::handleRequests() {
  while (true) {
    auto client{clientQueue.dequeue()};
    if (!client) {
      break;
    }
    try {
      client->sslAccept();
    } catch (exception &e) {
      Logger::error("Client error: ", e);
      Logger::error("Dropping client");
      continue;
    }
    string request{client->sslRead()};
    // check if the request is a nachos request
    if (isNachos(request)) {
      Logger::info("Nachos Client request: \n" + request);
      Logger::info("Sending response to client: " +
                   to_string(client->getSocketFD()));
      serveNachos(client, request);
    } else {
      // if the request is not a nachos request, serve the figure as usual
      serveFigures(client, request);
    }
  }
}

map<string, map<string, string>> FigureHttpsServer::parseHttpRequest(
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

map<string, string> FigureHttpsServer::parseHeaders(istringstream &stream) {
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

bool FigureHttpsServer::validateUrlFormat(const string &url) {
  regex pathFormat{R"(/lego/\w+$)"};
  return std::regex_match(url, pathFormat);
}

string FigureHttpsServer::getLastPath(const string &url) {
  size_t pos = url.find_last_of('/');
  if (pos != string::npos) {
    return url.substr(pos + 1);  // Return the part after the last '/'
  }
  return url;  // Return the whole URL if there is no '/'
}

string FigureHttpsServer::generateHttpResponse(int statusCode,
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

void FigureHttpsServer::sendHttpResponse(
    const shared_ptr<IPv4SslSocket> &client, int statusCode,
    const string &body) {
  string response = FigureHttpsServer::generateHttpResponse(statusCode, body);
  client->write(response);
}

void FigureHttpsServer::sendHttpsResponse(
    const shared_ptr<IPv4SslSocket> &client, int statusCode,
    const string &body) {
  string response = FigureHttpsServer::generateHttpResponse(statusCode, body);
  client->sslWrite(response);
}

string FigureHttpsServer::formatForNachos(const string &html) {
  string::const_iterator searchStart(html.cbegin());
  string::const_iterator searchEnd(html.cend());
  smatch matchName;
  regex regName{"Nombre: ([A-Za-z]+)"};
  string name;
  if (regex_search(searchStart, searchEnd, matchName, regName)) {
    name = matchName[1];
  }
  smatch matchParts;
  regex regParts{
      "(?:brick|plate|flag|eyes|bracket|cone|slopes) "
      "(?:[0-9]x[0-9]|[0-9]x[0-9]-[0-9]x[0-9] )?(?:[a-z ]+)"};
  smatch matchAmount;
  regex regAmount{"[0-9]+(?=</TD>)"};
  vector<Row> inputParts;
  while (regex_search(searchStart, searchEnd, matchParts, regParts) &&
         regex_search(searchStart, searchEnd, matchAmount, regAmount)) {
    inputParts.emplace_back(matchParts[0], stoi(matchAmount[0]));
    searchStart = matchParts.suffix().first;
  }

  string upperCaseName{name};
  transform(upperCaseName.begin(), upperCaseName.end(), upperCaseName.begin(),
            ::toupper);

  string asString{upperCaseName + "\n"};

  int totalParts{0};
  for (vector<Row>::size_type elem{0}; elem < inputParts.size(); elem++) {
    asString += to_string(inputParts[elem].second);
    asString += " pieces of ";
    asString += inputParts[elem].first;
    // 3 pieces of LEGO
    asString += "\n";
    totalParts += inputParts[elem].second;
  }
  asString = asString + "Total amount of parts for " + name +
             " is: " + to_string(totalParts);

  return asString;
}

bool FigureHttpsServer::isNachos(const string &request) {
  regex nachos{"N-([A-Za-z]+)"};
  string::const_iterator searchStart(request.cbegin());
  string::const_iterator searchEnd(request.cend());
  smatch matchName;
  return regex_search(searchStart, searchEnd, matchName, nachos);
}

void FigureHttpsServer::serveNachos(const shared_ptr<IPv4SslSocket> &client,
                                    const string &request) {
  try {
    string::const_iterator searchStart(request.cbegin());
    string::const_iterator searchEnd(request.cend());
    smatch matchName;
    regex nachos{"N-([A-Za-z]+)"};
    if (regex_search(searchStart, searchEnd, matchName, nachos)) {
      string name{matchName[1]};
      string nachosBody{formatForNachos(figureController.getFigureByName(name))};
      if (nachosBody.empty()) {
        Logger::info("Client request: \n" + request);
        Logger::info(
            "Sending 404 response to Nachos client (figure not found): " +
            to_string(client->getSocketFD()));
        sendHttpsResponse(client, 404, "");
      } else {
        Logger::info("Client request: \n" + request);
        Logger::info("Sending 200 response to client: " +
                     to_string(client->getSocketFD()));
        sendHttpsResponse(client, 200, nachosBody);
      }
    } else {
      Logger::info("Client request: \n" + request);
      Logger::info(
          "Sending 404 response to Nachos client (caused by invalid URL "
          "Format): " +
          to_string(client->getSocketFD()));
      sendHttpsResponse(client, 404, "");
    }
  } catch (exception &e) {
    Logger::error("Client error: ", e);
    Logger::error("Dropping client");
  }
}

void FigureHttpsServer::serveFigures(const shared_ptr<IPv4SslSocket> &client,
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
    string body{figureController.getFigureByName(getLastPath(url))};
    // prepare the headers
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