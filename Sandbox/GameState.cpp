#include "GameState.h"
#include "Player.h"
#include "Platform.h"
#include "Level.h"
#include "Tileset.h"

#include "GraphicsConstants.h"

#include <iostream>

GameState* GameState::m_instance = nullptr;

GameState::GameState()
{}

GameState::~GameState()
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		delete m_tilesets[i];
	}

	for (int i = 0; i < m_levels.size(); i++)
	{
		delete m_levels[i];
	}

	delete m_player;
}

GameState * GameState::inst()
{
	if (GameState::m_instance == nullptr)
	{
		GameState::m_instance = new GameState();
	}

	return GameState::m_instance;
}

void GameState::update(float dt)
{
	// dt is in milliseconds so / 1000.0f will make it in seconds
	float deltaTime = dt / 1000.0f;

	/*if (timer->IsRunning())
	{
		timer->Update(dt);
		std::cout << timer->GetAccumulatedTime() << std::endl;
	}*/


	m_current_level->update(deltaTime);
	m_player->update(deltaTime);

	testCollisions();
	//m_platform->update(deltaTime);
}

void GameState::init()
{
	m_assets_path = "assets/";

	m_textures_path = "textures/";
	m_sounds_path = "sounds/";
	m_levels_path = "levels/";

	m_window_width = WINDOW_WIDTH;
	m_window_height = WINDOW_HEIGHT;
	m_window_title = "Project Cpp";

	m_canvas_width = CANVAS_WIDTH;
	m_canvas_height = CANVAS_HEIGHT;

	// Create Level 0

	std::string m_levels_path = m_assets_path + "levels/";
	std::string m_level0_path = m_levels_path + "level0/";
		
	std::vector<std::string> group_names    { GROUP_NAME_ENVIRONMENT, GROUP_NAME_COLLISION};
	std::vector<int> group_indices { 0, 0, 
									 1, 1,
									 1, 1,
									 1, 1,
									 1, 1,
									 1 };

	std::vector<std::string> environment_layer_names    { LAYERS_ENVIRONMENT_SPIKES, LAYERS_ENVIRONMENT_BRIDGES,
														  LAYERS_ENVIRONMENT_FENCES, LAYERS_ENVIRONMENT_GRASS,
														  LAYERS_ENVIRONMENT_BUSHES, LAYERS_ENVIRONMENT_BIGTREES,
														  LAYERS_ENVIRONMENT_SMALLTREES, LAYERS_ENVIRONMENT_ROCKSFORE,
														  LAYERS_ENVIRONMENT_ROCKSBACK };
														  

	std::vector<std::string> collision_layer_names		{ LAYERS_COLLISION_SOLIDTILES, LAYERS_COLLISION_SPIKES };

	std::vector<std::string> level_layers;

	m_tilesets_path = m_assets_path + m_textures_path + "tiles/";

	std::vector<std::string> tileset_paths { TILESET_FOREST, TILESET_TREES, TILESET_COLLISION_TILE };
	std::vector<int> tileset_max_indices { TILESET_FOREST_TEXTURES_MAX, TILESET_TREES_TEXTURES_MAX, TILESET_COLLISION_TILE_MAX };

	createTilesets(tileset_paths, tileset_max_indices);

	std::string tileset_collisiontile_path = m_tilesets_path + "collision_tile/";
	std::string tileset_forest_path = m_tilesets_path + "forest/";
	std::string tileset_trees_path = m_tilesets_path + "trees/";

	std::vector<std::string> layer_tileset_paths { tileset_collisiontile_path, tileset_collisiontile_path,
												   tileset_forest_path, tileset_forest_path,
												   tileset_forest_path, tileset_forest_path,
												   tileset_forest_path, tileset_trees_path, 
												   tileset_trees_path, tileset_forest_path,
												   tileset_forest_path };
	
	std::string m_parallax_path = m_assets_path + m_textures_path + "parallax/";

	std::vector<std::string> parallax_names { PARALLAX_NAME_0, PARALLAX_NAME_1,
											 PARALLAX_NAME_2, PARALLAX_NAME_3 };

	std::vector<float> parallax_speeds_x { PARALLAX_NAME_0_SPEED_X, PARALLAX_NAME_1_SPEED_X, 
										 PARALLAX_NAME_2_SPEED_X, PARALLAX_NAME_3_SPEED_X };

	std::vector<float> parallax_speeds_y { PARALLAX_NAME_0_SPEED_Y, PARALLAX_NAME_1_SPEED_Y,
										 PARALLAX_NAME_2_SPEED_Y, PARALLAX_NAME_3_SPEED_Y };


	std::string m_knight_path = m_assets_path + m_textures_path + "knight/";
	std::string m_skeleton_path = m_assets_path + m_textures_path + "skeleton/";

	// textures
	//		knight
	//			Animations...
	//		skeleton
	//			Idle
	//		parallax
	//		tiles
	//			collision_tile
	//			forest
	//			trees

	std::vector<std::string> directories { m_knight_path + KNIGHT_ANIM_ATTACKCOMBO2HIT + "/",
										   m_knight_path + KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT + "/",
										   m_knight_path + KNIGHT_ANIM_CROUCHIDLE + "/",
										   m_knight_path + KNIGHT_ANIM_CROUCHATTACK + "/",
										   m_knight_path + KNIGHT_ANIM_CROUCHTRANSITION + "/",
										   m_knight_path + KNIGHT_ANIM_CROUCHWALK + "/",
										   m_knight_path + KNIGHT_ANIM_DASH + "/",
										   m_knight_path + KNIGHT_ANIM_DEATH + "/",
										   m_knight_path + KNIGHT_ANIM_DEATHNOMOVEMENT + "/",
										   m_knight_path + KNIGHT_ANIM_FALL + "/",
										   m_knight_path + KNIGHT_ANIM_HIT + "/",
										   m_knight_path + KNIGHT_ANIM_IDLE + "/",
										   m_knight_path + KNIGHT_ANIM_JUMP + "/",
										   m_knight_path + KNIGHT_ANIM_JUMPFALLINBETWEEN + "/",
										   m_knight_path + KNIGHT_ANIM_RUN + "/",
										   m_knight_path + KNIGHT_ANIM_TURN_ARROUND + "/",
											

										   m_skeleton_path + SKELETON_ANIM_ATTACK + "/",
										   m_skeleton_path + SKELETON_ANIM_DEATH + "/",
										   m_skeleton_path + SKELETON_ANIM_HIT + "/",
										   m_skeleton_path + SKELETON_ANIM_IDLE + "/",
										   m_skeleton_path + SKELETON_ANIM_WALK + "/",
											
										   
										   m_parallax_path,

										   tileset_collisiontile_path,
										   tileset_forest_path,
										   tileset_trees_path};

	preLoadTextures(directories);

	m_current_level = new Level(GameState::inst(), 
								"level0", 
								m_level0_path,
								m_parallax_path,
								layer_tileset_paths,
								group_names,
								group_indices,
								environment_layer_names,
								collision_layer_names,
								parallax_names,
								parallax_speeds_x,
								parallax_speeds_y);

	m_player = new Player(GameState::inst(), "player/", "player/boy2.png", "Player");
	m_platform = new Platform(GameState::inst(), "", "blocks/red_block.png", "Platform");

	m_current_level->init();

	m_player->init();
	m_platform->init();
}

