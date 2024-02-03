#include "Level.h"
#include "CSVParse.h"
#include "Constants.h"
#include "GraphicsConstants.h"

#include "ParallaxBackground.h"
#include "Layer.h"
#include "GameState.h"
#include "Area.h"
#include "Player.h"
#include "Enemy.h"
#include "Camera.h"

Level::Level(GameState* gs,
			 const std::string& name,
			 int level_map_width,
			 int level_map_height,
			 const std::string& level_path,
			 const std::string& parallax_path,
			 const std::vector<int>& tileset_indices,
			 const std::vector<std::string>& group_names,
			 const std::vector<int>& group_indices,
			 const std::vector<std::string>& layer_names,
			 const std::vector<std::string>& parallax_names,
			 const std::vector<float>& parallax_speeds_x,
			 const std::vector<float>& parallax_speeds_y)
	: GameObject(gs, name)
{
	this->m_level_map_width = level_map_width;
	this->m_level_map_height = level_map_height;
	this->m_level_path = level_path;
	this->m_parallax_path = parallax_path;
	this->m_tileset_indices = tileset_indices;
	this->m_group_names = group_names;
	this->m_group_indices = group_indices;
	this->m_layer_names = layer_names;
	this->m_parallax_names = parallax_names;
	this->m_parallax_speeds_x = parallax_speeds_x;
	this->m_parallax_speeds_y = parallax_speeds_y;

	m_parallax_backgrounds.resize(parallax_names.size());
}

Level::~Level()
{
	for (int i = 0; i < m_parallax_backgrounds.size(); i++)
	{
		delete m_parallax_backgrounds[i];
	}

	for (int i = 0; i < m_environment_layers.size(); i++)
	{
		delete m_environment_layers[i];
	}

	for (int i = 0; i < m_solid_tile_areas.size(); i++)
	{
		delete m_solid_tile_areas[i];
	}
}

void Level::update(float dt)
{
	for (int i = 0; i < m_parallax_backgrounds.size(); i++)
	{
		m_parallax_backgrounds[i]->update(dt);
	}

	for (int i = 0; i < m_environment_layers.size(); i++)
	{
		m_environment_layers[i]->update(dt);
	}

	GameObject::update(dt);
}
#include <iostream>
void Level::init()
{
	Camera::inst()->setBounds(0.0f, (float)(m_level_map_width * TILE_WIDTH), 0.0f, (float)(m_level_map_height * TILE_HEIGHT));
	m_camera_min_x = Camera::inst()->getMinX();
	m_camera_max_x = Camera::inst()->getMaxX();
	m_camera_min_y = Camera::inst()->getMinY();
	m_camera_max_y = Camera::inst()->getMaxY();

	for (int i = 0; i < m_parallax_backgrounds.size(); i++)
	{
		m_parallax_backgrounds[i] = new ParallaxBackground(GameState::inst(), 
														   m_parallax_names[i],
														   m_parallax_path,
														   (float)PARALLAX_WIDTH, (float)PARALLAX_HEIGHT,
														   0.0f, 0.0f, 
														   m_parallax_speeds_x[i], m_parallax_speeds_y[i],
														   true, false);
		m_parallax_backgrounds[i]->init();
	}

	ParseInfo info = {};
	std::string group_name;

	int m_environment_layer_index = 0;

	for (int i = 0; i < m_layer_names.size(); i++)
	{
		info = CSVParse::parseInts(m_level_path + m_name + "._" + m_group_names[m_group_indices[i]] + "_" + m_layer_names[i], ',');
		std::cout << info.width << " " << info.height << std::endl;
		group_name = m_group_names[m_group_indices[i]];

		if (group_name == GROUP_NAME_ENVIRONMENT)
		{
			m_environment_layers.push_back(new Layer(GameState::inst(),
												m_layer_names[i],
												m_state->getTileset(m_tileset_indices[i]),
												info.width, info.height,
												info.int_array));

			m_environment_layers[m_environment_layer_index]->init();

			m_environment_layer_index++;
		}
		else if (group_name == GROUP_NAME_COLLISION)
		{
			int index;
			for (int y = 0; y < info.height; y++)
			{
				for (int x = 0; x < info.width; x++)
				{
					index = y * info.width + x;

					if (info.int_array[index] == TILE_SPIKE)
					{
						m_solid_tile_areas.push_back(new Area((float)(TILE_WIDTH), (float)(TILE_HEIGHT),
															  (float)(x * TILE_WIDTH), (float)(y * TILE_HEIGHT),
															  nullptr,
															  Area::AreaType::SPIKE, Area::OriginType::LEVEL, this));

						SETCOLOR(m_solid_tile_areas[m_solid_tile_areas.size() - 1]->m_debug_box_brush.fill_color, 1.0f, 0.0f, 0.0f);
					}
					else if (info.int_array[index] == TILE_SOLID_TILE)
					{
						m_solid_tile_areas.push_back(new Area((float)(TILE_WIDTH), (float)(TILE_HEIGHT),
															  (float)(x * TILE_WIDTH), (float)(y * TILE_HEIGHT),
															  nullptr,
															  Area::AreaType::TILE, Area::OriginType::LEVEL, this));

						SETCOLOR(m_solid_tile_areas[m_solid_tile_areas.size() - 1]->m_debug_box_brush.fill_color, 0.0f, 1.0f, 1.0f);
					}
				}
			}
		}
	}

	GameObject::init();
}

void Level::draw()
{
	for (int i = 0; i < m_parallax_backgrounds.size(); i++)
	{
		m_parallax_backgrounds[i]->draw();
	}

	for (int i = 0; i < m_environment_layers.size(); i++)
	{
		m_environment_layers[i]->draw();
	}

	if (m_state->m_is_debug_mode)
	{



		for (int i = 0; i < m_solid_tile_areas.size(); i++)
		{

			graphics::drawRect(graphics::windowToCanvasX(m_solid_tile_areas[i]->getLeft() - Camera::inst()->getFocalPointX() + 8.0f, false),
				graphics::windowToCanvasY(m_solid_tile_areas[i]->getTop() - Camera::inst()->getFocalPointY() + 8.0f, false),
				graphics::windowToCanvasX(16.0f, false),
				graphics::windowToCanvasY(16.0f, false),
				m_solid_tile_areas[i]->m_debug_box_brush);
		}
	}

	GameObject::draw();
}


void Level::checkCollisions(Area& area)
{
	checkTileCollisions(area);
	
	if (area.m_type == Area::AreaType::HURTBOX)
	{
		checkBoundsCollisions(area);
	}
}

void Level::checkTileCollisions(Area& area)
{
	for (int i = 0; i < m_solid_tile_areas.size(); i++)
	{
		if (m_state->collide(*m_solid_tile_areas[i], area))
		{
			area.resolveCollision(*m_solid_tile_areas[i]);
		}
	}
}

void Level::checkBoundsCollisions(Area& area)
{
	// Clamp box dimensions

	// X axis
	if (area.getLeft() < m_camera_min_x)
	{
		area.setLeft(m_camera_min_x);
	}
	else if (area.getRight() > m_camera_max_x)
	{
		area.setRight(m_camera_max_x);
	}

	// Y axis
	if (area.getTop() < m_camera_min_y)
	{
		area.setTop(m_camera_min_y);
	}
	else if (area.getBottom() > m_camera_max_y)
	{
		area.setBottom(m_camera_max_y);
	}
}