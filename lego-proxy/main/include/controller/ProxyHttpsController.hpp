#pragma once

#include <map>
#include <sstream>
#include <string>

#include "../../../../lego-common/main/include/logging/Logger.hpp"
#include "../../../../lego-common/main/include/net/socket/IPv4SslSocket.hpp"
#include "../net/ProxySslClient.hpp"

class ProxyHttpsController {
 public:
  ProxyHttpsController() = default;
  ~ProxyHttpsController() = default;
  /**
   * @brief Get the Figure By Name object
   * @details search in proxy routing table for a figure by to find a host
   * @param name name of the figure
   * @return string with the figure in html format
   */
  std::string getFigureByName(const std::string &name);

 private:
  // instancia routing table
  ProxySslClient proxySslClient{};
};