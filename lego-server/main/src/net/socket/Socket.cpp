// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// based on the code from Francisco Arroyo Mora, 2023, modified based on
// book "The Sys Programming Interface" by Michael Kerrisk, 2010
// chapters 59-61.
#include "../include/net/socket/Socket.hpp"

int Socket::fdIsValid(int fd) {
  // checks if the file descriptor is valid
  return fcntl(fd, F_GETFD) != -1 || errno != EBADF;
}

Socket::Socket(char socketType, bool isIpv6, bool isSsl) {
  // check if socket type is valid.
  if (socketType != 's' && socketType != 'd') {
    throw SocketException("Invalid socket type", "Socket::Socket", EINVAL);
  }
  // Set the domain to IPv4 or IPv6
  int domain = AF_INET;
  if (isIpv6) {
    domain = AF_INET6;
    this->ipv6 = true;
  }
  // Set the socket type to TCP or UDP
  int type = 0;
  if (socketType == 's') {
    type = SOCK_STREAM;  // TCP socket (connection oriented)
  } else if (socketType == 'd') {
    type = SOCK_DGRAM;  // UDP socket (connectionless)
  }
  // Create the socket
  this->idSocket = socket(domain, type, 0);
  if (this->idSocket == -1) {
    throw SocketException("Error creating socket", "Socket::Socket", errno);
  }
  // Prepare socket if SSL is enabled
  if (isSsl) {
    try {
      this->SSLInit();
    } catch (const SocketException &e) {
      throw_with_nested(
          SocketException("Error Creating Socket", "Socket::Socket", false));
    }
  }
  this->isOpen = true;
}

Socket::Socket(char socketType, int port, bool isIpv6) noexcept(false) {
  // check if socket type is valid.
  if (socketType != 's' && socketType != 'd') {
    throw SocketException("Invalid socket type", "Socket::Socket", EINVAL);
  }
  // Set the domain to IPv4 or IPv6
  int domain = AF_INET;
  if (isIpv6) {
    domain = AF_INET6;
    this->ipv6 = true;
  }
  // Set the socket type to TCP or UDP
  int type = 0;
  if (socketType == 's') {
    type = SOCK_STREAM;  // TCP socket (connection oriented)
  } else if (socketType == 'd') {
    type = SOCK_DGRAM;  // UDP socket (connectionless)
  }
  // Create the socket
  this->idSocket = socket(domain, type, 0);
  if (this->idSocket == -1) {
    throw SocketException("Error creating pasive Socket", "Socket::Socket",
                          errno);
  }
  // bind the socket to the port
  try {
    this->Bind(port);
    this->Listen(128);
  } catch (const SocketException &e) {
    throw_with_nested(SocketException("Error Creating Passive Socket",
                                      "Socket::Socket", false));
  }
}
Socket::Socket(char socketType, int port, std::string certFileName,
               std::string keyFileName, bool isIpv6) {
  // check if socket type is valid.
  if (socketType != 's' && socketType != 'd') {
    throw SocketException("Invalid socket type", "Socket::Socket", EINVAL);
  }
  // prepare the ssl context
  try {
    this->SSLInitServer(certFileName.c_str(), keyFileName.c_str());
  } catch (const SocketException &e) {
    throw_with_nested(SocketException("Error Creating Passive Socket",
                                      "Socket::Socket", false));
  }
  // Create a socket:
  // Set the domain to IPv4 or IPv6
  int domain = AF_INET;
  if (isIpv6) {
    domain = AF_INET6;
    this->ipv6 = true;
  }
  // Set the socket type to TCP or UDP
  int type = 0;
  if (socketType == 's') {
    type = SOCK_STREAM;  // TCP socket (connection oriented)
  } else if (socketType == 'd') {
    type = SOCK_DGRAM;  // UDP socket (connectionless)
  }
  // Create the socket
  this->idSocket = socket(domain, type, 0);
  if (this->idSocket == -1) {
    throw SocketException("Error creating pasive Socket", "Socket::Socket",
                          errno);
  }
  // bind it to an address and port, and start listening
  // for incoming connections
  try {
    this->Bind(port);
    this->Listen(SOMAXCONN);
  } catch (const SocketException &e) {
    throw_with_nested(SocketException("Error Creating Passive Socket",
                                      "Socket::Socket", false));
  }
}

Socket::Socket::~Socket() {
  if (this->isOpen) {
    try {
      this->Close();
    } catch (SocketException &e) {
      std::cerr << e.what() << std::endl;
    }
  }
}

