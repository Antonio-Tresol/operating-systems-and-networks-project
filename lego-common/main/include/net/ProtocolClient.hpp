// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include "./socket/IPv4UdpSocket.hpp"
#include <string>
#include <vector>

class ProtocolClient {
    // Constructor and destructor.
public:
    ProtocolClient() = default;

    ~ProtocolClient() = default;

    explicit ProtocolClient(int port);

    // Protocol methods.
public:
    /**
     * @brief Sends a discover message to the given broadcast address.
     * @param broadcastAddr Broadcast address to send the message to.
     */
    void discover();

    void presentBcast(const std::vector<std::string> &figures);

    /**
     * @brief Sends a presentBcast message to the given IP address.
     * @param ipAddress IP address to send the message to or broadcast address.
     * @param figures Vector of figures to send.
     */
    void present(const std::string &ipAddress, const std::vector<std::string> &figures);

    /**
     * @brief Sends a release message to the given broadcast address.
     * @param broadcastAddr Broadcast address to send the message to.
     */
    void release();

    /**
     * @brief Sends an error message to the given IP address.
     * @param code Error code.
     * @param ipAddress IP address to send the message to.
     */
    void errorMsg(const std::string &code, const std::string &ipAddress);

    /**
     * @brief Gets the current IP address of the device.
     * @return Current IP address.
     */
    std::string getCurrentIP();

    /**
     * @brief Gets the port of the protocol client.
     * @return socket of the protocol.
     */
    inline IPv4UdpSocket getProtocolClientSocket() const {
        return protocolClientSocket;
    }

private:
    int port;
    IPv4UdpSocket protocolClientSocket;
};