//
// Created by ariel on 6/24/23.
//

#include "../../include/net/SslServer.hpp"
#include "./logging/Logger.hpp"
#include "net/ProtocolHeader.hpp"

#include <algorithm>
#include <exception>
#include <string>

#include "./logging/Logger.hpp"

using std::exception;
using std::string;
using std::to_string;

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
    this->workers.emplace_back(&SslServer::handleRequests, this, i);
  }

  Logger::info("SslServer: Listener certificates: \n" + listener.getCerts());

  try {
        Logger::info("SslServer: Listening at " + getCurrentIP());
    } catch (std::runtime_error &e) {
        Logger::error("Could not find valid self IP: ", e);
        stop();
        exit(1);
    }

  while (true) {
    try {
      auto client{listener.accept()};
      Logger::info("SslServer: Accepted connection");
      this->clientQueue.enqueue(client);
    } catch (exception &e) {
      Logger::error("SslServer: Listener error: ", e);
    }
  }
}

void SslServer::stop() {
  for (auto &worker : workers) {
    clientQueue.enqueue(nullptr);
  }

  for (auto &handler : workers) {
    handler.join();
  }
  Logger::info("SslServer: Stopped.");
}

void SslServer::handleRequests(int worker_pos) {
  while (true) {
    auto client{clientQueue.dequeue()};
    if (!client) {
      break;
    }
    try {
      client->sslAccept();
    } catch (exception &e) {
      Logger::error("SslServer: Client error: ", e);
      Logger::error("SslServer: Dropping client");
      continue;
    }
    handleClient(client);
  }
}

std::string SslServer::getCurrentIP() {
  std::string command = "hostname -I";
  std::string ips = "";
  // Open pipe for reading output of command (hostname -I)
  FILE *pipe = popen(command.c_str(), "r");
  if (pipe) {
    char buffer[128];
    while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != nullptr) {
        ips += buffer;
      }
    }
    pclose(pipe);
  }
  // Erase any newline characters from the ips
  ips.erase(std::remove(ips.begin(), ips.end(), '\n'), ips.end());
  ips.erase(std::remove(ips.begin(), ips.end(), '\r'), ips.end());

  std::istringstream iss(ips);
    std::string output;

    //std::getline(iss, output, ' ');

    std::vector<std::string> addresses;

    for(std::string s; iss >> s; )
        addresses.push_back(s);

  for (const auto& address : addresses) {
        std::istringstream isss(address);
        std::string segment1;
        std::string segment2;
        std::getline(isss, segment1, '.');
        std::getline(isss, segment2, '.');
//        if (segment1 == BROADCAST_FIRST && segment2 == BROADCAST_SECOND) {
//            return address;
//        }
        return address;
    }

    throw std::runtime_error("No IP found with the initial segments: " + std::string{BROADCAST_FIRST} + "." + std::string{BROADCAST_SECOND});
}
