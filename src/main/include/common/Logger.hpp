// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.

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
class Logger
{
public:
	/**
	 * @brief Logs message to console with timestamp.
	 * @param message Message to log.
	 */
	static void print(const std::string& message);

	/**
	 * @brief Logs info messages with timestamp.
	 * @param message Message to log.
	 */
	static void info(const std::string& message);

	/**
	 * @brief Logs error messages with timestamp.
	 * @param message Message to log.
	 */
	static void error(const std::string& message);

	/**
	 * @brief Logs error messages with timestamp and exception unwinding.
	 * @param message Message to log.
	 * @param e Exception to unwind.
	 */
	static void error(const std::string& message, const std::exception& e);

	static void initialize();

	/**
 	 * @brief Sets internal timer to zero.
	 */
	static void setStart();

private:
	static constexpr char LOG_DIR[8]{ "./" };

	static constexpr char LOG_PATH[12]{ "./log.txt" };

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
	static std::string deduce_exception_what(const std::exception& e);

	/**
	 * @brief Unwinds exception and prints each level.
	 * @param e Exception to unwind.
	 * @param level Current unwind depth level.
	 */
	static void print_exception(const std::exception& e, int level = 0);

	static std::ofstream file;

	static std::chrono::high_resolution_clock::time_point start;
};

std::ofstream Logger::file;

std::chrono::high_resolution_clock::time_point Logger::start{
		std::chrono::high_resolution_clock::now()
};

void Logger::print(const std::string& message)
{
	std::cout << "[" << duration() << " ms]" << "[INFO]: "
			  << message << std::endl;
}

void Logger::info(const std::string& message)
{
	file << "[" << duration() << " ms]" << "[INFO]: "
		 << message << std::endl;
}

void Logger::error(const std::string& message)
{
	file << "[" << duration() << " ms]" << "[ERROR]: "
		 << message << std::endl;
}

void Logger::error(const std::string& message, const std::exception& e)
{
	error(message);
	print_exception(e);
}

u_int64_t Logger::duration()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::high_resolution_clock::now() - start).count();
}

void Logger::print_exception(const std::exception& e, int level)
{
	file << "Caused by: " << e.what() << std::endl;
	try
	{
		std::rethrow_if_nested(e);
	}
	catch (const std::exception& ne)
	{
		print_exception(ne, level + 1);
	}
}

std::string Logger::deduce_exception_what(const std::exception& e)
{
	try
	{
		std::rethrow_if_nested(e);
	}
	catch (const std::exception& ne)
	{
		return deduce_exception_what(ne);
	}
	return e.what();
}

void Logger::initialize()
{
	std::filesystem::remove_all(LOG_DIR);
	std::filesystem::create_directory(LOG_DIR);

	file.open(LOG_PATH);
}

void Logger::setStart()
{
	start = std::chrono::high_resolution_clock::now();
}
