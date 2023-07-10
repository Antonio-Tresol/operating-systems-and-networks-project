#include <regex>
#include <stdexcept>

#include "../include/net/FigureSslServer.hpp"
#include "./logging/Logger.hpp"

using std::exception;
using std::regex;
using std::string;
using std::to_string;

void FigureSslServer::handleClient(const std::shared_ptr<IPv4SslSocket> &client) {
    string request{client->sslRead()};

    try {
        // check if the request is valid
        if (!validateRequest(request)) {
            Logger::info("Client request: \n" + request);
            Logger::info("Sending emtpy response to client (caused by invalid URL Format): "
            + to_string(client->getSocketFD()));
            client->sslWrite("");
            return;
        }

        client->sslWrite(figureSslController.getFigureByName(request));
    } catch (exception &e) {
        Logger::error("Client error: ", e);
        Logger::error("Dropping client");
    }
    Logger::info("Handled connection with socket: " + to_string(client->getSocketFD()));
}

bool FigureSslServer::validateRequest(const string &request) {
    regex requestFormat{R"(w+$)"};
    return std::regex_match(request, requestFormat);
}