void Socket::Close() {
  int status = close(this->idSocket);
  if (status == -1) {
    throw SocketException("Error closing socket", "Socket::Close", errno);
  }
  if (this->SSLContext != nullptr) {
    SSL_CTX_free(this->SSLContext);
  }
  if (this->SSLStruct != nullptr) {
    SSL_shutdown(this->SSLStruct);
    SSL_free(this->SSLStruct);
  }
  this->isOpen = false;
}

void Socket::connectIPv4(const char *host, int port) {
  int status = -1;
  // sockaddr_in is a struct containing an information about internet sockets.
  // sockaddr_in6 is used for IPv6. they contain ip address and port number.
  struct sockaddr_in hostIpv4;  // ipv4 address struct set to 0.
  memset(&hostIpv4, 0, sizeof(hostIpv4));
  hostIpv4.sin_family = AF_INET;  // socket domain (IPv4)
  // inep_pton(inet_presentation string to network) converts an IP address in
  // dotted-decimal notation to binary form.
  status = inet_pton(AF_INET, host, &hostIpv4.sin_addr);
  if (status == 0) {
    throw SocketException("Invalid IPv4 address", "Socket::Connect", EINVAL);
  } else if (status == -1) {
    throw SocketException("Error converting IPv4 address", "Socket::Connect",
                          errno);
  }
  // sin_port is the port number we want to connect to. it is a 16-bit integer
  // network byte order is big endian, host byte order is little endian, so we
  // need to convert the port number to network byte order.
  hostIpv4.sin_port = htons(port);  // host to network short (htons)
  struct sockaddr *hostIpv4Ptr = reinterpret_cast<struct sockaddr *>(&hostIpv4);
  socklen_t hostIpv4Len = sizeof(hostIpv4);
  // connect() system call connects this active socket to a listening socket
  // pasive socket. usually used for TCP sockets.
  status = connect(idSocket, hostIpv4Ptr, hostIpv4Len);
  if (status == -1) {
    throw SocketException("Error connecting to IPv4 address", "Socket::Connect",
                          errno);
  }
}

void Socket::connectIPv6(const char *host, int port) {
  int status = -1;
  struct sockaddr_in6 hostIpv6;            // IPv6 address struct
  memset(&hostIpv6, 0, sizeof(hostIpv6));  // set to 0
  hostIpv6.sin6_family = AF_INET6;         // socket domain (IPv6)
  // inep_pton(inet_presentation string to network) converts an IP address in
  // dotted-decimal notation to binary form.
  status = inet_pton(AF_INET6, host, &hostIpv6.sin6_addr);
  if (status == 0) {
    throw SocketException("Invalid IPv6 address", "Socket::Connect", EINVAL);
  } else if (status == -1) {
    throw SocketException("Error converting IPv6 address", "Socket::Connect",
                          errno);
  }
  // sin_port is the port number we want to connect to. it is a 16-bit integer
  hostIpv6.sin6_port = htons(port);
  struct sockaddr *hostIpv6Ptr = reinterpret_cast<sockaddr *>(&hostIpv6);
  socklen_t hostIpv6Len = sizeof(hostIpv6);
  // connect() system call connects this active socket to a listening socket
  // pasive socket. usually used for TCP sockets.
  status = connect(idSocket, hostIpv6Ptr, hostIpv6Len);
  if (status == -1) {
    throw SocketException("Error connecting to IPv6 address", "Socket::Connect",
                          errno);
  }
}

void Socket::Connect(std::string host, int port) {
  try {
    if (this->ipv6) {
      this->connectIPv6(host.c_str(), port);
    } else {
      this->connectIPv4(host.c_str(), port);
    }
  } catch (SocketException &e) {
    throw;
  }
}

void Socket::Connect(std::string host, std::string service) {
  int status = -1;
  struct addrinfo hints, *result, *rp;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;      // to allow IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;  // TCP
  hints.ai_flags = 0;
  hints.ai_protocol = 0;
  hints.ai_canonname = nullptr;
  hints.ai_addr = nullptr;
  hints.ai_next = nullptr;
  // Given a hostname and a service name, getaddrinfo() returns a set of
  // structures containing the corresponding binary IP address(es) and port
  // number. Thats why we use rp and result to iterate over the list of
  // addresses returned by getaddrinfo.
  status = getaddrinfo(host.c_str(), service.c_str(), &hints, &result);
  if (status != 0) {
    throw SocketException("Error getting address info", "Socket::Connect",
                          status);
  }
  for (rp = result; rp; rp = rp->ai_next) {
    status = connect(this->idSocket, rp->ai_addr, rp->ai_addrlen);
    if (0 == status) {
      break;
    }
  }
  freeaddrinfo(result);
  if (status == -1) {
    throw SocketException("Error connecting to host", "Socket::Connect", errno);
  }
}

