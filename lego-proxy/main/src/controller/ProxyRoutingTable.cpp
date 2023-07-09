#include "../../include/controller/ProxyRoutingTable.hpp"

ProxyRoutingTable* ProxyRoutingTable::proxyRoutingTable = nullptr;
std::mutex ProxyRoutingTable::mutex;

ProxyRoutingTable::ProxyRoutingTable() {}

ProxyRoutingTable* ProxyRoutingTable::getInstance() {
  std::lock_guard<std::mutex> lock(mutex);
  if (instance == nullptr) {
    proxyRoutingTable = new ProxyRoutingTable();
  }
  return proxyRoutingTable;
}


void ProxyRoutingTable::insertFigure(const std::string& figure,
                                     const std::string& ip) {
  std::lock_guard<std::mutex> lock(mutex);
  auto it = routingTable.find(figure);
  if (it != routingTable.end()) {
    it->second.push_back(ip);
  } else {
    std::vector<std::string> ipList = {ip};
    routingTable.insert({figure, ipList});
  }
}



void ProxyRoutingTable::eraseIP(const std::string& ip) {
  std::lock_guard<std::mutex> lock(mutex);

  // Iterate over each entry in the routingTable map
  for (auto it = routingTable.begin(); it != routingTable.end(); ++it) {
    // Get a reference to the vector of the current iteration
    auto& ipList = it->second;

    // Iterate over the IP list
    for (auto ipIt = ipList.begin(); ipIt != ipList.end(); ) {
      if (*ipIt == ip) {
        // If the IP matches, erase it from the vector
        ipIt = ipList.erase(ipIt);
      } else {
        // Move to the next IP in the vector
        ++ipIt;
      }
    }
    if (ipList.empty()) {
      // If the vector is empty after removing IPs, erase the entry from the map
      routingTable.erase(it);
    }
  }
}

std::string ProxyRoutingTable::getIP(const std::string& figure) {
  std::lock_guard<std::mutex> lock(mutex);
  auto it = routingTable.find(figure);
  if (it != routingTable.end()) {
    std::vector<std::string> ipList = it->second;
    if (ipList.size() > 0) {
      return ipList[0];
    }
  }
  return "";
}