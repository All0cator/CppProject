#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Tileset
{
public:
	std::string m_tileset_path;
	std::unordered_map<int, std::string> m_index_to_texture;
public:
	Tileset(std::string tileset_path, int max_tile_index);
	virtual ~Tileset();
};