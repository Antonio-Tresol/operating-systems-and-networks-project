// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.

#pragma once

#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>    // for inet_pton
#include <sys/types.h>    // for connect
#include <sys/socket.h>
#include <openssl/ssl.h>
#include <cstddef>
#include <cstdio>    // for perror
#include <cstdlib>    // for exit
#include <cstring>    // for memset
#include <cerrno>
#include <string>

#include "./SslCtxPtr.hpp"
#include "./SslPtr.hpp"

/**
 *
 */

class Ipv4SslSocket {

public:
    /**
     * Constructor.
     *
     * Checks initialized values are valid.
     */
    Ipv4SslSocket();

    /**
     * Destructor.
     *
     * Closes SSL and TCP connections.
     */
    ~Ipv4SslSocket();

    /**
     * Object is meant to be unique.
     */
    Ipv4SslSocket(const Ipv4SslSocket &) = delete;

    Ipv4SslSocket &operator=(const Ipv4SslSocket &) = delete;

    void sslConnect(const std::string &host, const std::string &service) const;

    [[nodiscard]] std::string sslRead();

    void sslWrite(const std::string &text) const;

private:
    static constexpr int TCP_ID{6};
    static constexpr int64_t MAX_SIZE{4096};
    static constexpr struct addrinfo hints{
            0,
            AF_UNSPEC,
            SOCK_STREAM,
            0,
            0,
            nullptr,
            nullptr,
            nullptr
    };

    /**
     * Appends the current C error to the input message.
     * @param message message to append the error
     * @return concatenation of message and error
     */
    static std::string appendErr(const std::string &message);

    /**
      * tcpConnect method
      *
      * @param	char * host: host address in dot notation, example "163.178.104.187"
      * @param	char * service: service name, example "http"
      *
     **/
    void tcpConnect(const std::string &host, const std::string &service) const;

    /**
     *
     * @return
     */
    bool isReadReady();

    int socketFd{socket(AF_INET, SOCK_STREAM, TCP_ID)};
    fd_set read_fds{};
    struct timeval timeout{5, 0};
    SslCtxPtr sslContext{};
    SslPtr ssl{static_cast<SSL_CTX *>(this->sslContext)};
};

// TODO(aarevalo): Exception class. Deeper handling of system call responses.

Ipv4SslSocket::Ipv4SslSocket() {
    if (-1 == socketFd) {
        throw std::runtime_error(appendErr("Ipv4SslSocket::Ipv4SslSocket: Failed to create socket: "));
    }
}

Ipv4SslSocket::~Ipv4SslSocket() {
    close(socketFd);
}


void Ipv4SslSocket::sslConnect(const std::string &host, const std::string &service) const {
    tcpConnect(host, service);

    if (!SSL_set_fd(static_cast<SSL *>(this->ssl), this->socketFd)) {
        throw std::runtime_error(appendErr("Ipv4SslSocket::sslConnect: Failed to set SSL socket: "));
    }

    if (0 >= SSL_connect(static_cast<SSL *>(this->ssl))) {
        throw std::runtime_error(appendErr("Ipv4SslSocket::sslConnect: Failed to connect socket: "));
    }
}

std::string Ipv4SslSocket::sslRead() {
    char buf[MAX_SIZE]{0};
    char *current{buf};
    int toRead{MAX_SIZE - 1};
    int bytesRead{1};

    while (toRead && bytesRead) {
        if (isReadReady()) {
            bytesRead = SSL_read(static_cast<SSL *>(this->ssl),
                                 static_cast<void *>(current),
                                 toRead);
            if (0 > bytesRead) {
                throw std::runtime_error(appendErr("Ipv4SslSocket::sslRead: Failed to read from socket: "));
            }

            current = &current[bytesRead];
            *current = '\n';
            ++current;

            toRead -= bytesRead;
        }
    }

    *current = '\0';

    return std::string{buf};
}

void Ipv4SslSocket::sslWrite(const std::string &text) const {
    if (0 >= SSL_write(static_cast<SSL *>(this->ssl),
                       static_cast<const void *>(text.c_str()),
                       static_cast<int>(text.size()))) {
        throw std::runtime_error(appendErr("Ipv4SslSocket::sslWrite: Failed to write to socket: "));
    }
}

std::string Ipv4SslSocket::appendErr(const std::string &message) {
    return message + std::string(strerror(errno));
}

void Ipv4SslSocket::tcpConnect(const std::string &host, const std::string &service) const {
    struct addrinfo *result;

    if (0 != getaddrinfo(host.c_str(), service.c_str(), &hints, &result)) {
        throw std::runtime_error(appendErr("Ipv4SslSocket::tcpConnect: Failed to get address info: "));
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
        throw std::runtime_error(appendErr("Ipv4SslSocket::isReadReady: Failed to select read_fds: "));
    }

    return select_result > 0 && FD_ISSET(socketFd, &read_fds);
}
