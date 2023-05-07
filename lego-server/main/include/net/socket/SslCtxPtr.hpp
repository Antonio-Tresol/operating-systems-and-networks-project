// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <iostream>
#include <stdexcept>

/**
 * RAII wrapper for SSL_CTX*
 */
class SslCtxPtr {
 public:
  SslCtxPtr();
  SslCtxPtr();

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
  SSL_CTX *ctx{};
};
