// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>

#pragma once

#include <string>
#include <sstream>

#include "./net/socket/Ipv4SslSocket.hpp"

class HttpsClient {
public:
    [[nodiscard]] std::string get(const std::string &url, const std::string &host) const;

private:
    static constexpr char GET[]{"GET / HTTP/1.1\r\n"};
    static constexpr char HOST[]{"Host: "};
    static constexpr char CRLF[]{"\r\n\r\n"};
    static constexpr char HTTPS[]{"https"};
};
