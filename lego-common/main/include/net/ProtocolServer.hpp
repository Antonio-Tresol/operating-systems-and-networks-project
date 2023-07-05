// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include "socket/IPv4UdpSocket.hpp"
#include "controller/ProtocolController.hpp"
#include <string>
#include <vector>
#include <thread>
#include <atomic>

class ProtocolServer {
public:
    // Constructor and destructor.
    explicit ProtocolServer(int port, ProtocolController& protocolController);

    ~ProtocolServer() = default;

    /**
     * @brief Starts the server (including the 7 threads).
     *
    */
    void start();

    /**
     * @brief Stops the server (including the 7 threads).
     *
    */
    void stop();

private:
    /**
     * @brief Analyzes the message and returns the code of the message.
     *
     * @param message Message to analyze.
     * @return int Code of the message.
     */
    int validateMessage(std::string message) const;

    /**
     * @brief Responds to the message with the given code.
     *
     * @param code Code of the message.
     * @param ip IP address to respond to.
     */
    void respond(int code, std::string ip, std::string message) const;

    /**
     * @brief Handles the request of the message (a received packet).
     *
     * @param message Message to handle.
     */
    void handleRequest(std::string message) const;

    bool checkHost(std::string message) const;

    /**
     * @brief Get the IP from the message.
     *
     * @param message Message to get the IP from.
     * @return std::string IP address.
     */
    std::string getIP(std::string message) const;

    /**
     * @brief Get the body from the message.
     *
     * @param message Message to get the body from.
     * @return std::string body.
     */
    std::string getBody(std::string message) const;

    /**
     * @brief When a LEGO_PRESENT message is received, this function extracts the
     * figures from the message.
     *
     * @param message Raw message from socket.
     * @return std::string Figures
     */
    std::string extractFigures(std::string message) const;

    /**
     * @brief Keeps listening for messages.
     *
     */
    void keepListening() const;

    /**
     * @brief Finds the nth occurrence of a character in a string.
     *
     * @param str String to search in.
     * @param c Character to search for.
     * @param n Nth occurrence.
     * @return int Position of the nth occurrence.
     */
    int findNthOccurrence(const std::string &str, char c, int n) const;

    IPv4UdpSocket receiverSocket;
    ProtocolController& protocolController;
    std::vector<std::thread> workers;
    std::atomic<bool> keepListeningFlag;
};