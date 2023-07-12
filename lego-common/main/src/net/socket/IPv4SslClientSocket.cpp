// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include <arpa/inet.h>    // for inet_pton
#include <sys/socket.h>
#include <openssl/ssl.h>
#include <unistd.h>

#include <cstdio>    // for perror
#include <cstdlib>    // for exit
#include <cstring>    // for memset
#include <iostream>
#include <stdexcept>
#include <openssl/err.h>

#include "./net/socket/IPv4SslClientSocket.hpp"

namespace Sys {
    using ::close;
    using ::connect;
}

using std::runtime_error;
using std::string;

IPv4SslClientSocket::IPv4SslClientSocket() : socketFD(socket(AF_INET, SOCK_STREAM, 0)) {
    if (-1 == socketFD) {
        throw runtime_error(appendErr(
                "IPv4SslClientSocket::IPv4SslClientSocket: Failed to create listener socket: "));
    }

    const SSL_METHOD *method = TLS_client_method();
    if (method == nullptr) {
        throw runtime_error(
                appendSslErr("IPv4SslClientSocket::IPv4SslClientSocket: Failed to create SSL_METHOD: "));
    }
    SSL_CTX *ctx = SSL_CTX_new(method);
    if (ctx == nullptr) {
        throw runtime_error(
                appendSslErr("IPv4SslClientSocket::IPv4SslClientSocket: Failed to create SSL_CTX: "));
    }
    this->SSLContext = ctx;

    SSL *ssl = SSL_new((SSL_CTX *) this->SSLContext);
    if (ssl == nullptr) {
        throw runtime_error("Failed to create SSL");
    }
    this->SSLStruct = ssl;
}

IPv4SslClientSocket::~IPv4SslClientSocket() {
    if (SSLStruct) {
        SSL_shutdown(SSLStruct);
        SSL_free(SSLStruct);
    }

    if (SSLContext) {
        SSL_CTX_free(SSLContext);
    }

    close();
}

void IPv4SslClientSocket::close() const {
    Sys::close(socketFD);
}


void IPv4SslClientSocket::connect(const string &host, int port) const {
    struct sockaddr_in hostIpv4{};

    hostIpv4.sin_family = AF_INET;

    int status = inet_pton(AF_INET, host.c_str(), &hostIpv4.sin_addr);

    if (status == 0) {
        throw runtime_error(
                appendErr("IPv4SslClientSocket::connect: Invalid IPv4 address: "));
    } else if (status == -1) {
        throw runtime_error(
                appendErr("IPv4SslClientSocket::connect: Error converting IPv4 address: "));
    }

    hostIpv4.sin_port = htons(port);

    auto *hostIpv4Ptr = reinterpret_cast<struct sockaddr *>(&hostIpv4);

    socklen_t hostIpv4Len = sizeof(hostIpv4);

    status = Sys::connect(socketFD, hostIpv4Ptr, hostIpv4Len);
    if (status == -1) {
        throw runtime_error(
                appendErr("IPv4SslClientSocket::connect: Invalid IPv4 address: "));
    }
}

void IPv4SslClientSocket::sslConnect(std::string host, int port) {
    connect(host, port);

    if (!SSL_set_fd(SSLStruct, socketFD)) {
        throw runtime_error(appendErr(
                "IPv4SslClientSocket::sslConnect: Failed to set socket to SSL: "));
    }

    if (0 >= SSL_connect(SSLStruct)) {
        throw runtime_error(
                appendSslErr("IPv4SslClientSocket::sslConnect: Failed to connect socket: "));
    }
}

string IPv4SslClientSocket::sslRead() {
    string output{};

    char buf[CHUNK_SIZE]{};
    int bytesRead;

    do {
        if (isReadReady()) {
            bytesRead = SSL_read(SSLStruct,static_cast<void *>(buf), CHUNK_SIZE);

            if (0 > bytesRead) {
                int sslError{SSL_get_error(SSLStruct, bytesRead)};
                if (sslError == SSL_ERROR_WANT_READ ||
                    sslError == SSL_ERROR_WANT_WRITE) {
                    continue;
                } else {
                    throw runtime_error(appendSslErr(
                            "IPv4SslClientSocket::sslRead: Failed to read from socket: "));
                }
            }

            output.append(buf, bytesRead);
        } else {
            bytesRead = 0;
        }
    } while (bytesRead > 0);

    return output;
}

void IPv4SslClientSocket::sslWrite(const std::string text) const {
    int st{SSL_write(SSLStruct, static_cast<const void *>(text.c_str()), static_cast<int>(text.size()))};
    if (0 >= st) {
        int sslError{SSL_get_error(SSLStruct, st)};
        if (sslError == SSL_ERROR_WANT_READ || sslError == SSL_ERROR_WANT_WRITE) {
            sslWrite(text);
        } else {
            throw runtime_error(
                    appendSslErr("IPv4SslSocket::sslWrite: Failed to write to socket: "));
        }
    }
}

bool IPv4SslClientSocket::isReadReady() {
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

string IPv4SslClientSocket::appendErr(const string &message) const {
    return message + string(strerror(errno));
}

string IPv4SslClientSocket::appendSslErr(const string &message) const {
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