// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.

#include <iostream>
#include <stdexcept>
#include <openssl/ssl.h>
#include <openssl/err.h>

/**
 * RAII wrapper for SSL_CTX*
 */
class SslCtxPtr {
public:
    SslCtxPtr();

    ~SslCtxPtr();

    /**
     * Object is meant to be unique.
     */
    SslCtxPtr(const SslCtxPtr &) = delete;
    SslCtxPtr& operator=(const SslCtxPtr&) = delete;


    explicit operator SSL_CTX*() const {
        return ctx;
    }

private:
    SSL_CTX* ctx{SSL_CTX_new(TLS_client_method())};
};

SslCtxPtr::SslCtxPtr() {
    if (!ctx) {
        throw std::runtime_error("Failed to create SSL_CTX");
    }
}

SslCtxPtr::~SslCtxPtr() {
    if (ctx) {
        SSL_CTX_free(ctx);
    }
}