std::string Socket::Read() {
  int nBytesRead = -1;
  std::string output;
  int bufferSize = 512;
  char buffer[512];

  while (isReadyToRead(5)) {
    // Read from the socket and store the data in buffer using system call read
    nBytesRead = read(this->idSocket, buffer, bufferSize);

    if (-1 == nBytesRead) {
      throw SocketException("Error reading from socket", "Socket::Read", errno);
    } else if (0 == nBytesRead) {
      // Connection has been closed or reset, break the loop and return the
      // output
      break;
    } else {
      // Append the data read from the socket to the output string
      output.append(buffer, nBytesRead);
    }
  }

  return output;
}

void Socket::Write(std::string message) {
  int status = -1;
  const char *buffer = message.c_str();
  int bufferSize = message.length();
  // Write to the socket using system call write
  status = write(this->idSocket, buffer, bufferSize);
  if (-1 == status) {
    throw SocketException("Error writing to socket", "Socket::Write", errno);
  }
}

void Socket::Listen(int backlog) {
  int status = -1;
  // mark the socket as passive using system call listen
  status = listen(this->idSocket, backlog);
  if (-1 == status) {
    throw SocketException("Error listening to socket", "Socket::Listen", errno);
  }
}

void Socket::bindIPv4(int port) {
  int status = -1;
  // prepare the address structure for the bind system call
  struct sockaddr_in hostIpv4;
  memset(&hostIpv4, 0, sizeof(hostIpv4));
  hostIpv4.sin_family = AF_INET;          // socket domain is IPv4
  hostIpv4.sin_addr.s_addr = INADDR_ANY;  //  bind to any address
  // htons converts the unsigned short integer hostshort from host byte order
  // to network byte order. For portable code, it is recommended to use htons
  // whenver you are using a number from host byte order in a context where
  // network byte order is expected.
  hostIpv4.sin_port = htons(port);  //  bind to port
  struct sockaddr *hostIpv4Ptr = reinterpret_cast<sockaddr *>(&hostIpv4);
  socklen_t hostIpv4Len = sizeof(hostIpv4);
  // bind the socket to the address and port number
  status = bind(idSocket, hostIpv4Ptr, hostIpv4Len);
  if (-1 == status) {
    throw SocketException("Error binding to socket IPV4", "Socket::Bind",
                          errno);
  }
}

void Socket::bindIPv6(int port) {
  int status = -1;
  // prepare the address structure to bind the socket to an IPv6 address
  struct sockaddr_in6 hostIpv6;
  memset(&hostIpv6, 0, sizeof(hostIpv6));
  hostIpv6.sin6_family = AF_INET6;   // socket domain IPv6
  hostIpv6.sin6_addr = in6addr_any;  // bind to any address IPv6
  hostIpv6.sin6_port = htons(port);  // port number to bind to
  struct sockaddr *hostIpv6Ptr = reinterpret_cast<sockaddr *>(&hostIpv6);
  socklen_t hostIpv6Len = sizeof(hostIpv6);
  // bind the socket to the address and port number
  status = bind(idSocket, hostIpv6Ptr, hostIpv6Len);
  if (-1 == status) {
    throw SocketException("Error binding to socket IPV6", "Socket::Bind",
                          errno);
  }
}

void Socket::Bind(int port) {
  try {
    if (this->ipv6) {
      this->bindIPv6(port);
    } else {
      this->bindIPv4(port);
    }
  } catch (SocketException &e) {
    throw;
  }
}

Socket *Socket::Accept() {
  int newSocketFD = -1;
  // sockaddr_storage is large enough to hold both IPv4 and IPv6 structures
  struct sockaddr_storage clientAddr;
  memset(&clientAddr, 0, sizeof(clientAddr));
  struct sockaddr *clientAddrPtr = reinterpret_cast<sockaddr *>(&clientAddr);
  socklen_t clientAddrLen = sizeof(clientAddr);
  // accept a connection on a socket
  newSocketFD = accept(this->idSocket, clientAddrPtr, &clientAddrLen);
  if (newSocketFD < 0) {
    throw SocketException("Error accepting connection", "Socket::Accept",
                          errno);
  }
  Socket *newSocket = new Socket(newSocketFD);
  return newSocket;
}

