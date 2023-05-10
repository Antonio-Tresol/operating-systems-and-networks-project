// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// based on the code from Francisco Arroyo Mora, 2023, modified based on
// book "The Linux Programming Interface" by Michael Kerrisk, 2010
// chapeters 59-61.
/**
 * @file Socket.hpp
 * @brief Defines a wrapper for the sys/socket.h library.
 */
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <iostream>

#include "SocketException.hpp"

#ifndef SOCKET_HPP
#define SOCKET_HPP

class Socket {
 public:
  /**
   * @brief Class constructor for sys/socket wrapper (builds active socket)
   * @param	char type: socket type to define ('s' for stream 'd' for
   * datagram) Stream sockets (SOCK_STREAM) provide a reliable, bidirectional
   * byte-stream communication channel between two endpoints (connection
   * oriented). Datagram sockets (SOCK_DGRAM) provide unreliable,
   * connectionless, message-oriented communication.
   * @param	bool ipv6: if we need a IPv6 socket
   * @param	bool ssl: if we need a SSL socket
   * @throws SocketException if the socket type is invalid.
   * @throws SocketException if the socket can't be created.
   * @throws SocketException if the socket SSL context can't be created.
   * @throws SocketException if the socket SSL structure can't be created.
   */
  Socket(char SocketType, bool isIpv6 = false,
         bool isSsl = false) noexcept(false);
  /**
   * @brief Class constructor for sys/socket wrapper (builds passive socket)
   * @param	char type: socket type to define ('s' for stream 'd' for
   * datagram) Stream sockets (SOCK_STREAM) provide a reliable, bidirectional
   * byte-stream communication channel between two endpoints (connection
   * oriented). Datagram sockets (SOCK_DGRAM) provide unreliable,
   * connectionless, message-oriented communication.
   * @param	int port: port number to bind to
   * @param	bool ipv6: if we need a IPv6 socket
   * @throws SocketException if the socket type is invalid.
   * @throws SocketException if the socket can't be created.
   */
  Socket(char socketType, int port, bool isIpv6 = false) noexcept(false);
  /**
   * @brief Class constructor for sys/socket wrapper (builds passive SSLsocket)
   * @param	char type: socket type to define ('s' for stream 'd' for
   * datagram) Stream sockets (SOCK_STREAM) provide a reliable, bidirectional
   * byte-stream communication channel between two endpoints (connection
   * oriented). Datagram sockets (SOCK_DGRAM) provide unreliable,
   * connectionless, message-oriented communication.
   * @param	int port: port number to bind to
   * @param	bool ipv6: if we need a IPv6 socket
   * @param	std::string certFileName: certificate file name
   * @param	std::string keyFileName: key file name
   * @throws SocketException if the socket type is invalid.
   * @throws SocketException if the socket can't be created.
   * @throws SocketException if the socket SSL context can't be created.
   * @throws SocketException if the socket SSL structure can't be created.
   */
  Socket(char socketType, int port, std::string certFileName,
         std::string keyFileName, bool isIpv6 = false) noexcept(false);
  /**
   * @brief constructor for socket, using existing socket descriptor.
   * @param int socketDescriptor
   * @details used for accepting connections, used by the accept method.
   * @throws SocketException if the socket descriptor is invalid.
   */
  explicit Socket(int socketDescriptor) noexcept(false) {
    if (fdIsValid(socketDescriptor) == 0) {
      throw SocketException("Invalid socket descriptor", "Socket(int)");
    }
    this->idSocket = socketDescriptor;
  }
  /**
   * @brief default constructor
   * @details closes socket file descriptor and frees SSL context and structure
   * @throws SocketException if the socket can't be closed.
   */
  ~Socket() noexcept(true);
  /**
   * @brief Close method uses "close" Unix system call. it closes socket file
   * descriptor and frees SSL context and structure if they exist.
   * @throws SocketException if the socket can't be closed.
   */
  void Close() noexcept(false);
  /**
   * @brief system call connects this active socket to a listening socket.
   *  usually used for TCP sockets.
   * @details the connect() syscall serves a purpose when applied to datagram
   *  sockets. Calling connect on a datagram socket causes the kernel to record
   *  a particular address as this socket’s peer. For more details on this see:
   *  The Linux Programming Interface, Michael Kerrisk, Chapter 56 section 6.2
   * @param	std::stringhost host address in dot notation
   * @param	int port port number
   * @throws with nested SocketException if: can't connect to host.
   */
  void Connect(std::string host, int port) noexcept(false);
  /**
   * @brief connects with a pasive socket (TCP). It uses getaddrinfo to get the
   * address of host and then connects to it and hints to specify the type of
   * socket we want to connect to.
   * @param std::string host host address in dot notation, example .
   * @param std::string service service name
   * @throws SocketException if can't get address info
   * @throws SocketException if can't connect to host
   */
  void Connect(std::string host, std::string service) noexcept(false);
  /**
   * @brief read method uses read system call to read data from a TCP socket
   * (STREAM). Other system like send/recv could be used for this too.
   * @throws SocketException if can't read from socket
   * @throws SocketException if connection was closed by peer
   * @return std::string with the message
   */
  std::string Read() noexcept(false);
  /**
   * @brief write method uses write system call.
   * @param std::string buffer to write in.
   * @param int bufferSize the capacity of the buffer.
   * @throws SocketException if can't write to socket
   */
  void Write(std::string message) noexcept(false);
  /**
   * @brief listen method uses listen system call to mark a socket as passive
   * @details the socket will be used to accept incoming connection requests.
   *  also, no socket that has used connect because it is an active socket
   * @param int backlog maximum number of pending connection requests in queue
   * @throws SocketException if can't listen to socket
   */
  void Listen(int backlog) noexcept(false);
  /**
   * @brief bind method uses bind sys call used to bind a socket to a address.
   *  ussually a well known address is used.
   * @param int port port number
   * @throws SocketException if can't bind to socket
   */
  void Bind(int port) noexcept(false);
  /**
   * @brief accept method uses accept system call to accepts an incoming
   *  connection on a listening stream socket.
   * @details blocking call, it will wait until a connection is available.
   * @throws SocketException if can't accept connection
   * @returns a new socket (handle) to communicate with the client.
   */
  Socket* Accept() noexcept(false);
  /**
   * @brief shutdown method uses shutdown system call
   * @param int mode mode to shutdown (SHUT_RD, SHUT_WR, SHUT_RDWR)
   * @throws SocketException if can't shutdown socket
   */
  void Shutdown(int mode) noexcept(false);
  /**
   * @brief: sets the id of the socket (socket file descriptor)
   * @param int id id of the socket
   */
  void SetIDSocket(int newId) noexcept(true);
  /**
   * @brief sendTo method uses sendto system call to send a message to a
   *  UDP Socket (datagram)
   * @param std::string message message to send
   * @param const void* destAddr socket to send the message to
   * @return int number of bytes sent
   * @throws SocketException if can't send message
   */
  int sendTo(std::string message, const void* destAddr) noexcept(false);
  /**
   * @brief recvFrom method uses recvfrom sys call to receive a message from a
   *  UDP Socket (datagram)
   * @param void* srcAddr socket to receive the message from
   * @return std::string message received
   * @throws SocketException if can't receive message
   */
  std::string recvFrom(void* srcAddr) noexcept(false);
  /**
   * @brief SSLConnect method uses SSL_connect sys call to connect to a server
   * @param std::string  host host name
   * @param int port port number
   * @throws SocketException if can't connect to host
   * @throws SocketException if can't set SSL file descriptor
   * @throws SocketException if can't connect to SSL host
   */
  void SSLConnect(std::string host, int port) noexcept(false);
  /**
   * @brief SSLConnect method uses SSL_connect sys call to connect to a server
   * @param std::string host host name
   * @param std::string  service service name
   * @details service name can be a port number or a service name
   * @throws SocketException if can't connect to host
   * @throws SocketException if can't set SSL file descriptor
   * @throws SocketException if can't connect to SSL host
   */
  void SSLConnect(std::string host, std::string service) noexcept(false);
  /**
   * @brief: SSLRead method uses SSL_read system call to read from a socket
   * @return: std::string message read
   * @throws SocketException if can't read from SSL socket
   */
  std::string SSLRead() noexcept(false);
  /**
   * @brief SSLWrite method uses SSL_write system call to write to a socket
   * @param std::string buffer buffer to store the message
   * @return int number of bytes written
   * @throws SocketException if can't write to SSL socket
   */
  int SSLWrite(std::string message) noexcept(false);
  /**
   * @brief Construct a new SSL * variable from a previously created context.
   * Constructs a new SSL * variable from a previously created context using the
   * original socket.
   * @param parent is the server socket with a previously created context.
   * @return SSL* A new SSL * variable.
   */
  void SSLCreate(Socket* parent) noexcept(false);
  /**
   * @brief Wait for a TLS/SSL client to initiate the TLS/SSL handshake.
   * @details Waits for a TLS/SSL client to initiate the TLS/SSL
   *  handshake and negotiates the TLS/SSL connection through a handshake.
   */
  void SSLAccept() noexcept(false);
  /**
   * @brief Get the cipher used by the current SSL connection.
   * @return const char* The cipher used by the current SSL connection.
   */
  const char* SSLGetCipher() noexcept(false);
  /**
   * @brief starts all Openssl libraries to get error information.
   * @throws SocketException if can't start libraries
   * @details According to OpenSSL documentation is called automatically since
   *  version 1.1.0. It is added here for backwards compatibility.
   *  It must be call before any other function that uses Openssl
   *  libraries so that the error information can be retrieved.
   */
  void SSLStartLibrary() noexcept(false);
  /**
   * @brief Show SSL certificates.
   *
   * Displays the SSL certificates identified in the connection.
   */
  void SSLShowCerts() noexcept(true);

