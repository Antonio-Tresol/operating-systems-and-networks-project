// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <openssl/ssl.h>

#include <string>

/**
 * @brief A socket to connect via IPv4 over TCP over SSL.
 */
class IPv4SslClientSocket {

public:
    /**
     * Client constructor.
     */
    IPv4SslClientSocket();

    /**
     * Destructor.
     *
     * Closes object socket.
     */
    ~IPv4SslClientSocket();

    /**
     * @brief Establishes a TCP connection.
     * @param host Host to connect to.
     * @param port Port over which to connect.
     */
    void connect(const std::string &host, int port ) const;


    void close() const;

    /**
     * @brief Establishes a TCP connection over SSL.
     * @param host Host to connect to.
     * @param port Port over which to connect.
     */
    void sslConnect(std::string host, int port );

    /**
     * @brief Reads from a TCP connection over SSL.
     * @return Response returned by connection.
     */
    std::string sslRead();

    /**
     * @brief Writes to a TCP connection over SSL.
     * @param text Content to write to connection.
     */
    void sslWrite(const std::string text) const;

private:
    static constexpr int64_t CHUNK_SIZE{512};

    int socketFD;
    SSL_CTX * SSLContext;	// SSL context
    SSL * SSLStruct;	// SSL BIO basis input output

    fd_set read_fds{};
    struct timeval timeout{
            5, 0
    };

    bool isReadReady();

    [[nodiscard]] std::string appendErr(const std::string &message) const;

    std::string appendSslErr(const std::string &message) const;
};
