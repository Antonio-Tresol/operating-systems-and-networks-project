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
    static constexpr char GET[]{"GET / HTTP/1.1\r\n"};
    static constexpr char HOST[]{"Host: "};
    static constexpr char CRLF[]{"\r\n\r\n"};
    static constexpr char HTTPS[]{"https"};
};

std::string HttpsClient::get(const std::string &url, const std::string &host) const {
    try {
        Ipv4SslSocket socket{};

        socket.sslConnect(url, HTTPS);

        const std::string request{std::string{GET} + HOST + host + CRLF};

        socket.sslWrite(request);

        return socket.sslRead();
    } catch (std::exception const &e) {
        // TODO: Catch retryable
        // std::throw_with_nested(CustomException("Error in outerFunction"));
    }
}
