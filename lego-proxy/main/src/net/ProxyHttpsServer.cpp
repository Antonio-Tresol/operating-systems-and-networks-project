#include "../../include/net/ProxyHttpsServer.hpp"
using std::string;

void ProxyHttpsServer::handleClient(const std::shared_ptr<IPv4SslSocket>& client) {
  try {
    string request{client->sslRead()};
    Logger::info("Received request: " + request);
    proxyHttpsController.serveFigure(client, request);
  } catch (const std::exception& e) {
    Logger::error("Error reading from client: " + string{e.what()});
  }
}

void ProxyHttpsServer::handleAcceptError(const std::exception& e) {
  Logger::error("Error accepting client: " + string{e.what()});
}