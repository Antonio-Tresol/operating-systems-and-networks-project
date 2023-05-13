// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/FigureHttpsServer.hpp"

using ::Handler;
using std::exception;
using std::runtime_error;
using std::string;

FigureHttpsServer::FigureHttpsServer(std::string certificatesFilePath,
  int port = 7777) {
  this->server = new Socket('s', port, certificatesFilePath, certificatesFilePath); 
}

/**
 * @brief Starts the server, creates the threads and starts them running. Besides
 * accepts incoming connections and puts them in the client queue.
 */
void FigureHttpsServer::start() {

  for (auto& handler : handlers) {
    this->handlers.push_back(Handler(&FigureHttpsServer::handleRequests, this));
  }

  while (true) {
    // add new client to queue
    this->clientQueue.enqueue(server->Accept());
  }
}

/**
 * @brief Stops the server, closes the socket and threads.
 * @details send a nullptr to the client queue so that the threads are
 * stop and join the threads
 */
void FigureHttpsServer::stop() {
  for (auto& handler : handlers) { // for each handler thread
    clientQueue.enqueue(nullptr); // send nullptr to stop them
  }
  for (auto& handler : handlers) {
    handler.join(); // wait for them to finish
  }
}

void FigureHttpsServer::handleRequests() {

  while (true) {
    Socket* client = clientQueue.dequeue();
    if (client == nullptr) {
      break;
    } else {
      client->SSLCreate(this->server);
      client->SSLAccept();
      string request = client->SSLRead();
      
      /*
      # Revisa el metodo (GET, POST, PUT, DELETE)
      # Revisa que 'tipo' de path es ("/*")
      # dado que hay que extraer un parametro, lo hace
      */
      std::map<string, string> params = getUrlParams(request);

      string body = figureController.getFigureByName(params["figure"]);
      
      if (body.empty()) {
        sendHttpResponse(client, 404, params, body);
      } else {
        sendHttpResponse(client, 200, params, body); 
      }
      client->Close();
    }
  }
}

std::map<std::string, std::string> FigureHttpsServer::getUrlParams(
    const std::string& httpRequest) {
  std::map<std::string, std::string> params;
  std::regex urlParamRegex("GET\\s.+\\?(.+)\\sHTTP\\/1\\.1");
  std::smatch urlParamMatch;

  if (std::regex_search(httpRequest, urlParamMatch, urlParamRegex) &&
      urlParamMatch.size() > 1) {
    std::string paramString = urlParamMatch.str(1);
    std::regex paramRegex("([^=&]+)=([^&]+)");
    std::sregex_iterator paramIter(paramString.begin(), paramString.end(),
                                   paramRegex);
    std::sregex_iterator paramEnd;

    while (paramIter != paramEnd) {
      std::smatch match = *paramIter;
      params[match.str(1)] = match.str(2);
      ++paramIter;
    }
  }

  return params;
}

std::string FigureHttpsServer::generateHttpResponse(
    int statusCode, const std::map<std::string, std::string>& headers,
    const std::string& body) {
  std::string statusMessage;
  switch (statusCode) {
    case 200:
      statusMessage = "OK";
      break;
    case 404:
      statusMessage = "Not Found";
      break;
      // Add other status codes and messages as needed
    default:
      statusMessage = "Unknown";
  }

  std::string response =
      "HTTP/1.1 " + std::to_string(statusCode) + " " + statusMessage + "\r\n";
  for (const auto& header : headers) {
    response += header.first + ": " + header.second + "\r\n";
  }
  response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
  response += "\r\n" + body;

  return response;
}

void FigureHttpsServer::sendHttpResponse(
    Socket* client, int statusCode,
    const std::map<std::string, std::string>& headers,
    const std::string& body) {
  std::string response =
      FigureHttpsServer::generateHttpResponse(statusCode, headers, body);
  client->SSLWrite(response);
}
