#include "../include/controller/ProxyProtocolController.hpp"
#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"

#include <algorithm>
using std::string;
using std::vector;

int findNthOccurrence(const std::string& str, char c, int n);

ProxyProtocolController::ProxyProtocolController() {
  this->availableFigures = std::make_shared<std::unordered_map<std::string, std::vector<std::string>>>(); // Don't delete
}

void ProxyProtocolController::handle(int code, std::string ip, std::string body) {
  if (code == LEGO_PRESENT) {
    // Se deben guardar las figuras, no se responde.
    // Fijarse si existe la figura en availableFigures, si no existe, se agrega.
    int indexNthOccurrence = findNthOccurrence(body, SEPARATOR, 2);
    if (indexNthOccurrence == -1) {
      // TODO: Error.
      Logger::error("Error: invalid body.");
      return;
    }

    string extractedBody = body.substr(indexNthOccurrence + 1); // Se quita el codigo, separador e ip:puerto.

    std::istringstream iss(extractedBody);
    std::string token;

    while (std::getline(iss, token, SEPARATOR)) {
      if (availableFigures->find(token) == availableFigures->end()) { 
        // If token is not found in availableFigures, add it
        vector<string> ips = {ip};
        availableFigures->insert(std::make_pair(token, ips));
      } else {
        auto converted = *availableFigures;
        if (std::find(converted[token].begin(), converted[token].end(), ip)
              == converted[token].end()) {
          // Se agrega la ip a la lista de ips.
          (converted[token]).push_back(ip);
        }
      }
    }



  } else if (code == LEGO_RELEASE) {
    // Se debe quitar de la lista de servidores de piezas disponibles.
    // Fijarse si existe la figura en availableFigures
    for (auto& pair: (*availableFigures)) {
      auto it = std::find(pair.second.begin(), pair.second.end(), ip);
      if (it != pair.second.end()) {
        // Elemento encontrado, se elimina.
        pair.second.erase(it);
      }
      // TODO: si es la ultima ip de la key entonces se elimina la key.
    }
    
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