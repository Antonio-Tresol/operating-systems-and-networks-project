// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.

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


