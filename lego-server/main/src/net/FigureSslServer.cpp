#include "../include/net/FigureSslServer.hpp"

#include <regex>
#include <stdexcept>

#include "./logging/Logger.hpp"

using std::exception;
using std::regex;
using std::string;
using std::to_string;

FigureSslServer::FigureSslServer(int32_t numWorkers,
                                 const std::string &certPath, int32_t port,
                                 FigureHtmlRepository &figureHtmlRepository)
    : SslServer(numWorkers, certPath, port),
      figureSslController(figureHtmlRepository) {}

void FigureSslServer::handleClient(const std::shared_ptr<IPv4SslSocket> &client) {
  string request{client->sslRead()};
  Logger::info("SslServer: Received request on socket " +
               std::to_string(client->getSocketFD()));

  try {
    // check if the request is valid
    if (!validateRequest(request)) {
      Logger::info("SslServer: Client request: " + request);
      Logger::info(
          "SslServer: Sending empty response to client (caused by invalid URL "
          "Format) on socket " +
          to_string(client->getSocketFD()));
      client->sslWrite("");
      return;
    }

    client->sslWrite(figureSslController.getFigureByName(request.substr(2)));
  } catch (exception &e) {
    Logger::error("SslServer: Client error: ", e);
    Logger::error("SslServer: Dropping client");
  }
  Logger::info("SslServer: Handled connection on socket " +
               std::to_string(client->getSocketFD()));
}

bool FigureSslServer::validateRequest(const string &request) {
  regex requestFormat{R"(\d\x1D\w+)"};
  return std::regex_match(request, requestFormat);
}