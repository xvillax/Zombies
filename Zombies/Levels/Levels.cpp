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

	std::string tmp;
	file >> tmp >> m_numHumans;

	//bin first string read in to tmp
	tmp = "";
	//read in the rest of the lvl data
	while (std::getline(file, tmp))
	{
		m_lvlData.push_back(tmp);
	}
}


Levels::~Levels()
{
}

void Levels::Draw()
{
}
