// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.

#include "../include/net/socket/Ipv4SslSocket.hpp"

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

// TODO(aarevalo): Exception class. Deeper handling of system call responses.

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

    if (!SSL_set_fd(static_cast<SSL *>(this->ssl), this->socketFd)) {
        throw runtime_error(appendErr("Ipv4SslSocket::sslConnect: Failed to set SSL socket: "));
    }

    if (0 >= SSL_connect(static_cast<SSL *>(this->ssl))) {
        throw runtime_error(appendErr("Ipv4SslSocket::sslConnect: Failed to connect socket: "));
    }
}

string Ipv4SslSocket::sslRead() {
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
                throw runtime_error(appendErr("Ipv4SslSocket::sslRead: Failed to read from socket: "));
            }

            current = &current[bytesRead];
            *current = '\n';
            ++current;

            toRead -= bytesRead;
        }
    }

    *current = '\0';

    return string{buf};
}

void Ipv4SslSocket::sslWrite(const string &text) const {
    if (0 >= SSL_write(static_cast<SSL *>(this->ssl),
                       static_cast<const void *>(text.c_str()),
                       static_cast<int>(text.size()))) {
        throw runtime_error(appendErr("Ipv4SslSocket::sslWrite: Failed to write to socket: "));
    }
}

string Ipv4SslSocket::appendErr(const string &message) {
    return message + string(strerror(errno));
}

void Ipv4SslSocket::tcpConnect(const string &host, const string &service) const {
    struct addrinfo *result;

    if (0 != getaddrinfo(host.c_str(), service.c_str(), &hints, &result)) {
        throw runtime_error(appendErr("Ipv4SslSocket::tcpConnect: Failed to get address info: "));
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
