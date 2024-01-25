#include "CSVParse.h"
#include <fstream>
#include <vector>

// We could make it generic but there is no reason to overengineer this
// We only need to parse integers
ParseInfo CSVParse::parseInts(std::string filePath, char separator)
{
	std::vector<int> ints;
	ParseInfo info;
	info.width = 0; // number of ints in a line
	info.height = 0; // number of lines read
	info.int_array = nullptr; // should be set to ints.data() in the end before returning

	// Read File line by line and read characters and convert them to numbers
	// Until you get to a separator=comma then convert characters to integer



	return info;
}