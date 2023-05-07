// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/socket/Ipv4SslSocket.hpp"
#include "common/Logger.hpp"

using ::SSL_connect;
using ::SSL_CTX_new;
using ::SSL_free;
using ::SSL_new;
using ::SSL_set_fd;
using ::SSL_shutdown;
using ::SSL_read;
using ::SSL_write;
using ::TLS_client_method;

using std::runtime_error;
using std::string;


Ipv4SslSocket::Ipv4SslSocket() {
  if (-1 == socketFd) {
    throw runtime_error(appendErr("Ipv4SslSocket::Ipv4SslSocket: Failed to create socket: "));
  }
  this->sslContext.setCtx(SSL_CTX_new(TLS_client_method()));
  this->ssl.startSsl(static_cast<SSL_CTX *>(this->sslContext));
  this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
}

Ipv4SslSocket::Ipv4SslSocket(std::string certFilePath, int port = 7777) {
  if (-1 == socketFd) {
    throw runtime_error(appendErr("Ipv4SslSocket::Ipv4SslSocket: Failed to create socket: "));
  }
  try {
    this->sslContext.setCtx(SSL_CTX_new(TLS_client_method()));
    this->loadCertificates(certFilePath);
    this->sslBind(7777);
    this->sslListen(SOMAXCONN);
  } catch (const std::exception &e) {
    throw e;
  }

}

Ipv4SslSocket::Ipv4SslSocket(int socketFd) : socketFd(socketFd) {}

Ipv4SslSocket::~Ipv4SslSocket() {
  close(socketFd);
}

void Ipv4SslSocket::sslCreate(SSL_CTX *parentContext) {
  this->sslContext.setCtx(ctx);
  try {
    this->ssl.startSsl(static_cast<SSL_CTX *>(this->sslContext));
  } catch (const std::exception &e) {
    throw e;
  }
}

void Ipv4SslSocket::sslConnect(const string &host, const string &service) const {
  tcpConnect(host, service);

  int st{SSL_set_fd(static_cast<SSL *>(this->ssl), this->socketFd)};
  if (!st) {
    throw runtime_error(appendSslErr("Ipv4SslSocket::sslConnect: Failed to set SSL socket: "));
  }

  st = SSL_connect(static_cast<SSL *>(this->ssl));
  if (0 >= st) {
    throw runtime_error(appendSslErr("Ipv4SslSocket::sslConnect: Failed to connect socket: "));
  }
}

string Ipv4SslSocket::sslRead() {
  string output{};

  if (isReadReady()) {
    char buf[CHUNK_SIZE]{};
    int bytesRead;

    do {
      bytesRead = SSL_read(static_cast<SSL *>(this->ssl),
        static_cast<void *>(buf), CHUNK_SIZE);

      if (0 > bytesRead) {
        int sslError{SSL_get_error(static_cast<SSL *>(this->ssl), bytesRead)};
        if (sslError == SSL_ERROR_WANT_READ || sslError == SSL_ERROR_WANT_WRITE) {
          continue;
        } else {
            throw runtime_error(
              appendSslErr("Ipv4SslSocket::sslRead: Failed to read from socket: "));
        }
      }

      output.append(buf, bytesRead);
    } while (bytesRead > 0);
  }

  return output;
}

void Ipv4SslSocket::sslWrite(const string &text) const {
  int st{SSL_write(static_cast<SSL *>(this->ssl),
                   static_cast<const void *>(text.c_str()),
                   static_cast<int>(text.size()))};
  if (0 >= st) {
    int sslError{SSL_get_error(static_cast<SSL *>(this->ssl), st)};
    if (sslError == SSL_ERROR_WANT_READ || sslError == SSL_ERROR_WANT_WRITE) {
      sslWrite(text);
    } else {
      throw runtime_error(appendSslErr("Ipv4SslSocket::sslWrite: Failed to write to socket: "));
    }
  }
}

string Ipv4SslSocket::appendErr(const string &message) {
  return message + string(strerror(errno));
}

string Ipv4SslSocket::appendSslErr(const string &message) {
  uint64_t err{ERR_get_error()};

  const char *buf{ERR_reason_error_string(err)};

  string output{message};

  if (buf) {
    output += buf;
  } else {
    output += "NULL";
  }

  return output;
}

void Ipv4SslSocket::tcpConnect(const string &host, const string &service) const {
  struct addrinfo *result;

  int st = getaddrinfo(host.c_str(), service.c_str(), &hints, &result);
  if (0 != st) {
    throw runtime_error("Ipv4SslSocket::tcpConnect: Failed to get address info: " + string(gai_strerror(st)));
  }

  for (struct addrinfo *rp{result}; rp; rp = rp->ai_next) {
    if (0 == connect(socketFd, rp->ai_addr, rp->ai_addrlen))
      break;
  }

  freeaddrinfo(result);
}

bool Ipv4SslSocket::isReadReady() {
  // Clear the fd_set
  FD_ZERO(&read_fds);

  // Add the socket file descriptor to the set
  FD_SET(socketFd, &read_fds);

  // Set a timeout (optional)
  timeout.tv_sec = 5; // 5 seconds
  timeout.tv_usec = 0;

  int select_result{select(socketFd + 1, &read_fds, nullptr, nullptr, &timeout)};
  if (0 > select_result) {
    throw runtime_error(appendErr("Ipv4SslSocket::isReadReady: Failed to select read_fds: "));
  }

  return select_result > 0 && FD_ISSET(socketFd, &read_fds);
}


