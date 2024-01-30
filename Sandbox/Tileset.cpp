#include "Tileset.h"

Tileset::Tileset(std::string tileset_path, int max_tile_index)
{
	this->m_tileset_path = tileset_path;

	for (int i = 0; i <= max_tile_index; i++)
	{
		m_index_to_texture[i] = std::to_string(i);
	}
}

Tileset::~Tileset()
{}
