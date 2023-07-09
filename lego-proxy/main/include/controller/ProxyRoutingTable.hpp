#pragma once

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <mutex>

class ProxyRoutingTable {
 public:
  static ProxyRoutingTable* getInstance();
  void insertFigure(const std::string& figure, const std::string& ip);
  void eraseIP(const std::string& ip);
  std::string getIP(const std::string& figure);
 private:
  static ProxyRoutingTable* proxyRoutingTable;
  static std::mutex mutex;
  std::unordered_map<std::string, std::vector<std::string>> routingTable;
  ProxyRoutingTable();
};