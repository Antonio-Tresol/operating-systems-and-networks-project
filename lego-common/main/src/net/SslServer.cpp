//
// Created by ariel on 6/24/23.
//

#include "../../include/net/SslServer.hpp"

#include <exception>
#include <string>

using std::exception;
using std::string;

SslServer::SslServer(int32_t numWorkers, const std::string &certPath,
                     int32_t port)
        : CERT_PATH{certPath},
          NUM_WORKERS{numWorkers},
          PORT{port},
          listener(certPath, certPath) {}

SslServer::~SslServer() { stop(); }

void SslServer::start() {
    listener.bind(PORT);
    listener.listen(QUEUE);

    for (int i{0}; i < NUM_WORKERS; ++i) {
        this->workers.emplace_back(&SslServer::handleRequests, this);
    }

    while (true) {
        try {
            auto client{listener.accept()};
            this->clientQueue.enqueue(client);
        } catch (exception &e) {
            // TODO(@Antonio): log message Could not accept incoming connection      
            continue;
        }
    }
}

void SslServer::stop() {
    for (auto &worker: workers) {
        clientQueue.enqueue(nullptr);
    }

    for (auto &handler: workers) {
        handler.join();
    }
}

void SslServer::handleRequests() {
    while (true) {
        auto client{clientQueue.dequeue()};
        if (!client) {
            break;
        }
        try {
            client->sslAccept();
        } catch (exception &e) {
            // TODO(@Antonio)Log error message could not make handshake
            continue;
        }
        handleClient(client);
    }
}
