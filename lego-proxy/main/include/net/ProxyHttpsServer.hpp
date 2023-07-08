#pragma once
#include "../../../../lego-common/main/include/logging/Logger.hpp"
#include "../../../../lego-common/main/include/net/SslServer.hpp"
#include "../controller/ProxyHttpsController.hpp"




class ProxyHttpsServer : public SslServer {
  public:
    ProxyHttpsServer(int32_t numWorkers, const std::string& certPath,
                              int32_t port): SslServer(numWorkers, certPath, port) {}
    
    ~ProxyHttpsServer() {}
    
    /** receive a client to handle. This client is a socket that has already
     * ben ssl accepted.
     * 
    */
    void handleClient(const std::shared_ptr<IPv4SslSocket>& client) override;
    

  private:
    ProxyHttpsController proxyHttpsController{};
    void handleAcceptError(const std::exception& e) override;

};