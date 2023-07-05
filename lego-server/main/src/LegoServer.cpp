// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include <csignal>
#include <string>

#include "./logging/Logger.hpp"
#include "./net/FigureHttpsServer.hpp"

using std::exception;
using std::invalid_argument;
using std::out_of_range;
using std::signal;
using std::stoi;
using std::string;

void signalAction(int signum);

void signalHandle();

/**
 * @brief Entry point.
 */
int main(int argc, char *argv[]) {
    Logger::initialize();

    if(argc < 2) {
      Logger::error("Missing certificate path.");
      exit(1);
    }

    string certPath{argv[1]};

    try {
        FigureHttpsServer server{certPath};

        signalHandle();

        server.start();
    } catch (exception const &e) {
        Logger::error("Server has crashed.", e);
        exit(1);
    }
}

void signalAction(int signum) {
    Logger::info("Exiting.");

    exit(signum);
}

void signalHandle() {
    signal(SIGINT, signalAction);
    signal(SIGTERM, signalAction);
}