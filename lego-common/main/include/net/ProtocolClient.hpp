// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#ifndef PI_REDES_SISTEMAS_OPERATIVOS_PROTOCOLCLIENT_HPP
#define PI_REDES_SISTEMAS_OPERATIVOS_PROTOCOLCLIENT_HPP

#include "./socket/IPv4UdpSocket.hpp"
#include <string>

class ProtocolClient {
 // Constructor and destructor. 
 public:
  ProtocolClient() = default;
  ~ProtocolClient() = default;
  explicit ProtocolClient(int port);
 
 // Protocol methods.
 public:
  /**
   * @brief Sends a discover message to the given broadcast address.
   * @param broadcastAddr Broadcast address to send the message to.
   */
  void discover(const std::string& broadcastAddr);

  /**
   * @brief Sends a present message to the given IP address.
   * @param ipAddress IP address to send the message to or broadcast address.
   * @param figures Vector of figures to send.
   */
  void present(const std::string& ipAddress, const std::vector<std::string>& figures);

  /**
   * @brief Sends a release message to the given broadcast address.
   * @param broadcastAddr Broadcast address to send the message to.
   */
  void release(const std::string& broadcastAddr);

  /**
   * @brief Sends an error message to the given IP address.
   * @param code Error code.
   * @param ipAddress IP address to send the message to.
   */
  void errorMsg(const std::string& code, const std::string& ipAddress);

  /**
   * @brief Gets the current IP address of the device.
   * @return Current IP address.
   */
  std::string getCurrentIP();
 private:
  int port;
  IPv4UdpSocket socket;
};


#endif //PI_REDES_SISTEMAS_OPERATIVOS_PROTOCOLCLIENT_HPP
