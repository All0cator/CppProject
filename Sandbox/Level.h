#pragma once

#include "GameObject.h"

class ParallaxBackground;
class Layer;
class Area;
class Box;

class Level : public GameObject
{
private:
	int m_level_index;
	int m_level_map_width;
	int m_level_map_height;

	float m_camera_min_x;
	float m_camera_max_x;
	float m_camera_min_y;
	float m_camera_max_y;

	std::vector<Layer*> m_environment_layers;
	std::vector<Area*> m_solid_tile_areas;

	std::string m_level_path;
	std::vector<int> m_tileset_indices;
	std::vector<std::string> m_group_names;
	std::vector<int> m_group_indices;
	std::vector<std::string> m_layer_names;

public:
	Level(GameState* gs,
		int level_index,
		const std::string& name,
		int level_map_width,
		int level_map_height,
		const std::string& level_path,
		const std::vector<int>& tileset_indices,
		const std::vector<std::string>& group_names,
		const std::vector<int>& group_indices,
		const std::vector<std::string>& layer_names);
	virtual ~Level();
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	void checkCollisions(Area& dynamic_box);
	void checkTileCollisions(Area& area);
};