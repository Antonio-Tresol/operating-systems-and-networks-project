#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../../../lego-common/main/include/controller/ProtocolController.hpp"
#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"
// #include "../../../../lego-common/main/src/net/ProtocolClient.cpp"
#include "ProxyRoutingTable.hpp"
#include "net/ProtocolClient.hpp"

class ProxyProtocolController : public ProtocolController {
 public:
  void handle(int code, std::string ip, std::string body) override;

  void discover();

 private:

    /**
     * @brief Finds the nth occurrence of a character in a string.
     *
     * @param str String to search in.
     * @param c Character to search for.
     * @param n Nth occurrence.
     * @return int Position of the nth occurrence.
     */
    int findNthOccurrence(const std::string& str, char c, int n);

  ProxyRoutingTable& proxyRoutingTable{ProxyRoutingTable::getInstance()};

  ProtocolClient protocolClient{PIECES_UDP_PORT};
};