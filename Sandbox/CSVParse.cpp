#include "CSVParse.h"
#include <fstream>
#include <iostream>


// We could make it generic but there is no reason to overengineer this
// We only need to parse integers
ParseInfo CSVParse::parseInts(std::string filePath, char separator)
{
	ParseInfo info;
	info.width = 0; // number of ints in a line
	info.height = 0; // number of lines read
	info.int_array = std::vector<int>(); // should be set to ints.data() in the end before returning

	// Read File line by line and read characters and convert them to numbers
	// Until you get to a separator=comma then convert characters to integer

	std::ifstream in(filePath + ".csv", std::ios_base::in);
	if (in.is_open())
	{
		std::string line;
		int idx;

		while (std::getline(in, line))
		{
			info.height++;
			idx = 0;


			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == separator)
				{
					info.int_array.push_back(std::stoi(line.substr(idx, i - idx)));
					idx = i + 1;
				}
			}

			info.int_array.push_back(std::stoi(line.substr(idx, line.length() - 1)));
		}

		info.width = info.int_array.size() / info.height;

		in.close();
	}
	else
	{
		std::cout << "Error: Could not load CSV file at: " << filePath << ".csv" << std::endl;
	}

	return info;
}