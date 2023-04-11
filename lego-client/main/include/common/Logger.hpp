// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>

#pragma once

#include <chrono>
#include <cstdint>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

/**
 * @brief Logs info and error messages to file, and unwinds nested exceptions.
 */
class Logger {
 public:
  /**
   * @brief Logs message to console with timestamp.
   * @param message Message to log.
   */
  static void print(const std::string &message);

  /**
   * @brief Logs info messages with timestamp.
   * @param message Message to log.
   */
  static void info(const std::string &message);

  /**
   * @brief Logs error messages with timestamp.
   * @param message Message to log.
   */
  static void error(const std::string &message);

  /**
   * @brief Logs error messages with timestamp and exception unwinding.
   * @param message Message to log.
   * @param e Exception to unwind.
   */
  static void error(const std::string &message, const std::exception &e);

  static void initialize();

 private:
  static constexpr char LOG_DIR[]{"./logs"};

  static constexpr char LOG_FILE[]{"/log.txt"};

  /**
   * @brief Determines the time it takes to process each method or action.
    * @details Method that records the processing time
   * @return u_int64_t value
   */
  static u_int64_t duration();

  /**
   * @brief Unwinds a nested exception to return the descriptive message of
   * the bottom level exception.
   * @param e Exception to unwind and deduce.
   * @return Descriptive message of bottom level exception.
   */
  static std::string deduce_exception_what(const std::exception &e);

  /**
   * @brief Unwinds exception and prints each level.
   * @param e Exception to unwind.
   * @param level Current unwind depth level.
   */
  static void print_exception(const std::exception &e, int level = 0);

  static std::ofstream file;

  static std::chrono::high_resolution_clock::time_point start;
};