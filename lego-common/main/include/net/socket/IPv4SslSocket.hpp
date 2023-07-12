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
#include <memory>
#include <sstream>
#include <string>

#include "./SslCtxPtr.hpp"
#include "./SslPtr.hpp"

/**
 * @brief A socket to connect via IPv4 over TCP over SSL.
 */
class IPv4SslSocket {
public:

    /**
     * Client constructor.
     */
    IPv4SslSocket();

    /**
     * Listener Constructor.
     *
     * Checks initialized socket is valid.
     */
    IPv4SslSocket(const std::string &certFileName,
                  const std::string &keyFileName);

    /**
     * Client Constructor.
     *
     * Sets new SSL to new FD
     */
    IPv4SslSocket(int socketFD, const IPv4SslSocket *original);

    /**
     * Destructor.
     *
     * Closes object socket.
     */
    ~IPv4SslSocket();

    /**
     * Object is meant to be unique.
     */
    IPv4SslSocket(const IPv4SslSocket &) = delete;

    IPv4SslSocket &operator=(const IPv4SslSocket &) = delete;

    /**
     * @brief Binds socket to given port.
     * @param port Port to bind to.
     */
    void bind(int port) const;

    /**
     * @brief Sets socket to listen with a given queue size.
     * @param queueSize Size of listen queue.
     */
    void listen(int queueSize) const;

    /**
     * @brief Writes input text to socket.
     * @param text Text to write out.
     */
    void write(const std::string &text) const;

    /**
     * @brief Accepts a connection and hands it to a new socket.
     * @return Socket to new connection.
     */
    [[nodiscard]] std::shared_ptr<IPv4SslSocket> accept() const;

    void sslConnect(const std::string &host, int port) const;

    /**
     * @brief Establishes a TCP connection over SSL.
     * @param host Host to connect to.
     * @param service Service over which to connect.
     */
    void sslConnect(const std::string &host, const std::string &service) const;

    /**
     * @brief Performs an SSL handshake to confirm connection.
     */
    void sslAccept() const;

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

    [[nodiscard]] std::string getCerts() const;

    void close() const;

    int getSocketFD() const;

private:
    static constexpr int TCP_ID{6};
    static constexpr int64_t CHUNK_SIZE{512};
    static constexpr struct addrinfo hints{
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

    void connect(const std::string &host, int port) const;

    /**
     * @brief Establishes a TCP connection.
     * @param host Host to connect to.
     * @param service Service over which to connect.
     */
    void connect(const std::string &host, const std::string &service) const;


    /**
     * @brief Returns whether socket fd is ready to be read from.
     * @return Whether socket fd is ready to be read from.
     */
    bool isReadReady();

    int socketFD;
    fd_set read_fds{};
    struct timeval timeout{
            5, 0
    };
    SslCtxPtr sslContext{};
    SslPtr ssl{sslContext};
};
