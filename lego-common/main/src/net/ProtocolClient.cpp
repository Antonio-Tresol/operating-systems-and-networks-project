#include "../../include/net/ProtocolClient.hpp"
#include "../../include/net/ProtocolHeader.hpp"
#include <iostream>
#include <cstdlib>

ProtocolClient::ProtocolClient(int port) : port(port) {}

void ProtocolClient::discover(const std::string& broadcastAddr) {
  std::string code { static_cast<char>(LEGO_DISCOVER) };
  std::string sep { SEPARATOR };
  std::string message = code + sep + getCurrentIP() + ":" + std::to_string(port);
  // TODO: Send message to broadcast address
  // send(message, broadcastAddr);
}

void ProtocolClient::present(const std::string& ipAddress, const std::vector<std::string>& figures) {
  std::string code { static_cast<char>(LEGO_PRESENT) };
  std::string sep { SEPARATOR };
  std::string message = code + sep + getCurrentIP() + ":" + std::to_string(port) + sep;
  for (const std::string& figure : figures) {
    message += figure + sep;
  }
  // TODO: Send message to ipAddress or broadcast address
  // send(message, ipAddress);
}

void ProtocolClient::release(const std::string& broadcastAddr) {
  std::string code { static_cast<char>(LEGO_RELEASE) };
  std::string sep { SEPARATOR };
  std::string message = code + sep + getCurrentIP() + ":" + std::to_string(port);
  // TODO: Send message to broadcast address
  // send(message, broadcastAddr);
}

void ProtocolClient::errorMsg(const std::string& code, const std::string& ipAddress) {
  std::string sep { SEPARATOR };
  std::string message = code + sep + "NotFound";
  // TODO: Send message to ipAddress
  // send(message, ipAddress);
}

std::string ProtocolClient::getCurrentIP() {
  std::string command = "hostname -I";
  std::string result = "";
  // Open pipe for reading output of command (hostname -I)
  FILE* pipe = popen(command.c_str(), "r");
  if (pipe) {
    char buffer[128];
    while (!feof(pipe)) {
      if (fgets(buffer, 128, pipe) != nullptr) {
        result += buffer;
      }
    }
    pclose(pipe);
  }
  // Erase any newline characters from the result
  result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
  result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
  return result;
}

