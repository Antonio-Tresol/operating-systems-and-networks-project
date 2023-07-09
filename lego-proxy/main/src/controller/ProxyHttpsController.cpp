#include "../../include/controller/ProxyHttpsController.hpp"

using std::string;

string ProxyHttpsController::getFigureByName(const string &name) {
  // todo: search in proxy routing table
  std::string host{};
  // todo: search in proxy routing table
  std::string figureHtml{proxySslClient.legoRequest(host, name)};
  return figureHtml;
};
