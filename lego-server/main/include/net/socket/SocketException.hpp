// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
/**
 * @file socket_exception.hpp
 * @brief Defines the SocketException class, which represents an exception
 * thrown when a socket operation fails.
 */
#ifndef SOCKET_EXCEPTION_HPP
#define SOCKET_EXCEPTION_HPP

#include <openssl/err.h>
#include <openssl/ssl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <exception>
#include <string>

/**
 * @class SocketException
 * @brief Exception thrown when a socket operation fails
 * @details This exception is thrown when a socket operation (e.g. connect,
 * bind, send, etc.) fails. It stores the error message, the name of the
 * function that failed, and the error code associated with the failure.
 */
class SocketException : public std::exception {
 public:
  /**
   * @brief Constructor for SocketException
   * @param message The error message to associate with the exception
   * @param function The name of the function that failed
   * @param errorCode The error code associated with the failure
   */
  SocketException(const std::string& message, const std::string& function,
                  int errorCode, bool isSslError = true);
  /**
   * @brief Constructor for SocketException that does not take an error code
   * @param message The error message to associate with the exception
   * @param function is the function where error occurs
   */
  SocketException(const std::string& message, const std::string& function,
                  bool isSslError = true);
  /**
   * @brief Returns a C-style character string describing the exception
   * @return A C-style character string describing the exception
   */
  const char* what() const noexcept override;

 private:
  std::string mMessage;   ///< The error message associated with the exception
  std::string mFunction;  ///< The name of the function that failed
  int mErrorCode;         ///< The error code associated with the failure
  std::string mErrorMessage;  ///< The error message to return
  /**
   * @brief Returns the name of the function that failed
   * @return The name of the function that failed
   */
  const std::string& function() const noexcept;

  /**
   * @brief Returns the error code associated with the failure
   * @return The error code associated with the failure
   */
  int errorCode() const noexcept;

  /**
   * @brief Returns a string describing the error
   * @return A string describing the error
   */
  std::string errorMessage() const noexcept;
  /**
   * @brief gets the error message from the SSL library
   * @param message the message to prepend to the error message
   * @details depends on initialization of SSL libraries outside this class
   */
  std::string sslErrorMessage() const noexcept;
  std::string getSslError() const noexcept;
};
#endif  // SOCKET_EXCEPTION_HPP
