// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../../include/net/ProtocolServer.hpp"
#include "../../include/net/ProtocolHeader.hpp"
#include <arpa/inet.h>

#define RESPOND_ERROR -2
#define THREAD_AMOUNT 7

// TODO: Agregar ProtocolController como dependencia
ProtocolServer::ProtocolServer(int port, ProtocolController &protocolController) : receiverSocket(port),
                                                                                   protocolController(
                                                                                           protocolController),
                                                                                   keepListeningFlag(true) {}

void ProtocolServer::keepListening() const {
    // Loop for listening (receiving)
    while (keepListeningFlag) {
        std::string message = this->receiverSocket.receive(); // TODO: port queue thread-safe?
        this->handleRequest(message);
    }
}

// Returns the message code. 
int ProtocolServer::validateMessage(std::string message) const {
    // - being the separator
    //0-host:port-figura-figura2...
    // Get the code of the message
    int code = atoi(&message[0]);

    if (!this->checkHost(message)) {
        return -1; // Can't send message back. Nothing is sent.
    }

    switch (code) {
        case LEGO_DISCOVER:
            return LEGO_DISCOVER;
        case LEGO_PRESENT:
            return LEGO_PRESENT;
        case LEGO_RELEASE:
            return LEGO_RELEASE;
        default: // message structure is ok, but code isn't valid.
            return RESPOND_ERROR; // -2
    }
}

void ProtocolServer::handleRequest(std::string message) const {
    // Calls analyzeMessage and depending on the response calls respond.
    int code = this->validateMessage(message);
    if (code == -1) {
        return;
    }

    // TODO: aaaaaaaaaaaaaaaaaaaa
    protocolController.handle(code, getIP(message), getBody(message));
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
    // TODO: check substring generation. De fijo bro (numero de char segundo arg)
    return message.substr(2, message.find(":") - 1);
}

std::string ProtocolServer::getBody(std::string message) const {
    // TODO: AAAAAAAAAAAAAAAAAAAAAAAa
    return std::string();
}


void ProtocolServer::start() {
    // Create 7 threads and call them to execute keepListening.
    for (int i{0}; i < THREAD_AMOUNT; i++) {
        this->workers.emplace_back(&ProtocolServer::keepListening, this);
    }
}

void ProtocolServer::stop() {
    this->keepListeningFlag = false;
    for (auto &worker: workers) {
        worker.join();
    }
}