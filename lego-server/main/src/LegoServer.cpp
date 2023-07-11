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
FigureSslServer* sslServerPtr = nullptr;
ProtocolServer* protocolServerPtr = nullptr;

void signalAction(int signum);

void signalHandle();

int main(int argc, char* argv[]) {
  Logger::initialize();

  if (argc < 2) {
    Logger::error("Missing certificate path.");
    exit(1);
  }

  string certPath{argv[1]};

  try {
    FigureHtmlRepository figureHtmlRepository{};

    FigureSslServer sslServer{8, certPath, PIECES_TCP_PORT,
                              figureHtmlRepository};

    FigureProtocolController figureProtocolController{figureHtmlRepository};

    ProtocolServer protocolServer{PIECES_UDP_PORT, figureProtocolController};

    // Set the global pointers to point to the server instances
    sslServerPtr = &sslServer;
    protocolServerPtr = &protocolServer;

    figureProtocolController.presentBcast();

    signalHandle();

    protocolServer.start();
    sleep(1);
    sslServer.start();
  } catch (exception const& e) {
    Logger::error("Server has crashed.", e);
    exit(1);
  }
}

void signalAction(int signum) {
  Logger::info("Exiting.");

  // Clean up the servers before exiting
  if (sslServerPtr != nullptr) {
    sslServerPtr->stop();
  }
  if (protocolServerPtr != nullptr) {
    protocolServerPtr->stop();
  }

  exit(signum);
}

void signalHandle() {
  signal(SIGINT, signalAction);
  signal(SIGTERM, signalAction);
}
