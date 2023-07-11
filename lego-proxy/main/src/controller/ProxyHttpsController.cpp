#include "../../include/controller/ProxyHttpsController.hpp"

using std::string;

string ProxyHttpsController::getFigureByName(const string &name) {
  // check if figure is in routing table
  int ipCount{proxyRoutingTable.sizeIPList(name)};
  if (1 > ipCount) {
    // if it is not in routing table, return empty string
    return "";
  }
  // we will try to connect to the host 3 times, if it fails 3 times or error is
  // econnrefused, we will erase the host from the routing table
  int attempts{0};
  int const maxAttempts{3};
  int hostIndex{0};
  string host{proxyRoutingTable.getNthIP(name, hostIndex)};

  while (hostIndex < ipCount) {
    try {
      // use proxy ssl client to connect to host and get the figure
      string figureHtml{proxySslClient.legoRequest(host, name)};
      return figureHtml;

    } catch (std::exception const &e) {
      if (std::string(e.what()) == "ECONNREFUSED" || attempts == maxAttempts) {
        // on econnrefused or after maxAttempts, we will erase the host
        proxyRoutingTable.eraseIP(host);

        // update IP count
        ipCount = proxyRoutingTable.sizeIPList(name);

        // reset attempts
        attempts = 0;

        hostIndex++;

        // and get the next host if we are still within bounds
        if (hostIndex < ipCount) {
          host = proxyRoutingTable.getNthIP(name, hostIndex);
        }

      } else {
        // if we have not tried to connect to the host 3 times, we will retry
        attempts++;
      }
    }
  }
  return "";
}