void Socket::Shutdown(int mode) {
  int status = -1;
  // shutdown can be used to disable read, write or both
  status = shutdown(this->idSocket, mode);
  if (-1 == status) {
    throw SocketException("Error shutting down socket", "Socket::Shutdown",
                          errno);
  }
}

void Socket::SetIDSocket(int newId) noexcept(true) { this->idSocket = newId; }

int Socket::sendTo(std::string message, const void *destAddr) {
  int nBytesSent = -1;
  // Determine the size of the sockaddr structure based on the ipv6 attribute
  socklen_t addrSize = this->ipv6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in);
  // Send the message using the sendto system call
  nBytesSent = sendto(this->idSocket, message.c_str(), message.length(), 0,
                      reinterpret_cast<const sockaddr *>(destAddr), addrSize);
  if (-1 == nBytesSent) {
    throw SocketException("Error sending message", "Socket::sendTo", errno);
  }
  return nBytesSent;
}

std::string Socket::recvFrom(void *srcAddr) {
  int nBytesReceived = -1;
  std::string output;
  int bufferSize = 512;
  char buffer[512];

  // Determine the size of the sockaddr structure based on the ipv6 attribute
  socklen_t addrSize = this->ipv6 ? sizeof(sockaddr_in6) : sizeof(sockaddr_in);

  while (isReadyToRead()) {
    // Receive data using the recvfrom system call
    nBytesReceived = recvfrom(this->idSocket, buffer, bufferSize, 0,
                              reinterpret_cast<sockaddr *>(srcAddr), &addrSize);

    if (-1 == nBytesReceived) {
      throw SocketException("Error receiving message", "Socket::recvFrom",
                            errno);
    } else if (0 == nBytesReceived) {
      // Connection has been closed or reset, break the loop and return the
      // output
      break;
    } else {
      // Append the data received to the output string
      output.append(buffer, nBytesReceived);
    }
  }
  return output;
}

void Socket::SSLInitContext() {
  SSLStartLibrary();
  // We must create a method to define our context
  const SSL_METHOD *method = TLS_client_method();
  if (method == nullptr) {
    throw SocketException("Error creating SSL method",
                          "Socket::SSLInitContext");
  }
  // build a new SSL context using the method
  SSL_CTX *context = SSL_CTX_new(method);
  if (context == nullptr) {
    throw SocketException("Error creating SSL Ctx", "Socket::SSLInitContext");
  }
  this->SSLContext = context;
}
/**
 * @brief SSLInitContext method initializes the SSL context
 * @details uses openssl library to initialize the SSL context
 * @throws SocketException if can't create SSL context
 * @throws SocketException if can't create SSL method
 */
void Socket::SSLInit() {
  // Create a SSL socket, a new context must be created before
  try {
    if (this->SSLContext == nullptr) {
      this->SSLInitContext();
    }
  } catch (SocketException &e) {
    throw;
  }
  SSL *ssl = SSL_new(this->SSLContext);
  if (ssl == nullptr) {
    throw SocketException("Error creating SSL", "Socket::SSLInit");
  }
  this->SSLStruct = ssl;
}
void Socket::SSLInitServerContext() {
  SSLStartLibrary();
  const SSL_METHOD *method = nullptr;
  method = TLS_server_method();
  if (method == nullptr) {
    throw SocketException("Error Initiating SSL Server Context",
                          "Socket::SSLInitServerContext");
  }
  this->SSLContext = SSL_CTX_new(method);
  if (this->SSLContext == nullptr) {
    throw SocketException("Error Initiating SSL Server Context",
                          "Socket::SSLInitServerContext");
  }
}
void Socket::SSLInitServer(const char *certFileName, const char *keyFileName) {
  try {
    this->SSLInitServerContext();
    this->SSLLoadCertificates(certFileName, keyFileName);
  } catch (SocketException &e) {
    throw;
  }
}

void Socket::SSLLoadCertificates(const char *certFileName,
                                 const char *keyFileName) {
  // set the local certificate from CertFileName
  int status = -1;
  status = SSL_CTX_use_certificate_file(this->SSLContext, certFileName,
                                        SSL_FILETYPE_PEM);
  if (status <= 0) {
    throw SocketException("Error loading certificate",
                          "Socket::SSLLoadCertificates");
  }

  // set the private key from KeyFileName (may be the same as CertFile)
  status = SSL_CTX_use_PrivateKey_file(this->SSLContext, keyFileName,
                                       SSL_FILETYPE_PEM);
  if (status <= 0) {
    throw SocketException("Error loading private key",
                          "Socket::SSLLoadCertificates");
  }
  // verify private key
  status = SSL_CTX_check_private_key(this->SSLContext);
  if (!status) {
    throw SocketException("Error verifying private key",
                          "Socket::SSLLoadCertificates");
  }
}

