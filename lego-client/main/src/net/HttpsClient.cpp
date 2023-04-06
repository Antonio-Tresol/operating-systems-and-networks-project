// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#include "../include/net/HttpsClient.hpp"

using std::exception;
using std::string;

string HttpsClient::get(const string &url, const string &host) const {
    try {
        Ipv4SslSocket socket{};

        socket.sslConnect(url, HTTPS);

        const string request{string{GET} + HOST + host + CRLF};

        socket.sslWrite(request);

        return socket.sslRead();
    } catch (exception const &e) {
        // TODO(Ariel): Catch retryable
        // std::throw_with_nested(CustomException("Error in outerFunction"));
        throw e;
    }
}
