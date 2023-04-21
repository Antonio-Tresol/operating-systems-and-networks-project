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
}

Ipv4SslSocket::~Ipv4SslSocket() {
    close(socketFd);
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
                                 static_cast<void *>(buf),
                                 CHUNK_SIZE);

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
