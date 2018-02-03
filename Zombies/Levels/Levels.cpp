#include "Levels.h"
#include <fstream>
#include "../Blondie/Utils/Printerror.h"


Levels::Levels(const std::string& filename)
{
	std::ifstream file;
	file.open(filename);
	if (file.fail())
	{
		BLONDIE::PrintError("Failed to open Level File  " + filename);
	}
}


Levels::~Levels()
{
}