void Socket::SSLShowCerts() noexcept(true) {
  // Get the peer's certificate
  X509 *peerCertificates = SSL_get_peer_certificate(this->SSLStruct);
  if (peerCertificates != nullptr) {
    std::cout << "Server certificates:" << std::endl;
    // Get the subject name of the certificate and convert it to a string
    char *line =
        X509_NAME_oneline(X509_get_subject_name(peerCertificates), nullptr, 0);
    std::cout << "Subject: " << line << std::endl;
    // Free the memory allocated for the subject name string
    OPENSSL_free(line);
    // Get the issuer name of the certificate and convert it to a string
    line =
        X509_NAME_oneline(X509_get_issuer_name(peerCertificates), nullptr, 0);
    std::cout << "Issuer: " << line << std::endl;
    // Free the memory allocated for the issuer name string
    OPENSSL_free(line);
    // Free the certificate object
    X509_free(peerCertificates);
  } else {
    std::cout << "No certificates." << std::endl;
  }
}

void Socket::SSLCreate(Socket *parent) {
  SSL *ssl = SSL_new(parent->SSLContext);
  if (ssl == nullptr) {
    throw SocketException("Error creating SSL", "Socket::SSLCreate");
  }
  this->SSLStruct = ssl;
  if (!SSL_set_fd(ssl, this->idSocket))
    throw SocketException("Error setting SSL fd", "Socket::SSLCreate");
}

void Socket::SSLAccept() {
  while (true) {
    // Call SSL_accept() to initiate TLS/SSL handshake
    int result = SSL_accept(this->SSLStruct);
    if (result > 0) {
      // Handshake succeeded
      break;
    }
    int error = SSL_get_error(this->SSLStruct, result);
    // Handle the error based on the specific SSL error code
    switch (error) {
        // ssl_error_want_read and ssl_error_want_write are not errors per se,
        // so we want to retry the call. Here we use a select() see if the
        // socket is ready for read/write
      case SSL_ERROR_WANT_READ:
      case SSL_ERROR_WANT_WRITE: {
        int readyToReadOrWrite = readyToReadWrite(error);
        if (readyToReadOrWrite < 0) {
          throw SocketException("Error while waiting to read/write socket",
                                "Socket::SSLAccept");
        }
        // The socket is now ready, retry SSL_accept()
        continue;
      }
      case SSL_ERROR_ZERO_RETURN:
        // The TLS/SSL connection has been closed
        throw SocketException("TLS/SSL connection has been closed",
                              "Socket::SSLAccept");
      case SSL_ERROR_SYSCALL:
        // I/O error occurred; check errno for the specific error
        throw SocketException("I/O error occurred", "Socket::SSLAccept", errno);
      default:
        // Other SSL errors
        throw SocketException("Other SSL errors", "Socket::SSLAccept");
    }
  }
}

void Socket::SSLConnect(std::string host, int port) {
  int status = -1;
  try {
    this->Connect(host, port);  // Establish a non SSL connection first
  } catch (SocketException &e) {
    throw_with_nested(SocketException("Error connecting to host",
                                      "Socket::SSLConnect", errno, false));
  }
  status = SSL_set_fd(this->SSLStruct, this->idSocket);
  if (-1 == status) {
    throw SocketException("Error setting SSL file descriptor",
                          "Socket::SSLConnect");
  }
  status = SSL_connect(this->SSLStruct);
  if (-1 == status) {
    throw SocketException("Error connecting to SSL host", "Socket::SSLConnect");
  }
}

void Socket::SSLConnect(std::string host, std::string service) {
  int status = -1;
  try {
    this->Connect(host, service);  // Establish a non SSL connection first
  } catch (SocketException &e) {
    throw_with_nested(SocketException("Error connecting to host",
                                      "Socket::SSLConnect", errno));
  }
  status = SSL_set_fd(this->SSLStruct, this->idSocket);
  if (-1 == status) {
    throw SocketException("Error setting SSL file descriptor",
                          "Socket::SSLConnect");
  }
  status = SSL_connect(this->SSLStruct);
  if (-1 == status) {
    throw SocketException("Error connecting to SSL host", "Socket::SSLConnect");
  }
}

