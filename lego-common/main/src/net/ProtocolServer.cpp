// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../../include/net/ProtocolServer.hpp"

#include <arpa/inet.h>

#include "logging/Logger.hpp"
#include "net/Timeout.hpp"

#define RESPOND_ERROR -2
#define THREAD_AMOUNT 7

ProtocolServer::ProtocolServer(int port, ProtocolController &protocolController)
        : receiverSocket(port),
          protocolController(protocolController),
          keepListeningFlag(true) {
    receiverSocket.bind();
}

ProtocolServer::~ProtocolServer() { stop(); }

void ProtocolServer::keepListening(int worker_pos) const {
    // Loop for listening (receiving)
    while (keepListeningFlag) {
        try {
            std::string message = this->receiverSocket.receive();
            Logger::info("ProtocolServer: Received message on worker " +
                         std::to_string(worker_pos));
            this->handleRequest(message, worker_pos);
        } catch(const Timeout &t) {
            continue;
        } catch (const std::runtime_error &e) {
//            Logger::error("ProtocolServer: Error receiving message on worker " +
//                         std::to_string(worker_pos));
            continue;
        }
    }
}

// Returns the message code.
int ProtocolServer::validateMessage(std::string message) const {
    // - being the separator
    // 0-host:port-figura-figura2...
    if (message.size() < 2) {
        return -1;
    }

    // Get the code of the message
    int code = atoi(&message[0]);

    if (!this->checkHost(message)) {
        return -1;  // Can't send message back. Nothing is sent.
    }

    switch (code) {
        case LEGO_DISCOVER:
            return LEGO_DISCOVER;
        case LEGO_PRESENT:
            return LEGO_PRESENT;
        case LEGO_RELEASE:
            return LEGO_RELEASE;
        default:                 // message structure is ok, but code isn't valid.
            return RESPOND_ERROR;  // -2
    }
}

void ProtocolServer::handleRequest(std::string message, int worker_pos) const {
    // Calls analyzeMessage and depending on the response calls respond.
    int code = this->validateMessage(message);
    if (code == -1) {
        Logger::info("ProtocolServer: Invalid message on worker " +
                     std::to_string(worker_pos));
        return;
    }

    std::string messageType{getLegoMessageCodeName(code)};

    Logger::info("ProtocolServer: Handling " + messageType + " on worker " +
                 std::to_string(worker_pos));

    protocolController.handle(code, getIP(message), message);
}

bool ProtocolServer::checkHost(std::string message) const {
    // First character doesn't matter anymore.
    bool st;
    st = (message[1] == SEPARATOR);
    // Get the IP address of the message
    struct sockaddr_in sa;
    std::string strIP = this->getIP(message);
    int validIP = inet_pton(AF_INET, strIP.c_str(), &(sa.sin_addr));
    return validIP && st;
}

// ! Assumes that the message has the right format.
std::string ProtocolServer::getIP(std::string message) const {
    // First character doesn't matter anymore.
    std::string::size_type pos = message.find(":");
    if (pos != std::string::npos) {
        message = message.substr(0, pos);
    }
    return message.substr(2);
}

void ProtocolServer::start() {
    // Create 7 threads and call them to execute keepListening.
    for (int i{0}; i < THREAD_AMOUNT; i++) {
        this->workers.emplace_back(&ProtocolServer::keepListening, this, i);
    }
    Logger::info("ProtocolServer: Listening");
}

void ProtocolServer::stop() {
    this->keepListeningFlag = false;
    for (auto &worker: workers) {
        worker.join();
    }
    Logger::info("ProtocolServer: Stopped");
}
