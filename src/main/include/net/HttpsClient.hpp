// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <string>
#include <sstream>

#include "net/socket/Ipv4SslSocket.hpp"

class HttpsClient {
public:
    [[nodiscard]] std::string get(const std::string &url, const std::string &host) const;
private:
    static const std::string GET;
    static const std::string HOST;
    static const std::string CRLF;
    static const std::string HTTPS;
};

const std::string HttpsClient::GET{"GET / HTTP/1.1\r\n"};
const std::string HttpsClient::HOST{"Host: "};
const std::string HttpsClient::CRLF{"\r\n\r\n"};
const std::string HttpsClient::HTTPS{"https"};

std::string HttpsClient::get(const std::string &url, const std::string &host) const {
    Ipv4SslSocket socket{};

    socket.sslConnect(url, HTTPS);

    const std::string request{GET + HOST + host + CRLF};

    socket.sslWrite(request);

    return socket.sslRead();
}