 private:
  int idSocket{0};               ///< id of the socket
  int port{0};                   ///< port number of passive socket
  bool ipv6{false};              ///< true if the socket is ipv6
  bool isOpen{false};            ///< true if the socket is open
  SSL_CTX* SSLContext{nullptr};  ///< SSL context if the socket is SSL
  SSL* SSLStruct{nullptr};       ///< SSL structure if the socket is SSL
  /**
   * @private
   * @brief Checks if the given file descriptor is valid or not.
   *
   * @param fd The file descriptor to be checked for validity.
   * @return 1 if the file descriptor is valid or there's an error other than a
   *  bad file descriptor, and 0 if the file descriptor is invalid.
   */
  int fdIsValid(int fd);
  /**
   * @private
   * @brief Connects to an IPv4 host at the specified port number.
   *
   * @param host The IPv4 address of the host in dotted-decimal notation.
   * @param port The port number to connect to.
   * @throws SocketException If there is an error connecting to the host.
   * @throws SocketException If the IPv4 address is invalid.
   */
  void connectIPv4(const char* host, int port) noexcept(false);
  /**
   * @private
   * @brief Connects to an IPv6 host at the specified port number.
   *
   * @param host The IPv6 address of the host in dotted-decimal notation.
   * @param port The port number to connect to.
   * @throws SocketException If there is an error connecting to the host.
   * @throws SocketException If the IPv6 address is invalid.
   */
  void connectIPv6(const char* host, int port) noexcept(false);
  /**
   * @private
   * @brief Binds the socket to an IPv4 address and port number.
   *
   * @param port The port number to bind to.
   * @throws SocketException If there is an error binding to the socket.
   */
  void bindIPv4(int port) noexcept(false);
  /**
   * @private
   * @brief Binds the socket to an IPv6 address and port number.
   * @param port The port number to bind to.
   * @throws SocketException If there is an error binding to the socket.
   */
  void bindIPv6(int port) noexcept(false);
  /**
   * @private
   * @brief Checks if the given file descriptor is ready to read from.
   *
   * @param fd The file descriptor to be checked.
   * @param timeoutSec The number of seconds to wait before timing out.
   * @param timeoutMicroSec The number of microseconds to wait before time out.
   * @return true if the file descriptor is ready to read from, 0 if the file
   *  descriptor is not ready to read from, and -1 if there is an error.
   */
  bool isReadyToRead(int timeoutSec = 0,
                     int timeoutMicroSec = 1) noexcept(false);
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
  /**
   * @private
   * @brief Initialize SSL server context.
   * @details Uses SSL_library_init, OpenSSL_add_all_algorithms,
   *  SSL_load_error_strings, TLS_server_method, and SSL_CTX_new
   *  to create a new SSL server context
   *  for encrypted communications. This context is stored in class instance.
   */
  void SSLInitServerContext() noexcept(false);
  /**
   * @brief Initialize server SSL object.
   * @details Uses SSL_CTX_new and SSL_new to create a new SSL object for server
   *  connections with the defined context.
   * @param certFileName File containing the certificate.
   * @param keyFileName File containing the keys.
   */
  void SSLInitServer(const char* certFileName,
                     const char* keyFileName) noexcept(false);
  /**
   * @private
   * @brief Load certificates
   * @details Verifies and loads the certificates specified as parameters.
   * @param certFileName File containing the certificate.
   * @param keyFileName File containing the keys.
   */
  void SSLLoadCertificates(const char* certFileName,
                           const char* keyFileName) noexcept(false);
  /**
   * @private
   * @brief SSLInitContext method initializes the SSL context
   * @details uses the TLS_client_method to create a new context
   * @throws SocketException if can't create SSL context
   * @throws SocketException if can't create SSL method
   */
  void SSLInitContext() noexcept(false);
  /**
   * @private
   * @brief SSLInitContext method initializes the SSL context
   * @details uses openssl library to initialize the SSL context
   * @throws SocketException if can't create SSL context
   * @throws SocketException if can't create SSL method
   */
  void SSLInit() noexcept(false);
};
#endif