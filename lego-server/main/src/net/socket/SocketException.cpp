// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
#include "../include/net/socket/SocketException.hpp"

SocketException::SocketException(const std::string& message,
                                 const std::string& function, int errorCode,
                                 bool isSslError)
    : mMessage(message), mFunction(function), mErrorCode(errorCode) {
  if (isSslError) {
    this->mErrorMessage = sslErrorMessage();
  } else {
    this->mErrorMessage = errorMessage();
  }
}

SocketException::SocketException(const std::string& message,
                                 const std::string& function, bool isSslError)
    : mMessage(message), mFunction(function) {
  if (isSslError) {
    this->mErrorMessage = sslErrorMessage();
  } else {
    this->mErrorMessage = mMessage + " (" + mFunction + ")";
  }
}
const char* SocketException::what() const noexcept {
  return this->mErrorMessage.c_str();
}

const std::string& SocketException::function() const noexcept {
  return mFunction;
}

int SocketException::errorCode() const noexcept { return mErrorCode; }

std::string SocketException::errorMessage() const noexcept {
  return mMessage + " (" + mFunction + ") - " + strerror(mErrorCode);
}

std::string SocketException::sslErrorMessage() const noexcept {
  return mMessage + " (" + mFunction + ") - " +
         ERR_error_string(mErrorCode, NULL);
}

std::string SocketException::getSslError() const noexcept {
  uint64_t error = ERR_get_error();
  const char* buffer = ERR_reason_error_string(error);
  std::string output = mMessage + " (" + mFunction + ") - ";
  if (buffer) {
    output += ": ";
    output += buffer;
  } else {
    output += ": NULL";
  }
  return output;
}
