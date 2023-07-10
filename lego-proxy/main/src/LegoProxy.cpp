// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include <csignal>
#include <string>

#include "../../../lego-common/main/include/logging/Logger.hpp"
#include "../../../lego-common/main/include/net/ProtocolServer.hpp"
// #include "../include/controller/ProxyHttpsController.hpp"
#include "../include/controller/ProxyProtocolController.hpp"
#include "../include/controller/ProxyRoutingTable.hpp"
#include "../include/net/ProxyHttpsServer.hpp"
#include "../include/net/ProxySslClient.hpp"

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

  if (argc < 2) {
    Logger::error("Missing certificate path.");
    exit(1);
  }

  string certPath{argv[1]};

  try {
    ProxyRoutingTable *proxyRoutingTable = ProxyRoutingTable::getInstance();
    ProxyHttpsServer server{2, certPath, 7777, proxyRoutingTable};
    ProxyProtocolController* proxyProtocolController = new ProxyProtocolController{proxyRoutingTable};
    ProtocolServer protocolServer{INTERMEDIARY_UDP_PORT, *proxyProtocolController};
    protocolServer.start();
    server.start();

    signalHandle();
    // pass start to a new thread
    // server.start();
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