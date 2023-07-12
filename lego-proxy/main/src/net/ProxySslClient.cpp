// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../../include/net/ProxySslClient.hpp"
#include "net/socket/IPv4SslClientSocket.hpp"

using std::exception;
using std::runtime_error;
using std::string;

string ProxySslClient::legoRequest(const std::string &host,
                                   const std::string &resource) const {
    Logger::info("SslClient: Sending " + getLegoMessageCodeName(LEGO_REQUEST));

    try {
        const string request{std::to_string(CODE) + SEP + resource};

        IPv4SslClientSocket client{};
        const char *hostc = host.c_str();
        client.sslConnect(hostc, PORT);
        client.sslWrite(request.data());
        char buf[4096];
        string response{client.sslRead()};
        return response;
    } catch (exception const &e) {
        throw_with_nested(runtime_error("Failed to GET from: " + resource));
    }
}
