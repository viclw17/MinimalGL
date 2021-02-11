#pragma once
#include <vector>
#include <string>
// static class
class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
};

