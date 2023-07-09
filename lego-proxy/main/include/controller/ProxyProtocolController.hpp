#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../../../lego-common/main/include/controller/ProtocolController.hpp"
#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"
#include "../../../../lego-common/main/src/net/ProtocolClient.cpp"

class ProxyProtocolController : public ProtocolController {
 public:
  ProxyProtocolController();
  ~ProxyProtocolController();

  void handle(int code, std::string ip, std::string body);

 private:
  std::shared_ptr<std::unordered_map<std::string, std::vector<std::string>>>
      availableFigures;  // <figure, [ips]>
};