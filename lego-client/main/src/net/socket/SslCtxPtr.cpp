// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>

#include "../include/net/socket/SslCtxPtr.hpp"

using std::runtime_error;

SslCtxPtr::SslCtxPtr() {
    if (!ctx) {
        throw runtime_error("Failed to create SSL_CTX");
    }
}

SslCtxPtr::~SslCtxPtr() {
    if (ctx) {
        SSL_CTX_free(ctx);
    }
}


