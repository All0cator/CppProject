#pragma once

#include <string>

struct ParseInfo
{
	int width; // number of collumns
	int height; // number of rows
	int* int_array;
};

class CSVParse
{
public:
	static ParseInfo parseInts(std::string filePath, char separator=',');
};