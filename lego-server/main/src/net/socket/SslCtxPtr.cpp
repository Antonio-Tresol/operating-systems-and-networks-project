// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/socket/SslCtxPtr.hpp"

using std::runtime_error;

SslCtxPtr::SslCtxPtr() {
    ctx = SSL_CTX_new(TLS_client_method());
    if (!ctx) {
        throw runtime_error("Failed to create SSL_CTX");
    }
}
void SslCtxPtr::setCtx(SSL_CTX *ctx){
    this->ctx = ctx;
}

SslCtxPtr::SslCtxPtr() noexcept {
}

SslCtxPtr::~SslCtxPtr() {
    if (ctx) {
        SSL_CTX_free(ctx);
    }
}


