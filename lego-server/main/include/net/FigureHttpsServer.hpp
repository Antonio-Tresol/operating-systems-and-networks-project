// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <functional>
#include <map>
#include <regex>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../common/Queue.hpp"
#include "../controller/FigureController.hpp"
#include "./socket/IPv4SslSocket.hpp"

using Worker = std::thread;

/**
 * @brief Makes HTTP requests.
 */
class FigureHttpsServer {
public:
    ~FigureHttpsServer();

    [[noreturn]] void start();

    void stop();

private:
    static constexpr int PORT{7777};
    static constexpr int QUEUE{10};
    static constexpr char CERT_NAME[]{"ci0123.pem"};
    static constexpr char CERT_DIR[]{"."};
    static constexpr char FIGURE[]{"figure"};

    IPv4SslSocket listener{CERT_DIR, CERT_NAME};

    FigureController figureController{};

    Queue<std::shared_ptr<IPv4SslSocket>> clientQueue{};

    std::vector<Worker> workers{};

    void handleRequests();

    static std::map<std::string, std::string> getUrlParams(
            const std::string &httpRequest);

    static std::string generateHttpResponse(
            int statusCode, const std::map<std::string, std::string> &headers,
            const std::string &body);

    static void sendHttpResponse(const std::shared_ptr<IPv4SslSocket>& client, int statusCode,
                                 const std::map<std::string, std::string> &headers,
                                 const std::string &body);
};
