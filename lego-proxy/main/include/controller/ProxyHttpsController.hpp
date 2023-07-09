#pragma once

#include <map>
#include <sstream>
#include <string>

#include "../../../../lego-common/main/include/logging/Logger.hpp"
#include "../../../../lego-common/main/include/net/socket/IPv4SslSocket.hpp"

class ProxyHttpsController {
 public:
  ProxyHttpsController() = default;
  ~ProxyHttpsController() = default;
  std::string getFigureByName(const std::string &name);

 private:
  // instancia routing table
};