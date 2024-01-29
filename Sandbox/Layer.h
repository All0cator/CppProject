#pragma once
#include "GameObject.h"
#include <unordered_map>

class Layer : public GameObject
{
private:
	std::string m_tileset_path;
	// Maps index of tile to the graphic texture
	std::unordered_map<int, bool> m_index_texture_exists;

	// Number of tiles horizontally and vertically
	int m_width;
	int m_height;
	// The array of indices
	int* m_map;

	graphics::Brush m_tile_brush;

public:
	Layer(GameState* gs,
		  const std::string& name = "",
		  const std::string& tileset_path,
		  int width,
		  int height,
		  int * map);
	virtual ~Layer();
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
};