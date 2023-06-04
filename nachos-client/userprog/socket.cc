#include "socket.h"

Socket::Socket(int family, int sockType) : family(family), sockType(sockType) {}

Socket::Socket(int family, int sockType, SSL *ssl, SSL_CTX *sslCtx) :
        family(family), sockType(sockType), isSsl(true), ssl(ssl), sslCtx(sslCtx) {}
