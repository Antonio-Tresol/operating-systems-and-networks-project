#pragma once

#include "../../../lego-common/include/controller/ProtocolController.hpp"
#include "lego-common/main/src/net/ProtocolClient.cpp"
#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

class ProxyProtocolController : public ProtocolController {
public:
  ProxyProtocolController();
  ~ProxyProtocolController();

  void handle(int code, std::string ip, std::string body);

private:
  std::shared_ptr<std::unordered_map<std::string, std::vector<std::string>>> availableFigures; // <figure, [ips]>

};