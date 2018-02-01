#include "IOmanager.h"
#include <fstream>

namespace BLONDIE
{
	bool IOManager::FileToBuffer(const std::string filepath, std::vector<unsigned char>& buffer)
	{
		//open the file for reading in binary so we get an ecact copy of the file
		std::ifstream file(filepath, std::ios::binary);

		//Check to make sure all is ok opening the file
		if (file.fail())
		{
			perror(filepath.c_str());
			return false;
		}
		//goto the end of the file
		file.seekg(0, std::ios::end);

		//get file size
	     int filesize = (int)file.tellg();
		file.seekg(0, std::ios::beg);

		// reduce file size by header bytes if any present
		filesize -= (int)file.tellg();

		// set buffer to the size of the file
		buffer.resize(filesize);

		//read in the file to the buffer
		file.read((char*)&(buffer[0]), filesize);

		file.close();

		return true;
	}
}