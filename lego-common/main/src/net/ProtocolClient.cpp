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
    std::string message = buildMessage(code);

    for (int i{0}; i < 7; ++i) {
        int broadcastAddrSuffix{BROADCAST_ADDR_START + BROADCAST_ADDR_INCREMENT * i};
        std::string broadcastAddr{BROADCAST_ADDR_PREFIX + std::to_string(broadcastAddrSuffix)};

        this->protocolClientSocket.send(message, broadcastAddr);
    }

    this->protocolClientSocket.send(message, "255.255.255.255");
}

std::string ProtocolClient::buildMessage(const std::string &code) {
    try {
        std::string message = code + SEPARATOR + getCurrentIP() + ":" + std::to_string(port);
        return message;
    } catch (std::runtime_error &e) {
        Logger::error("Could not find valid self IP: ", e);
        exit(1);
    }
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
    std::string message = buildMessage(code);
    for (const std::string &figure: figures) {
        message += SEPARATOR + figure;
    }
    this->protocolClientSocket.send(message, ipAddress);
}

void ProtocolClient::release() {
    Logger::info("ProtocolClient: Sending " + getLegoMessageCodeName(LEGO_RELEASE));
    std::string code{std::to_string(static_cast<int>(LEGO_RELEASE))};
    std::string message = buildMessage(code);

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
        if (segment1 == BROADCAST_FIRST && segment2 == BROADCAST_SECOND) {
            return address;
        }
    }

    throw std::runtime_error("No IP found with the initial segments: " + std::string{BROADCAST_FIRST} + "." + std::string{BROADCAST_SECOND});
}

