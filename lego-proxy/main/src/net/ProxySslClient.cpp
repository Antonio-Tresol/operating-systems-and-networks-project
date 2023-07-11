// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../../include/net/ProxySslClient.hpp"

using std::exception;
using std::runtime_error;
using std::string;

string ProxySslClient::legoRequest(const std::string &host,
                                   const std::string &resource) const {
    Logger::info("SslClient: Sending " + getLegoMessageCodeName(LEGO_REQUEST));
  try {
    // IPv4SslSocket socket{};

    // socket.sslConnect(host, PORT);

    const string request{std::to_string(CODE) + SEP + resource};
    // const string request{resource};
    // Logger::info("Sending request: " + request);
    // socket.sslWrite(request);
    // string response{socket.sslRead()};

    // return response;
    Socket* client = new Socket('s', false);
    client->InitSSL();
    const char* hostc = host.c_str();
    client->SSLConnect(hostc, PORT);

    client->SSLWrite(request.data(), request.size());
    char buf[4096];
    int bytes = client->SSLRead(buf, sizeof(buf));
    buf[bytes] = '\0';
    string response = string(buf);
    return response;
  } catch (exception const &e) {
    throw_with_nested(runtime_error("Failed to GET from: /" + resource));
  }
}
