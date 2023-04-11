// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>

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
