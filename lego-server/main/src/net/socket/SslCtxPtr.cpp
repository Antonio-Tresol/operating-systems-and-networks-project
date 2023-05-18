// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/socket/SslCtxPtr.hpp"

using std::runtime_error;
using std::string;

SslCtxPtr::SslCtxPtr() { // TODO(aarevalo): Risky shit. Split IPv4SslSocket into two classes if this doesn't work.
    const SSL_METHOD *method{TLS_server_method()};
    if (!method) {
        throw runtime_error(appendSslErr("SslCtxPtr::SslCtxPtr(): Failed to create SSL_METHOD: "));
    }

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        throw runtime_error(appendSslErr("SslCtxPtr::SslCtxPtr(): Failed to create SSL_CTX: "));
    }
}

SslCtxPtr::SslCtxPtr(const std::string &certPath, const std::string &keyPath) {

    SSL_library_init();

    OpenSSL_add_all_algorithms();

    SSL_load_error_strings();

    const SSL_METHOD *method{TLS_server_method()};
    if (!method) {
        throw runtime_error(appendSslErr("SslCtxPtr::SslCtxPtr(): Failed to create SSL_METHOD: "));
    }

    ctx = SSL_CTX_new(method);
    if (!ctx) {
        throw runtime_error(appendSslErr("SslCtxPtr::SslCtxPtr(): Failed to create SSL_CTX: "));
    }

    if (0 >= SSL_CTX_use_certificate_file(ctx, certPath.c_str(), SSL_FILETYPE_PEM)) {
        throw runtime_error(appendSslErr("SslCtxPtr::SslCtxPtr(): Failed to set certificate: "));
    }

    if (0 >= SSL_CTX_use_PrivateKey_file(ctx, keyPath.c_str(), SSL_FILETYPE_PEM)) {
        throw runtime_error(appendSslErr("SslCtxPtr::SslCtxPtr(): Failed to set private key: "));
    }

    if (!SSL_CTX_check_private_key(ctx)) {
        throw runtime_error(appendSslErr("SslCtxPtr::SslCtxPtr(): Failed to verify private key: "));
    }
}

void SslCtxPtr::setCtx(SSL_CTX *ctx) { this->ctx = ctx; }

SslCtxPtr::~SslCtxPtr() {
    if (ctx) {
        SSL_CTX_free(ctx);
    }
}

string SslCtxPtr::appendSslErr(const string &message) {
    uint64_t err{ERR_get_error()};

    const char *buf{ERR_reason_error_string(err)};

    string output{message};

    if (buf) {
        output += buf;
    } else {
        output += "NULL";
    }

    return output;
}
