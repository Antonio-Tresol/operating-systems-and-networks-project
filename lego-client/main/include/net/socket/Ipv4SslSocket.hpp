// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <arpa/inet.h>  // for inet_pton
#include <netdb.h>
#include <openssl/ssl.h>
#include <sys/socket.h>
#include <sys/types.h>  // for connect
#include <unistd.h>

#include <cerrno>
#include <cstddef>
#include <cstdio>   // for perror
#include <cstdlib>  // for exit
#include <cstring>  // for memset
#include <string>

#include "./SslCtxPtr.hpp"
#include "./SslPtr.hpp"

/**
 * @brief A socket to connect via IPv4 over TCP over SSL.
 */
class Ipv4SslSocket {
 public:
  /**
   * Constructor.
   *
   * Checks initialized socket is valid.
   */
  Ipv4SslSocket();

  /**
   * Destructor.
   *
   * Closes object socket.
   */
  ~Ipv4SslSocket();

  /**
   * Object is meant to be unique.
   */
  Ipv4SslSocket(const Ipv4SslSocket &) = delete;

  Ipv4SslSocket &operator=(const Ipv4SslSocket &) = delete;

  void sslConnect(const std::string &host, int port) const;

  /**
   * @brief Establishes a TCP connection over SSL.
   * @param host Host to connect to.
   * @param service Service over which to connect.
   */
  void sslConnect(const std::string &host, const std::string &service) const;

  /**
   * @brief Reads from a TCP connection over SSL.
   * @return Response returned by connection.
   */
  [[nodiscard]] std::string sslRead();

  /**
   * @brief Writes to a TCP connection over SSL.
   * @param text Content to write to connection.
   */
  void sslWrite(const std::string &text) const;

 private:
  static constexpr int TCP_ID{6};
  static constexpr int64_t CHUNK_SIZE{512};
  static constexpr struct addrinfo hints {
    0, AF_UNSPEC, SOCK_STREAM, 0, 0, nullptr, nullptr, nullptr
  };

  /**
   * Appends the current C error to the input message.
   * @param message Message to append the error.
   * @return Concatenation of message and error
   */
  static std::string appendErr(const std::string &message);

  /**
   * Appends the current SSL error to the input message.
   * @param message Message to append the error.
   * @return Concatenation of message and error
   */
  static std::string appendSslErr(const std::string &message);

  void tcpConnect(const std::string &host, int port) const;

  /**
   * @brief Establishes a TCP connection.
   * @param host Host to connect to.
   * @param service Service over which to connect.
   */
  void tcpConnect(const std::string &host, const std::string &service) const;

  /**
   * @brief Returns whether socket fd is ready to be read from.
   * @return Whether socket fd is ready to be read from.
   */
  bool isReadReady();

  int socketFd{socket(AF_INET, SOCK_STREAM, TCP_ID)};
  fd_set read_fds{};
  struct timeval timeout {
    5, 0
  };
  SslCtxPtr sslContext{};
  SslPtr ssl{static_cast<SSL_CTX *>(this->sslContext)};
};
