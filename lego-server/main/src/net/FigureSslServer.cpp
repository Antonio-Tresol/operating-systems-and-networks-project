#include <regex>
#include <stdexcept>

#include "../include/net/FigureSslServer.hpp"
#include "./logging/Logger.hpp"

using std::exception;
using std::regex;
using std::string;
using std::to_string;

FigureSslServer::FigureSslServer(int32_t numWorkers, const std::string &certPath, int32_t port,
                                 FigureHtmlRepository &figureHtmlRepository) :
        SslServer(numWorkers, certPath, port), figureSslController(figureHtmlRepository) {}

void FigureSslServer::handleClient(const std::shared_ptr<IPv4SslSocket> &client, int worker_pos) {
    string request{client->sslRead()};

    Logger::info("SslServer: Received request on worker " + std::to_string(worker_pos));

    try {
        // check if the request is valid
        if (!validateRequest(request)) {
            Logger::info("SslServer: Client request: " + request);
            Logger::info("SslServer: Sending emtpy response to client (caused by invalid URL Format): "
                         + to_string(client->getSocketFD()));
            client->sslWrite("");
            return;
        }

        client->sslWrite(figureSslController.getFigureByName(request));
    } catch (exception &e) {
        Logger::error("SslServer: Client error: ", e);
        Logger::error("SslServer: Dropping client");
    }
    Logger::info("SslServer: Handled connection with socket: " + to_string(client->getSocketFD()));
}

bool FigureSslServer::validateRequest(const string &request) {
    regex requestFormat{R"(w+$)"};
    return std::regex_match(request, requestFormat);
}