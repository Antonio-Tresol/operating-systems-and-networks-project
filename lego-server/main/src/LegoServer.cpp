// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include <csignal>
#include <string>

#include "./logging/Logger.hpp"
#include "./net/FigureSslServer.hpp"
#include "./net/ProtocolHeader.hpp"
#include "controller/FigureProtocolController.hpp"
#include "net/ProtocolServer.hpp"

using std::exception;
using std::invalid_argument;
using std::out_of_range;
using std::signal;
using std::stoi;
using std::string;

// Define global pointers to the servers so they can be accessed from the signal
// handler
FigureSslServer *sslServer = nullptr;
FigureProtocolController *figureProtocolController = nullptr;
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
        FigureHtmlRepository figureHtmlRepository{};

        sslServer = new FigureSslServer{8, certPath, PIECES_TCP_PORT,
                                  figureHtmlRepository};

        figureProtocolController = new FigureProtocolController{figureHtmlRepository};

        protocolServer = new ProtocolServer{PIECES_UDP_PORT, *figureProtocolController};

        figureProtocolController->presentBcast();

        signalHandle();

        protocolServer->start();
        sleep(1);
        sslServer->start();
    } catch (exception const &e) {
        Logger::error("Server has crashed.", e);
        exit(1);
    }
}

void signalAction(int signum) {
    // Clean up the servers before exiting
    delete sslServer;

    delete protocolServer;

    delete figureProtocolController;

    Logger::info("Exiting.");

    exit(signum);
}

void signalHandle() {
    signal(SIGINT, signalAction);
    signal(SIGTERM, signalAction);
}
