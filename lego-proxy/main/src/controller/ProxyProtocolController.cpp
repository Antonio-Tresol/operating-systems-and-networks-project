#include "../../include/controller/ProxyProtocolController.hpp"

#include <algorithm>

#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"
using std::string;
using std::vector;

int findNthOccurrence(const std::string& str, char c, int n);

ProxyProtocolController::ProxyProtocolController(ProxyRoutingTable* routingTable) {
  setRoutingTable(routingTable);
}

void ProxyProtocolController::handle(int code, std::string ip,
                                     std::string body) {
  if (code == LEGO_PRESENT) {
    // Se deben guardar las figuras, no se responde.
    int indexNthOccurrence = findNthOccurrence(body, SEPARATOR, 2);
    if (indexNthOccurrence == -1) {
      // TODO: Error.
      // Logger::error("Error: invalid body.");
      return;
    }

    string extractedBody = body.substr(indexNthOccurrence + 1); // Se quita el codigo, separador e ip:puerto.

    std::istringstream iss(extractedBody);
    std::string token;
    while (std::getline(iss, token, SEPARATOR)) {
      proxyRoutingTable->insertFigure(token, ip);
    }
  } else if (code == LEGO_RELEASE) {
    proxyRoutingTable->eraseIP(ip);
  }
  
}

int findNthOccurrence(const std::string& str, char c, int n) {
  int count = 0;
  for (int i = 0; i < str.length(); i++) {
    if (str[i] == c) {
      count++;
      if (count == n) {
        return i;
      }
    }
  }
  return -1;  // Character not found or nth occurrence not found
}