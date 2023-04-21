// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/socket/SslPtr.hpp"

using std::runtime_error;

SslPtr::SslPtr(SSL_CTX* ctx) : ssl(SSL_new(ctx)) {
    if (!ssl) {
        throw runtime_error("Failed to create SSL");
    }
}

SslPtr::~SslPtr() {
    if (ssl) {
        SSL_shutdown(ssl);
        SSL_free(ssl);
    }
}

SslPtr::operator SSL*() const {
    return ssl;
}
