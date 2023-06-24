// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/socket/IPv4SslSocket.hpp"

#include "./logging/Logger.hpp"

namespace Sys {
using ::accept;
using ::bind;
using ::connect;
using ::listen;
using ::write;
}  // namespace Sys

using ::SSL_connect;
using ::SSL_free;
using ::SSL_new;
using ::SSL_read;
using ::SSL_set_fd;
using ::SSL_shutdown;
using ::SSL_write;
using ::TLS_client_method;

using std::endl;
using std::ostringstream;
using std::runtime_error;
using std::shared_ptr;
using std::string;

IPv4SslSocket::IPv4SslSocket(const string &certFileName,
                             const string &keyFileName)
    : socketFD(socket(AF_INET, SOCK_STREAM, TCP_ID)),
      sslContext(certFileName, keyFileName),
      ssl(sslContext) {
  if (-1 == socketFD) {
    throw runtime_error(appendErr(
        "IPv4SslSocket::IPv4SslSocket: Failed to create listener socket: "));
  }
}

IPv4SslSocket::IPv4SslSocket(int socketFD, const IPv4SslSocket *original)
    : socketFD(socketFD), ssl(original->sslContext) {
  if (!SSL_set_fd(static_cast<SSL *>(ssl), socketFD)) {
    throw runtime_error(appendErr(
        "IPv4SslSocket::IPv4SslSocket: Failed to create client socket: "));
  }
}

IPv4SslSocket::~IPv4SslSocket() { close(socketFD); }

void IPv4SslSocket::connect(const string &host, const string &service) const {
  struct addrinfo *result;

  int st = getaddrinfo(host.c_str(), service.c_str(), &hints, &result);
  if (0 != st) {
    throw runtime_error("IPv4SslSocket::connect: Failed to get address info: " +
                        string(gai_strerror(st)));
  }

  for (struct addrinfo *rp{result}; rp; rp = rp->ai_next) {
    if (0 == Sys::connect(socketFD, rp->ai_addr, rp->ai_addrlen)) break;
  }

  freeaddrinfo(result);
}

void IPv4SslSocket::bind(int port) const {
  struct sockaddr_in host4 {
    AF_INET, htons(port), INADDR_ANY
  };

  if (-1 == Sys::bind(socketFD, reinterpret_cast<sockaddr *>(&host4),
                      sizeof(host4))) {
    throw runtime_error(appendErr("IPv4SslSocket::bind: "));
  }
}

void IPv4SslSocket::listen(int queueSize) const {
  if (-1 == Sys::listen(socketFD, queueSize)) {
    throw runtime_error(appendErr("IPv4SslSocket::listen: "));
  }
}

shared_ptr<IPv4SslSocket> IPv4SslSocket::accept() const {
  int newFD{Sys::accept(socketFD, nullptr, nullptr)};
  if (-1 == newFD) {
    throw runtime_error(appendErr("IPv4SslSocket::accept: "));
  }

  return std::make_shared<IPv4SslSocket>(newFD, this);
}

void IPv4SslSocket::write(const string &text) const {
  if (-1 == Sys::write(socketFD, text.c_str(), text.size())) {
    throw runtime_error(appendErr("IPv4SslSocket::write: "));
  }
}

void IPv4SslSocket::sslConnect(const string &host,
                               const string &service) const {
  connect(host, service);

  if (!SSL_set_fd(static_cast<SSL *>(this->ssl), this->socketFD)) {
    throw runtime_error(
        appendSslErr("IPv4SslSocket::sslConnect: Failed to set SSL socket: "));
  }

  if (0 >= SSL_connect(static_cast<SSL *>(this->ssl))) {
    throw runtime_error(
        appendSslErr("IPv4SslSocket::sslConnect: Failed to connect socket: "));
  }
}

void IPv4SslSocket::sslAccept() const {
  if (0 >= SSL_accept(static_cast<SSL *>(ssl))) {
    throw runtime_error(appendSslErr("IPv4SslSocket::sslAccept: "));
  }
}

string IPv4SslSocket::sslRead() {
  string output{};

  char buf[CHUNK_SIZE]{};
  int bytesRead;

  do {
    if (isReadReady()) {
      bytesRead = SSL_read(static_cast<SSL *>(this->ssl),
                           static_cast<void *>(buf), CHUNK_SIZE);

      if (0 > bytesRead) {
        int sslError{SSL_get_error(static_cast<SSL *>(this->ssl), bytesRead)};
        if (sslError == SSL_ERROR_WANT_READ ||
            sslError == SSL_ERROR_WANT_WRITE) {
          continue;
        } else {
          throw runtime_error(appendSslErr(
              "IPv4SslSocket::sslRead: Failed to read from socket: "));
        }
      }

      output.append(buf, bytesRead);
    } else {
      bytesRead = 0;
    }
  } while (bytesRead > 0);

  return output;
}

void IPv4SslSocket::sslWrite(const string &text) const {
  int st{SSL_write(static_cast<SSL *>(this->ssl),
                   static_cast<const void *>(text.c_str()),
                   static_cast<int>(text.size()))};
  if (0 >= st) {
    int sslError{SSL_get_error(static_cast<SSL *>(this->ssl), st)};
    if (sslError == SSL_ERROR_WANT_READ || sslError == SSL_ERROR_WANT_WRITE) {
      sslWrite(text);
    } else {
      throw runtime_error(
          appendSslErr("IPv4SslSocket::sslWrite: Failed to write to socket: "));
    }
  }
}

string IPv4SslSocket::getCerts() const {
  X509 *peerCertificates{SSL_get_certificate(static_cast<SSL *>(ssl))};

  if (!peerCertificates) {
    return "No certificates";
  }

  ostringstream out;
  out << "Server certificates:" << endl;

  char *subject =
      X509_NAME_oneline(X509_get_subject_name(peerCertificates), nullptr, 0);

  out << "Subject: " << subject << endl;

  char *issuer =
      X509_NAME_oneline(X509_get_issuer_name(peerCertificates), nullptr, 0);

  out << "Issuer: " << issuer << endl;

  OPENSSL_free(subject);
  OPENSSL_free(issuer);

  return out.str();
}

int IPv4SslSocket::getSocketFD() const { return socketFD; }

string IPv4SslSocket::appendErr(const string &message) {
  return message + string(strerror(errno));
}

string IPv4SslSocket::appendSslErr(const string &message) {
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

bool IPv4SslSocket::isReadReady() {
  // Clear the fd_set
  FD_ZERO(&read_fds);

  // Add the socket file descriptor to the set
  FD_SET(socketFD, &read_fds);

  // Set a timeout (optional)
  timeout.tv_sec = 0;  // 5 seconds
  timeout.tv_usec = 500000;

  int select_result{
      select(socketFD + 1, &read_fds, nullptr, nullptr, &timeout)};
  if (0 > select_result) {
    throw runtime_error(
        appendErr("IPv4SslSocket::isReadReady: Failed to select read_fds: "));
  }

  return select_result > 0 && FD_ISSET(socketFD, &read_fds);
}
