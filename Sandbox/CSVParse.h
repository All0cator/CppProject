#pragma once

#include <string>
#include <vector>

struct ParseInfo
{
	int width; // number of collumns
	int height; // number of rows
	std::vector<int> int_array;
};

class CSVParse
{
public:
	static ParseInfo parseInts(std::string filePath, char separator=',');
};