// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <string>

#include "net/Ipv4SslSocket.hpp"

class HttpsClient {
public:
    std::string get(const std::string &url, const std::string &host);
private:
    static const std::string GET;
    static const std::string HOST;
    static const std::string CRLF;
};

const std::string HttpsClient::GET{"GET / HTTP/1.1\r\n"};
const std::string HttpsClient::HOST{"Host: "};
const std::string HttpsClient::CRLF{"\r\n\r\n"};

std::string HttpsClient::get(const std::string &url, const std::string &host) {
    Ipv4SslSocket s('s', false);    // Create a new stream socket for IPv4
    char a[SIZE];
    int count;

    // TODO: Check if const char[] can be <<'d to change constants into constexpr

    memset(a, 0, SIZE);
    s.init();
    s.sslConnect(os, (char *) "https");
    s.sslWrite((void *) GET);
    while ((count = s.sslRead()) > 0)
    {
        printf("%s\n", a);
        memset(a, 0, SIZE);
    }
    return a; // TODO: Memory
}
