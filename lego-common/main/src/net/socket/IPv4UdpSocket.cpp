// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "./net/socket/IPv4UdpSocket.hpp"
#include "net/Timeout.hpp"

namespace Sys {
using ::bind;
using ::close;
using ::recv;
using ::sendto;
}  // namespace Sys

using std::runtime_error;
using std::string;

IPv4UdpSocket::IPv4UdpSocket(int port)
    : socketFD(socket(AF_INET, SOCK_DGRAM, UDP_ID)), port(port) {
  if (-1 == socketFD) {
    throw runtime_error(
        appendErr("IPv4UdpSocket::IPv4UdpSocket: Failed to create socket: "));
  }

  int broadcastEnable = 1;

  if (-1 == setsockopt(socketFD, SOL_SOCKET, SO_BROADCAST, &broadcastEnable,
                       sizeof(broadcastEnable))) {
    throw runtime_error(
        appendErr("IPv4UdpSocket::IPv4UdpSocket: Failed to set broadcast: "));
  }

    struct timeval timeout{1, 500000};

    if (-1 == setsockopt(socketFD, SOL_SOCKET, SO_RCVTIMEO, &timeout,
                         sizeof(timeout))) {
        throw runtime_error(
                appendErr("IPv4UdpSocket::IPv4UdpSocket: Failed to set timeout: "));
    }
}

IPv4UdpSocket::~IPv4UdpSocket() { Sys::close(socketFD); }

void IPv4UdpSocket::close() const { Sys::close(socketFD); };

void IPv4UdpSocket::bind() const {
  struct sockaddr_in host4 {
    AF_INET, htons(port), INADDR_ANY
  };

  if (-1 == Sys::bind(socketFD, reinterpret_cast<sockaddr *>(&host4),
                      sizeof(host4))) {
    throw runtime_error(appendErr("IPv4UdpSocket::bind: "));
  }
}

void IPv4UdpSocket::send(const string &text, const string &address) const {
  struct sockaddr_in host4 {
    AF_INET, htons(port)
  };

  inet_pton(AF_INET, address.c_str(), &(host4.sin_addr));

  if (-1 == Sys::sendto(socketFD, text.c_str(), text.size(), NONE,
                        reinterpret_cast<sockaddr *>(&host4), sizeof(host4))) {
    throw runtime_error(appendErr("IPv4UdpSocket::send: "));
  }
}

string IPv4UdpSocket::receive() const {
  char buf[CHUNK_SIZE]{};

  if (-1 == recv(socketFD, static_cast<void *>(buf), CHUNK_SIZE, NONE)) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        throw Timeout{};
      }
    throw runtime_error(appendErr("IPv4UdpSocket::receive: "));
  }

  return string{buf};
}