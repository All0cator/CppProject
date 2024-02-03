#pragma once
#include "GameObject.h"
#include <unordered_map>

class Tileset;

class Layer : public GameObject
{
private:
	Tileset* m_tileset;

	// Number of tiles horizontally and vertically
	int m_width;
	int m_height;
	// The array of indices
	std::vector<int> m_map;

	graphics::Brush m_tile_brush;
	graphics::Brush m_debug_brush;

public:
	Layer(GameState* gs,
		  const std::string& name,
		  Tileset * tileset,
		  int width,
		  int height,
		  const std::vector<int>& map);
	virtual ~Layer();
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
};