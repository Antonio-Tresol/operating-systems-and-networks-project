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
 * RAII wrapper for SSL*
 */
class SslPtr {
 public:
  explicit SslPtr(SSL_CTX *ctx);

  ~SslPtr();

  /**
   * Object is meant to be unique.
   */
  SslPtr(const SslPtr &) = delete;
  SslPtr &operator=(const SslPtr &) = delete;

  explicit operator SSL *() const;

 private:
  SSL *ssl;
};
