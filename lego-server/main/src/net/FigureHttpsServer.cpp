// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/FigureHttpsServer.hpp"

using ::Worker;

using std::exception;
using std::istringstream;
using std::map;
using std::regex;
using std::runtime_error;
using std::smatch;
using std::sregex_iterator;
using std::string;
using std::to_string;

FigureHttpsServer::~FigureHttpsServer() { stop(); }

/**
 * @brief Starts the listener, creates the threads and starts them running.
 * Besides accepts incoming connections and puts them in the client queue.
 */
void FigureHttpsServer::start() {
  listener.bind(PORT);

  listener.listen(QUEUE);

  for (int i{0}; i < 4; ++i) {
    this->workers.emplace_back(&FigureHttpsServer::handleRequests, this);
  }

  Logger::info("Listener certificates: \n" + listener.getCerts());

  Logger::info("Listening...");

  while (true) {
    this->clientQueue.enqueue(listener.accept());
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
    } else {
      client->sslAccept();

      Logger::info(client->getCerts());

      string request{client->sslRead()};

      // parseHttpRequest for all bits of request
      map<string, map<string, string>> parsedRequest{parseHttpRequest(request)};
      map<string, string> headers{parsedRequest["Headers"]};
      // isolate url, getLastPath, pass to getFigureByName
      string url{parsedRequest["Request-Line"]["URL"]};
      // isolate headers, pass to sendHttpResponse
      string last = getLastPath(url);
      string figure{};
      std::regex pattern("figure=([^&]+)");
      std::smatch match;
      if (std::regex_search(last, match, pattern)) {
        figure = match[1];
      }
      string body{figureController.getFigureByName(figure)};

      if (body.empty()) {
        sendHttpResponse(client, 404, headers, body);
      } else {
        sendHttpResponse(client, 200, headers, body);
      }
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
  while (getline(stream, line) && line != "\r") {
    auto colonPos = line.find(':');
    if (colonPos != string::npos) {
      string name = line.substr(0, colonPos);
      string value =
          line.substr(colonPos + 2);  // Skip the colon and the space after it
      headers[name] =
          value.substr(0, value.size() - 1);  // Remove the trailing '\r'
    }
  }
  return headers;
}

string FigureHttpsServer::getLastPath(const string &url) {
  size_t pos = url.find_last_of('/');
  if (pos != string::npos) {
    return url.substr(pos + 1);  // Return the part after the last '/'
  }
  return url;  // Return the whole URL if there is no '/'
}

string FigureHttpsServer::generateHttpResponse(
    int statusCode, const map<string, string> &headers, const string &body) {
  string statusMessage;
  switch (statusCode) {
    case 200:
      statusMessage = "OK";
      break;
    case 404:
      statusMessage = "Not Found";
      break;
    default:
      statusMessage = "Unknown";
      break;
  }

  string response =
      "HTTP/1.1 " + to_string(statusCode) + " " + statusMessage + "\r\n";
  for (const auto &header : headers) {
    response += header.first + ": " + header.second + "\r\n";
  }
  response += "Content-Length: " + to_string(body.size()) + "\r\n";
  response += "\r\n" + body;

  return response;
}

void FigureHttpsServer::sendHttpResponse(
    const std::shared_ptr<IPv4SslSocket> &client, int statusCode,
    const std::map<std::string, std::string> &headers,
    const std::string &body) {
  string response =
      FigureHttpsServer::generateHttpResponse(statusCode, headers, body);
  client->sslWrite(response);
}
