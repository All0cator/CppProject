#include "Level.h"
#include "CSVParse.h"
#include "Constants.h"
#include "GraphicsConstants.h"

#include "ParallaxBackground.h"
#include "Layer.h"
#include "GameState.h"

Level::Level(GameState* gs,
			 const std::string& name = "",
			 const std::string& level_path,
			 const std::string& parallax_path,
			 const std::vector<std::string>& layer_tileset_paths,
			 const std::vector<std::string>& layer_names,
			 const std::vector<std::string>& parallax_names,
			 const std::vector<float>& parallax_speeds_x,
			 const std::vector<float>& parallax_speeds_y)
	: GameObject(gs, name)
{
	this->m_level_path = level_path;
	this->m_parallax_path = parallax_path;
	this->m_layer_tilesets_path = layer_tileset_paths;
	this->m_layer_names = layer_names;
	this->m_parallax_names = parallax_names;
	this->m_parallax_speeds_x = parallax_speeds_x;
	this->m_parallax_speeds_y = parallax_speeds_y;

	m_environment_layers.resize(layer_names.size());
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

void Level::init()
{
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

	for (int i = 0; i < m_environment_layers.size(); i++)
	{
		info = CSVParse::parseInts(m_layer_names[i], ',');

		m_environment_layers[i] = new Layer(GameState::inst(),
											m_layer_names[i],
											m_layer_tilesets_path[i],
											info.width, info.height, 
											info.int_array);

		m_environment_layers[i]->init();
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

	GameObject::draw();
}
