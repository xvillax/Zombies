#pragma once
#include <vector>

namespace BLONDIE {
	class IOManager
	{
	public:
		static bool FileToBuffer(const std::string filepath, std::vector<unsigned char>& buffer);
	private:
	};
}