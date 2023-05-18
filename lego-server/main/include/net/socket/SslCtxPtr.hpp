// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>
#include <stdexcept>
#include <string>

/**
 * RAII wrapper for server SSL_CTX*
 */
class SslCtxPtr {
public:
    /**
     * @brief Constructs a new context.
     */
    SslCtxPtr();

    /**
     * @brief Constructs a context for a given certificate and key.
     * @param certPath Path to certificate to use.
     * @param keyPath Path to key to use.
     */
    SslCtxPtr(const std::string &certPath, const std::string &keyPath);

    ~SslCtxPtr();

    /**
     * Object is meant to be unique.
     */
    SslCtxPtr(const SslCtxPtr &) = delete;

    SslCtxPtr &operator=(const SslCtxPtr &) = delete;

    explicit operator SSL_CTX *() const {
        return ctx;
    }

    void setCtx(SSL_CTX *ctx);

private:
    /**
     * Appends the current SSL error to the input message.
     * @param message Message to append the error.
     * @return Concatenation of message and error
     */
    static std::string appendSslErr(const std::string &message);

    SSL_CTX *ctx{};
};
