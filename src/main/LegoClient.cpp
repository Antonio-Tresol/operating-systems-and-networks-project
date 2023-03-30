// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2022 Pablo Madrigal Ramírez <pablo.madrigalramirez@ucr.ac.cr>.

#include <string>

#include "./include/common/Logger.hpp"
#include "./include/controller/Controller.hpp"

using std::stoi;
using std::string;
using std::invalid_argument;
using std::out_of_range;
using std::exception;

/**
 * @brief Entry point.
 */
int main(int argc, char* argv[])
{
	Logger::initialize();
	try
	{
		if (argc < 1)
		{
			Logger::error("Invalid arguments", invalid_argument("No figure name provided."));

			exit(1);
		}

		string figureName{argv[0] };

		Controller().printFigure(figureName);
	}
	catch (exception const& e)
	{
		Logger::error("Client has crashed.", e);
	}

	Logger::print("Finished.");

	exit(0);
}
