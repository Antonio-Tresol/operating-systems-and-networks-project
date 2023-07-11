// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include <csignal>
#include <string>

#include "./controller/ProxyProtocolController.hpp"
#include "./logging/Logger.hpp"
#include "./net/ProtocolServer.hpp"
#include "./net/ProxyHttpsServer.hpp"

using std::exception;
using std::invalid_argument;
using std::out_of_range;
using std::signal;
using std::stoi;
using std::string;

// Declare global pointers to the servers
ProxyHttpsServer *httpsServer = nullptr;
ProtocolServer *protocolServer = nullptr;

void signalAction(int signum);

void signalHandle();

int main(int argc, char *argv[]) {
    Logger::initialize();

    if (argc < 2) {
        Logger::error("Missing certificate path.");
        exit(1);
    }

    string certPath{argv[1]};

    try {
        httpsServer = new ProxyHttpsServer{2, certPath, 7777};

        ProxyProtocolController proxyProtocolController{};

        protocolServer = new ProtocolServer{INTERMEDIARY_UDP_PORT,
                                      proxyProtocolController};

        proxyProtocolController.discover();

        signalHandle();

        protocolServer->start();
        sleep(1);
        httpsServer->start();
    } catch (exception const &e) {
        Logger::error("Server has crashed.", e);
        exit(1);
    }
}

void signalAction(int signum) {
    delete httpsServer;

    delete protocolServer;

    Logger::info("Exiting.");

    exit(signum);
}

void signalHandle() {
    signal(SIGINT, signalAction);
    signal(SIGTERM, signalAction);
}
