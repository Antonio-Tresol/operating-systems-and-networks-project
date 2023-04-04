// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.

#pragma once

#include <cstddef>
#include <unistd.h>
#include <cstdio>    // for perror
#include <cstdlib>    // for exit
#include <cstring>    // for memset
#include <cerrno>
#include <netdb.h>
#include <arpa/inet.h>    // for inet_pton
#include <sys/types.h>    // for connect
#include <sys/socket.h>
#include <openssl/ssl.h>

#include "SslCtxPtr.hpp"
#include "SslPtr.hpp"


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
    Ipv4SslSocket& operator=(const Ipv4SslSocket&) = delete;

    void sslConnect(const std::string &host, const std::string &service) const;

    [[nodiscard]] std::string sslRead() const;

    void sslWrite(const std::string& text) const;

private:
    static std::string appendErr(const std::string &message);

    static constexpr int TCP_ID{6};
    static constexpr int MAX_SIZE{4096};
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
      * tcpConnect method
      *
      * @param	char * host: host address in dot notation, example "163.178.104.187"
      * @param	char * service: service name, example "http"
      *
     **/
    void tcpConnect(const std::string &host, const std::string &service) const;

    int socketId{socket(AF_INET, SOCK_STREAM, TCP_ID)};

    SslCtxPtr sslContext;
    SslPtr ssl{(SSL_CTX *) this->sslContext};
};

// TODO(aarevalo): Exception class.

Ipv4SslSocket::Ipv4SslSocket() {
    if (-1 == socketId) {
        throw std::runtime_error(appendErr("Failed to create socket: "));
    }
}

Ipv4SslSocket::~Ipv4SslSocket() {
    close(socketId);
}


void Ipv4SslSocket::sslConnect(const std::string &host, const std::string &service) const {
    tcpConnect(host, service);
    SSL_set_fd((SSL *) this->ssl, this->socketId);

    if (0 >= SSL_connect((SSL *) this->ssl)) {
        throw std::runtime_error(appendErr("Failed to connect socket: "));
    }
}

std::string Ipv4SslSocket::sslRead() const {
    char buf[MAX_SIZE];
    if (0 >= SSL_read((SSL *) ssl, (void *) buf, MAX_SIZE)) {
        throw std::runtime_error(appendErr("Failed to read from socket: "));
    }
    return std::string{buf};
}

void Ipv4SslSocket::sslWrite(const std::string& text) const {
    if (0 >= SSL_write((SSL *) ssl, (void *) text.c_str(), (int) text.size())) {
        throw std::runtime_error(appendErr("Failed to write to socket: "));
    }
}

void Ipv4SslSocket::tcpConnect(const std::string &host, const std::string &service) const {
    struct addrinfo *result;

    if (0 != getaddrinfo(host.c_str(), service.c_str(), &hints, &result)) {
        throw std::runtime_error(appendErr("Failed to get address info: "));
    }

    for (struct addrinfo *rp{result}; rp; rp = rp->ai_next) {
        if (0 == connect(socketId, rp->ai_addr, rp->ai_addrlen))
            break;
    }

    freeaddrinfo(result);
}

std::string Ipv4SslSocket::appendErr(const std::string &message) {
    return message + std::string(strerror(errno));
}
