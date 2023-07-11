// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <sstream>
#include <string>

#include "../../../../lego-common/main/include/logging/Logger.hpp"
#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"
#include "../../../../lego-common/main/include/net/socket/IPv4SslSocket.hpp"
#include "../../../../lego-common/main/include/net/socket/clSocket.hpp"
/**
 * @brief Makes Ssl Lego Requests from proxy servers.
 */
class ProxySslClient {
 public:
  /**
   * @brief Makes a lego request to the given resource and host.
   * @param resource Resource to request.
   * @param host Host to request from.
   * @return Response from host.
   */
  [[nodiscard]] std::string legoRequest(const std::string &host,
                                        const std::string &resource) const;

 private:
  static constexpr char SEP{SEPARATOR};
  static constexpr int PORT{PIECES_TCP_PORT};
  static constexpr int CODE{static_cast<int>(LEGO_REQUEST)};
};
