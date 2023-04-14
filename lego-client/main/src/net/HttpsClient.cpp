// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/HttpsClient.hpp"

using std::exception;
using std::runtime_error;
using std::string;

string HttpsClient::get(const std::string &host, const std::string &resource) const {
    try {
        Ipv4SslSocket socket{};

        socket.sslConnect(host, HTTPS);

        const string request{string{GET} + resource + CRLF + HOST + host + CRLF + CRLF};

        socket.sslWrite(request);

        string response{socket.sslRead()};

        return response;
    } catch (exception const &e) {
        throw_with_nested(runtime_error("Failed to GET from: " + resource));
    }
}
