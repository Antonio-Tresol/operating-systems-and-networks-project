// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <arpa/inet.h>  // for inet_pton
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>  // for connect
#include <unistd.h>

#include <cerrno>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>

/**
 * @brief A socket to connect via IPv4 over UDP.
 */
class IPv4UdpSocket {
 public:
  explicit IPv4UdpSocket(int port);

  ~IPv4UdpSocket();

  /**
   * @brief Binds socket to given port.
   */
  void bind() const;

  /**
   * @brief Sends a message to a given address
   * @param text message to send
   * @param address address to send to
   */
  void send(const std::string &text, const std::string &address) const;

  /**
   * @brief Receives a message on the set port
   * @return message received
   */
  std::string receive() const;

  void close() const;

 private:
  static constexpr int NONE{0};
  static constexpr int UDP_ID{17};
  static constexpr int64_t CHUNK_SIZE{512};

  /**
   * Appends the current C error to the input message.
   * @param message Message to append the error.
   * @return Concatenation of message and error
   */
  static std::string appendErr(const std::string &message) {
    return message + ": " + strerror(errno);
  }

  int socketFD;
  int port;
};