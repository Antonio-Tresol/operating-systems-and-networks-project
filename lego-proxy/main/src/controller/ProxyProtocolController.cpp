#include "../../include/controller/ProxyProtocolController.hpp"

#include <algorithm>

#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"
#include "./logging/Logger.hpp"

using std::string;
using std::vector;

void ProxyProtocolController::handle(int code, string ip, string body) {
    if (code == LEGO_PRESENT) {
        // Se deben guardar las figuras, no se responde.
        int indexNthOccurrence = findNthOccurrence(body, SEPARATOR, 2);
        if (indexNthOccurrence == -1) {
            Logger::error("Error: invalid body.");
            return;
        }

        string extractedBody = body.substr(indexNthOccurrence + 1); // Se quita el codigo, separador e ip:puerto.

        std::istringstream iss(extractedBody);
        string token;
        while (std::getline(iss, token, SEPARATOR)) {
            Logger::info("ProtocolController: Adding entry:\n\t Figure: " + token + "\n\t IP: " + ip);
            proxyRoutingTable.insertFigure(token, ip);
        }
    } else if (code == LEGO_RELEASE) {
        Logger::info("ProtocolController: Erasing IP address: " + ip);
        proxyRoutingTable.eraseIP(ip);
    }
}

void ProxyProtocolController::discover() {
    protocolClient.discover();
}

int ProxyProtocolController::findNthOccurrence(const string &str, char c, int n) {
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
