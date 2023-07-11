// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "./net/ProtocolClient.hpp"
#include "./net/ProtocolHeader.hpp"
#include "logging/Logger.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

ProtocolClient::ProtocolClient(int port) : port(port), protocolClientSocket(port) {}

void ProtocolClient::discover() {
    Logger::info("ProtocolClient: Sending " + getLegoMessageCodeName(LEGO_DISCOVER));

    std::string code{std::to_string(static_cast<int>(LEGO_DISCOVER))};
    std::string message = code + SEPARATOR + this->getCurrentIP() + ":" + std::to_string(port);

    for (int i{0}; i < 7; ++i) {
        int broadcastAddrSuffix{BROADCAST_ADDR_START + BROADCAST_ADDR_INCREMENT * i};
        std::string broadcastAddr{BROADCAST_ADDR_PREFIX + std::to_string(broadcastAddrSuffix)};

        this->protocolClientSocket.send(message, broadcastAddr);
    }

    this->protocolClientSocket.send(message, "255.255.255.255");
}

void ProtocolClient::presentBcast(const std::vector<std::string> &figures) {
    Logger::info("ProtocolClient: Sending " + getLegoMessageCodeName(LEGO_PRESENT));
    for (int i{0}; i < 7; ++i) {
        int broadcastAddrSuffix{BROADCAST_ADDR_START + BROADCAST_ADDR_INCREMENT * i};
        std::string broadcastAddr{BROADCAST_ADDR_PREFIX + std::to_string(broadcastAddrSuffix)};

        present(broadcastAddr, figures);
    }

    present("255.255.255.255", figures);
}

void ProtocolClient::present(const std::string &ipAddress, const std::vector<std::string> &figures) {
    std::string code{std::to_string(static_cast<int>(LEGO_PRESENT))};
    std::string message = code + SEPARATOR + this->getCurrentIP() + ":" + std::to_string(port);
    for (const std::string &figure: figures) {
        message += SEPARATOR + figure;
    }
    this->protocolClientSocket.send(message, ipAddress);
}

void ProtocolClient::release() {
    Logger::info("ProtocolClient: Sending " + getLegoMessageCodeName(LEGO_RELEASE));
    std::string code{std::to_string(static_cast<int>(LEGO_RELEASE))};
    std::string message = code + SEPARATOR + this->getCurrentIP() + ":" + std::to_string(port);

    for (int i{0}; i < 7; ++i) {
        int broadcastAddrSuffix{BROADCAST_ADDR_START + BROADCAST_ADDR_INCREMENT * i};
        std::string broadcastAddr{BROADCAST_ADDR_PREFIX + std::to_string(broadcastAddrSuffix)};

        this->protocolClientSocket.send(message, broadcastAddr);
    }

    this->protocolClientSocket.send(message, "255.255.255.255");
}

void ProtocolClient::errorMsg(const std::string &code, const std::string &ipAddress) {
    std::string message = code + SEPARATOR + "NotFound";
    this->protocolClientSocket.send(message, ipAddress);
}

std::string ProtocolClient::getCurrentIP() {
    std::string command = "hostname -I";
    std::string ip = "";
    // Open pipe for reading output of command (hostname -I)
    FILE *pipe = popen(command.c_str(), "r");
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

    std::istringstream iss(ip);
    std::string output;
    std::getline(iss, output, ' ');

    return output;
}

