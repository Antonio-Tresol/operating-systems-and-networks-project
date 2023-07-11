#pragma once

#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <mutex>

class ProxyRoutingTable {
public:
    static ProxyRoutingTable & getInstance();

    void insertFigure(const std::string &figure, const std::string &ip);

    void eraseIP(const std::string &ip);

    int sizeIPList(const std::string &figure);

    std::string getIP(const std::string &figure);

    std::string getNthIP(const std::string &figure, int n);

private:
    static ProxyRoutingTable instance;
    static std::mutex mutex;

    ProxyRoutingTable() = default;

    std::unordered_map<std::string, std::vector<std::string>> routingTable;
};