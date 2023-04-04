// Copyright 2022 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2022 Pablo Madrigal Ramírez <pablo.madrigalramirez@ucr.ac.cr>.

#include <string>

#include "./include/common/Logger.hpp"
#include "controller/FigureController.hpp"

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
		if (argc < 2)
		{
			Logger::error("Invalid arguments", invalid_argument("No figure name provided."));

			exit(1);
		}

		string figureName{argv[1] };

        FigureController().printFigureByName(figureName);
	}
	catch (exception const& e)
	{
		Logger::error("Client has crashed.", e);
	}

	Logger::info("Finished.");

	exit(0);
}
