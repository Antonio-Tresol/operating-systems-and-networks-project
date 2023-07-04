// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../../include/net/ProtocolClient.hpp"
#include "../../include/net/ProtocolHeader.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

ProtocolClient::ProtocolClient(int port) : port(port), protocolClientSocket(port) {
  this->protocolClientSocket.bind();
}

void ProtocolClient::discover(const std::string& broadcastAddr) {
  std::string code { static_cast<char>(LEGO_DISCOVER) };
  std::string sep { SEPARATOR };
  std::string message = code + sep + getCurrentIP() + ":" + std::to_string(port);
  this->protocolClientSocket.send(message, broadcastAddr);
}

void ProtocolClient::present(const std::string& ipAddress, const std::vector<std::string>& figures) {
  std::string code { static_cast<char>(LEGO_PRESENT) };
  std::string sep { SEPARATOR };
  std::string message = code + sep + getCurrentIP() + ":" + std::to_string(port) + sep;
  for (const std::string& figure : figures) {
    message += figure + sep;
  }
  this->protocolClientSocket.send(message, ipAddress);
}

void ProtocolClient::release(const std::string& broadcastAddr) {
  std::string code { static_cast<char>(LEGO_RELEASE) };
  std::string sep { SEPARATOR };
  std::string message = code + sep + getCurrentIP() + ":" + std::to_string(port);
  this->protocolClientSocket.send(message, broadcastAddr);
}

void ProtocolClient::errorMsg(const std::string& code, const std::string& ipAddress) {
  std::string sep { SEPARATOR };
  std::string message = code + sep + "NotFound";
  this->protocolClientSocket.send(message, ipAddress);
}

std::string ProtocolClient::getCurrentIP() {
  std::string command = "hostname -I";
  std::string ip = "";
  // Open pipe for reading output of command (hostname -I)
  FILE* pipe = popen(command.c_str(), "r");
  if (pipe) {
    char buffer[128];
    while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != nullptr) {
        ip += buffer;
      }
    }
    pclose(pipe);
  }
  // Erase any newline characters from the ip
  ip.erase(std::remove(ip.begin(), ip.end(), '\n'), ip.end());
  ip.erase(std::remove(ip.begin(), ip.end(), '\r'), ip.end());
  return ip;
}