std::string Socket::SSLRead() {
  int nBytesRead = -1;
  std::string output;
  int bufferSize = 512;
  char buffer[512];
  // Read from the socket until there is no more data to read
  while (isReadyToRead()) {
    nBytesRead = SSL_read(this->SSLStruct, buffer, bufferSize);

    if (nBytesRead < 0) {
      // gets ssl error to see if we should try again.
      int sslError = SSL_get_error(this->SSLStruct, nBytesRead);
      if (sslError == SSL_ERROR_WANT_READ || sslError == SSL_ERROR_WANT_WRITE) {
        continue;
      } else {
        // if it was an error that will not be solved by trying again
        throw SocketException("Error reading from SSLSocket",
                              "Socket::SSLRead");
      }
    } else if (nBytesRead == 0) {
      // Connection has been closed or reset, break the loop and return the
      // output
      break;
    } else {
      // Append the data read from the socket to the output string
      output.append(buffer, nBytesRead);
    }
  }

  return output;
}

int Socket::SSLWrite(std::string message) {
  int nBytesWritten = -1;
  // ssl_write returns the number of bytes written or -1 if an error occurs
  nBytesWritten = SSL_write(this->SSLStruct, message.c_str(), message.length());
  if (nBytesWritten <= 0) {
    // If the error is SSL_ERROR_WANT_READ it means the write operation was
    // not completed and we must try again. If the error is
    // SSL_ERROR_WANT_WRITE it means the socket is not ready for writing and
    // we must try again.
    int sslError = SSL_get_error(this->SSLStruct, nBytesWritten);
    if (sslError == SSL_ERROR_WANT_READ || sslError == SSL_ERROR_WANT_WRITE) {
      SSLWrite(message);
    } else {
      throw SocketException("Error writing to SSL socket", "Socket::SSLWrite");
    }
  }
  return nBytesWritten;
}
bool Socket::isReadyToRead(int timeoutSec, int timeoutMicroSec) {
  // Declare a set of file descriptors to monitor for reading.
  fd_set readSet;
  // Initialize the set to have zero bits for all file descriptors.
  FD_ZERO(&readSet);
  // Add the socket's file descriptor to the set.
  FD_SET(this->idSocket, &readSet);
  // Declare a timeval structure to specify the timeout.
  timeval timeout;
  // Set the timeval structure's seconds field to the input timeoutSec.
  timeout.tv_sec = timeoutSec;
  // Set the timeval structure's microseconds field to the input
  // timeoutMicroSec.
  timeout.tv_usec = timeoutMicroSec;
  // Call the select() syscall to check file descriptor set for readability.
  // It returns the number of ready file descriptors, or -1 if an error.
  int status = select(this->idSocket + 1, &readSet, nullptr, nullptr, &timeout);
  // Check if the select() function returned -1 (indicating an error).
  if (-1 == status) {
    // If an error occurred, throw SocketException with description of error,
    // the function name, and the error number.
    throw SocketException("Error checking if socket is ready to read",
                          "Socket::isReadyToRead", errno);
  }
  // Return true if the select() function indicated that the socket's fd
  // is ready for reading, otherwise return false.
  return (status > 0 && FD_ISSET(this->idSocket, &readSet));
}

int Socket::readyToReadWrite(int error) noexcept(true) {
  fd_set read_fds, write_fds;
  FD_ZERO(&read_fds);
  FD_ZERO(&write_fds);
  // a data structure used by the select() function to represent a set of
  // file descriptors. In this case, read_fds is used to represent
  // the set of file descriptors that should be monitored for reading,
  // while write_fds is used to represent the set of file descriptors
  // that should be monitored for writing.
  if (error == SSL_ERROR_WANT_READ) {
    FD_SET(this->idSocket, &read_fds);
  } else {
    FD_SET(this->idSocket, &write_fds);
  }
  // Wait for the socket to become ready (you can also set a timeout if
  // needed)
  int select_result =
      select(this->idSocket + 1, &read_fds, &write_fds, nullptr, nullptr);
  return select_result;
}

void Socket::SSLStartLibrary() {
  SSL_library_init();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();
}

const char *Socket::SSLGetCipher() {
  // Call SSL_get_cipher() and return the name
  if (this->SSLStruct != nullptr) {
    return SSL_get_cipher(this->SSLStruct);
  } else {
    throw SocketException("Error getting cipher", "Socket::SSLGetCipher");
  }
}