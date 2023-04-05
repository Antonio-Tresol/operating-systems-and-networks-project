// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.

#include <iostream>
#include <stdexcept>
#include <openssl/ssl.h>
#include <openssl/err.h>

/**
 * RAII wrapper for SSL*
 */
class SslPtr {
public:
    explicit SslPtr(SSL_CTX* ctx) : ssl(SSL_new(ctx)) {
        if (!ssl) {
            throw std::runtime_error("Failed to create SSL");
        }
    }

    ~SslPtr();

    /**
     * Object is meant to be unique.
     */
    SslPtr(const SslPtr &) = delete;
    SslPtr& operator=(const SslPtr&) = delete;

    explicit operator SSL*() const {
        return ssl;
    }

private:
    SSL* ssl;
};

SslPtr::~SslPtr() {
    if (ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }
}
