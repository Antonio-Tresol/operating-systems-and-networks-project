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

#include "SslCtxPtr.hpp"
#include "SslPtr.hpp"

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
   * @brief builds server ssl ipv4 socket
   * @param
   */
  Ipv4SslSocket(std::string certFilePath, int port = 7777);

  explicit Ipv4SslSocket(int socketFd) { this->socketFd = socketFd; }
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

  //! NEW
  /**
   * @brief Wait for a TLS/SSL client to initiate the TLS/SSL handshake.
   * @details Waits for a TLS/SSL client to initiate the TLS/SSL
   *  handshake and negotiates the TLS/SSL connection through a handshake.
   */
  void sslAccept() noexcept(false);

  /**
   * @brief accept method uses accept system call to accepts an incoming
   *  connection on a listening stream socket.
   * @details blocking call, it will wait until a connection is available.
   * @throws SocketException if can't accept connection
   * @returns a new socket (handle) to communicate with the client.
   */
  Ipv4SslSocket *Accept() noexcept(false);
  /**
   * @brief listen method uses listen system call to mark a socket as passive
   * @details the socket will be used to accept incoming connection requests.
   *  also, no socket that has used connect because it is an active socket
   * @param int backlog maximum number of pending connection requests in queue
   * @throws SocketException if can't listen to socket
   */
  void sslListen(int backlog) noexcept(false);

  void SSLConnect(const char *host, int port);

  void Connect(const char *host, int port);

  /**
   * @private
   * @brief Binds the socket to an IPv4 address and port number.
   *
   * @param port The port number to bind to.
   * @throws SocketException If there is an error binding to the socket.
   */
  void sslBind(int port) noexcept(false);

  /**
   * Uses the select() function to monitor the socket file descriptor for
   * reading or writing, depending on the error parameter.
   *
   * @param error An error code to determine whether to monitor the socket for
   *  reading or writing. If error is SSL_ERROR_WANT_READ, the
   *  socket will be monitored for reading. Otherwise, it will be monitored for
   *  writing.
   * @return The result of the select() function, which indicates whether the
   *  socket is ready for reading or writing. Returns -1 on error, 0 if
   *  the select timed out, or a positive integer if the socket is ready.
   */
  int readyToReadWrite(int error) noexcept(true);
  void sslCreate(SSL_CTX *parentContext);
  SslCtxPtr *getContext() { return &sslContext; }

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

  /**
   * @private
   * @brief Load certificates
   * @details Verifies and loads the certificates specified as parameters.
   * @param certFileName File containing the certificate.
   * @param keyFileName File containing the keys.
   */
  void SSLLoadCertificates(const char *certFileName, const char *keyFileName);

  int socketFd{};
  fd_set read_fds{};
  struct timeval timeout {
    5, 0
  };
  SslCtxPtr sslContext{};
  SslPtr ssl{};
};