void GameState::draw()
{
	m_current_level->draw();
	m_player->draw();
}

void GameState::preLoadTextures(const std::vector<std::string>& directories)
{
	for (int i = 0; i < directories.size(); i++)
	{
		graphics::preloadBitmaps(directories[i]);
	}
}

std::string GameState::getTexturesPath()
{
	return m_assets_path + m_textures_path;
}

std::string GameState::getSoundsPath()
{
	return m_assets_path + m_sounds_path;
}

Tileset* GameState::getTileset(int index)
{
	if (index >= m_tilesets.size()) return nullptr;
	return m_tilesets[index];
}

int GameState::getWindowWidth()
{
	return m_window_width;
}

int GameState::getWindowHeight()
{
	return m_window_height;
}

float GameState::getCanvasWidth()
{
	return m_canvas_width;
}

float GameState::getCanvasHeight()
{
	return m_canvas_height;
}

std::string GameState::getWindowTitle()
{
	return m_window_title;
}

void GameState::testCollisions()
{
	for (int i = 0; i < m_collision_group_dynamic.size(); i++)
	{
		for (int j = 0; j < m_collision_group_all.size(); j++)
		{
			if (collide(m_collision_group_dynamic[i], m_collision_group_all[j]))
			{
				if (&m_collision_group_dynamic[i] != &m_collision_group_all[j])
				{
					m_collision_group_dynamic[i].resolveCollision(m_collision_group_all[j]);
				}
			}
		}
	}
}

void GameState::createTilesets(const std::vector<std::string>& tileset_paths, 
							   const std::vector<int>& tileset_max_indices)
{
	m_tilesets = std::vector<Tileset*>(TILESET_COUNT);
	for (int i = 0; i < TILESET_COUNT; i++)
	{
		m_tilesets[i] = new Tileset(tileset_paths[i], tileset_max_indices[i]);
	}
}

void GameState::createLevels()
{

}

bool GameState::collide(Box& a, Box& b)
{
	m_min_right = std::min(a.m_right, b.m_right);
	m_max_left = std::max(a.m_left, b.m_left);

	if (m_max_left > m_min_right) return false;

	m_min_bottom = std::min(a.m_bottom, b.m_bottom);
	m_max_top = std::max(a.m_top, b.m_top);

	if (m_max_top > m_min_bottom) return false;

	return true;
}
