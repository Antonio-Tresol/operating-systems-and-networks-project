#ifndef SOCKET_H
#define SOCKET_H

#include <openssl/ssl.h>
#include <openssl/err.h>

class Socket {
public:
    Socket(int family, int sockType);

    Socket(int family, int sockType, SSL* ssl, SSL_CTX* sslCtx);

    int family;
    int sockType;

    bool isSsl{false};

    SSL* ssl{nullptr};
    SSL_CTX* sslCtx{nullptr};
};

#endif //SOCKET_H
