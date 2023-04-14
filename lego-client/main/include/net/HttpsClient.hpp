// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>
#include <sstream>

#include "./net/socket/Ipv4SslSocket.hpp"

class HttpsClient {
public:
    [[nodiscard]] std::string get(const std::string &host, const std::string &resource) const;

private:
    static constexpr char GET[]{"GET "};
    static constexpr char CRLF[]{"\r\n"};
    static constexpr char HOST[]{"Host: "};
    static constexpr char HTTPS[]{"https"};
};
