// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.
#include <csignal>
#include <string>

#include "../include/common/Logger.hpp"
#include "../include/net/FigureHttpsServer.hpp"

using std::exception;
using std::invalid_argument;
using std::out_of_range;
using std::stoi;
using std::string;

void signalAction(int signum);
void signalHandle();
FigureHttpsServer *serverPtr = nullptr;
/**
 * @brief Entry point.
 */
int main(int argc, char *argv[]) {
  Logger::initialize();
  try {
    FigureHttpsServer server("certificates");
    serverPtr = &server;
    signalHandle();
    server.start();
  } catch (exception const &e) {
    Logger::error("Server has crashed.", e);
    exit(1);
  }
  Logger::info("Exiting.");

  exit(0);
}

void signalAction(int signum) {
  if (serverPtr != nullptr) {
    serverPtr->stop();
  }
  exit(signum);
}

void signalHandle() {
  std::signal(SIGINT, signalAction);
  std::signal(SIGTERM, signalAction);
}