void Ipv4SslSocket::sslAccept() noexcept(false) {
  while (true) {
    // Call SSL_accept() to initiate TLS/SSL handshake
    int result = SSL_accept(static_cast<SSL*>(this->ssl));
    if (result > 0) {
      // Handshake succeeded
      break;
    }
    int error = SSL_get_error(static_cast<SSL*>(this->ssl), result);
    // Handle the error based on the specific SSL error code
    switch (error) {
    // ssl_error_want_read and ssl_error_want_write are not errors per se,
    // so we want to retry the call. Here we use a select() see if the
    // socket is ready for read/write
    case SSL_ERROR_WANT_READ:
    case SSL_ERROR_WANT_WRITE: {
      int readyToReadOrWrite = readyToReadWrite(error);
      if (readyToReadOrWrite < 0) {
        throw runtime_error(appendSslErr("Ipv4SslSocket::sslAccept: Error while waiting to read/write socket"));
      }
      // The socket is now ready, retry SSL_accept()
      continue;
    }
    case SSL_ERROR_ZERO_RETURN:
      // The TLS/SSL connection has been closed
      throw runtime_error(appendSslErr("Ipv4SslSocket::sslAccept: connection has been closed"));
    case SSL_ERROR_SYSCALL:
      // I/O error occurred; check errno for the specific error
      throw runtime_error(appendSslErr("Ipv4SslSocket::sslAccept: I/O error occurred"));
    default:
      // Other SSL errors
      throw runtime_error(appendSslErr("Ipv4SslSocket::sslAccept: Other SSL errors"));
    }
  }
}

void Ipv4SslSocket::sslListen(int backlog) noexcept(false) {
  int status = -1;
  // mark the socket as passive using system call listen
  status = listen(this->socketFd, backlog);
  if (-1 == status) {
    throw runtime_error(appendSslErr("Ipv4SslSocket::sslListen: Error listening to socket"));
  }
}

void Ipv4SslSocket::sslBind(int port) noexcept(false) {
  int status = -1;
  // prepare the address structure for the bind system call
  struct sockaddr_in hostIpv4;
  memset(&hostIpv4, 0, sizeof(hostIpv4));
  hostIpv4.sin_family = AF_INET;          // socket domain is IPv4
  hostIpv4.sin_addr.s_addr = INADDR_ANY;  //  bind to any address
  // htons converts the unsigned short integer host short from host byte order
  // to network byte order. For portable code, it is recommended to use htons
  // whenever you are using a number from host byte order in a context where
  // network byte order is expected.
  hostIpv4.sin_port = htons(port);  //  bind to port
  struct sockaddr *hostIpv4Ptr = reinterpret_cast<sockaddr *>(&hostIpv4);
  socklen_t hostIpv4Len = sizeof(hostIpv4);
  // bind the socket to the address and port number
  status = bind(socketFd, hostIpv4Ptr, hostIpv4Len);
  if (-1 == status) {
    throw runtime_error(appendSslErr("Ipv4SslSocket::sslBind: Error binding to socket IPV4"));
  }
}

int Ipv4SslSocket::readyToReadWrite(int error) noexcept(true) {
  fd_set read_fds, write_fds;
  FD_ZERO(&read_fds);
  FD_ZERO(&write_fds);
  // a data structure used by the select() function to represent a set of
  // file descriptors. In this case, read_fds is used to represent
  // the set of file descriptors that should be monitored for reading,
  // while write_fds is used to represent the set of file descriptors
  // that should be monitored for writing.
  if (error == SSL_ERROR_WANT_READ) {
    FD_SET(this->socketFd, &read_fds);
  } else {
    FD_SET(this->socketFd, &write_fds);
  }
  // Wait for the socket to become ready (you can also set a timeout if
  // needed)
  int select_result =
    select(this->socketFd + 1, &read_fds, &write_fds, nullptr, nullptr);
  return select_result;
}

void Ipv4SslSocket::SSLLoadCertificates(const char *certFileName, const char *keyFileName) {
  // set the local certificate from CertFileName
  int status = -1;
  status = SSL_CTX_use_certificate_file(static_cast<SSL_CTX*>(this->sslContext), certFileName,
                                        SSL_FILETYPE_PEM);
  if (status <= 0) {
    throw runtime_error(appendSslErr("Ipv4SslSocket::SSLoadCertificates: Error loading certificates"));

  // set the private key from KeyFileName (may be the same as CertFile)
  status = SSL_CTX_use_PrivateKey_file(static_cast<SSL_CTX*>(this->sslContext), keyFileName,
                                       SSL_FILETYPE_PEM);
  if (status <= 0) {
    throw runtime_error(appendSslErr("Ipv4SslSocket::SSLoadCertificates: Error loading private key"));
  }
  // verify private key
  status = SSL_CTX_check_private_key(static_cast<SSL_CTX*>(this->sslContext));
  if (!status) {
    throw runtime_error(appendSslErr("Ipv4SslSocket::SSLoadCertificates: Error verifying private key"));
  }
}


Ipv4SslSocket* Ipv4SslSocket::Accept() {
  int newSocketFd = -1;
  // sockaddr_storage is large enough to hold both IPv4 and IPv6 structures
  struct sockaddr_storage clientAddr;
  memset(&clientAddr, 0, sizeof(clientAddr));
  struct sockaddr *clientAddrPtr = reinterpret_cast<sockaddr *>(&clientAddr);
  socklen_t clientAddrLen = sizeof(clientAddr);
  // accept a connection on a socket
  newSocketFd = accept(this->idSocket, clientAddrPtr, &clientAddrLen);
  if (newSocketFd < 0) {
    throw runtime_error(appendSslErr("Ipv4SslSocket::Accept: Error accepting connection"));
  }
  Ipv4SslSocket *newSocket = new Ipv4SslSocket(newSocketFd);
  return newSocket;
}
