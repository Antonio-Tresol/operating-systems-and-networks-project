// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/HttpsServer.hpp"

using std::exception;
using std::runtime_error;
using std::string;
using ::Handler;

HttpsServer::HttpsServer() {
  // alistar el socket (listen)
}

void accept() {
  // bucle:
  // recibe request
  // descompone el string del request
  // revisa su validez
  // llama handleRequest(path, method)
}

void addRoute(const std::string& path, const std::string& method, Handler handler) {
  routes[std::make_tuple(path, method)] = handler;
}

void handleRequest(const std::string& path, const std::string& method) {
  auto key = std::make_tuple(path, method);
  if (routes.find(key) != routes.end()) {
    routes[key](method + " " + path);
  } else {
    std::cout << "404 Not Found" << std::endl;
  }

  // thread nuevo(handler, arg, returnAddr???)
  // {otro metodo}
  //    socketNuevo
  //    res = handler(arg)
  //    resp = buildResp(res)
  //    socketNuevo(returnAddr, resp)
  //    socketNuevo.close
}

std::string generateHttpResponse(int statusCode, const std::map<std::string, std::string>& headers, const std::string& body) {
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

  std::string response = "HTTP/1.1 " + std::to_string(statusCode) + " " + statusMessage + "\r\n";
  for (const auto& header : headers) {
    response += header.first + ": " + header.second + "\r\n";
  }
  response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
  response += "\r\n" + body;

  return response;
}

void sendHttpResponse(SSL* ssl, int statusCode, const std::map<std::string, std::string>& headers, const std::string& body) {
  std::string response = generateHttpResponse(statusCode, headers, body);
  SSL_write(ssl, response.c_str(), response.size());
}
