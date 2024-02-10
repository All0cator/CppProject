#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include "Tileset.h"
#include "Enemy.h"
#include "Area.h"
#include "Camera.h"
#include "ParallaxBackground.h"
#include "GraphicsConstants.h"

#include <iostream>

GameState* GameState::m_instance = nullptr;

GameState::GameState()
{
	m_window_width = WINDOW_WIDTH;
	m_window_height = WINDOW_HEIGHT;
	m_window_title = "Project Cpp";

	m_canvas_width = CANVAS_WIDTH;
	m_canvas_height = CANVAS_HEIGHT;
}

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
	if (graphics::getKeyState(graphics::SCANCODE_Q))
	{
		if (!m_toggle_timer->IsRunning())
		{
			m_is_debug_mode = !m_is_debug_mode;
			m_toggle_timer->Reset();
		}
	}
	else if (graphics::getKeyState(graphics::SCANCODE_0))
	{
		if (!m_toggle_timer->IsRunning())
		{
			std::cout << "Teleporting to Level 0" << std::endl;
			m_player->setLeft(48.0f - 64.0f);
			m_player->setTop(260.0f - 64.0f);
			m_player->updateAreaDimensions();
			m_player->init();
			m_toggle_timer->Reset();
		}
	}
	else if (graphics::getKeyState(graphics::SCANCODE_1))
	{
		if (!m_toggle_timer->IsRunning())
		{
			std::cout << "Teleporting to Level 1" << std::endl;
			m_player->setLeft(48.0f - 64.0f + LEVEL_OFFSET_X);
			m_player->setTop(260.0f - 64.0f);
			m_player->updateAreaDimensions();
			m_player->init();
			m_toggle_timer->Reset();
		}
	}
	else if (graphics::getKeyState(graphics::SCANCODE_2))
	{
		if (!m_toggle_timer->IsRunning())
		{
			std::cout << "Teleporting to Level 2" << std::endl;
			m_player->setLeft(32.0f - 64.0f + LEVEL_OFFSET_X * 2);
			m_player->setTop(164.0f - 64.0f);
			m_player->updateAreaDimensions();
			m_player->init();
			m_toggle_timer->Reset();
		}
	}
	else if (graphics::getKeyState(graphics::SCANCODE_3))
	{
		if (!m_toggle_timer->IsRunning())
		{
			std::cout << "Teleporting to Level 3" << std::endl;
			m_player->setLeft(48.0f - 64.0f + LEVEL_OFFSET_X * 3);
			m_player->setTop(260.0f - 64.0f);
			m_player->updateAreaDimensions();
			m_player->init();
			m_toggle_timer->Reset();
		}
	}
	else if (graphics::getKeyState(graphics::SCANCODE_4))
	{
		if (!m_toggle_timer->IsRunning())
		{
			std::cout << "Teleporting to Level 4" << std::endl;
			m_player->setLeft(48.0f - 64.0f + LEVEL_OFFSET_X * 4);
			m_player->setTop(52.0f - 64.0f);
			m_player->updateAreaDimensions();
			m_player->init();
			m_toggle_timer->Reset();
		}
	}
	else if (graphics::getKeyState(graphics::SCANCODE_5))
	{
		if (!m_toggle_timer->IsRunning())
		{
			std::cout << "Teleporting to Level 5" << std::endl;
			m_player->setLeft(48.0f - 64.0f + LEVEL_OFFSET_X * 5);
			m_player->setTop(164.0f - 64.0f);
			m_player->updateAreaDimensions();
			m_player->init();
			m_toggle_timer->Reset();
		}
	}
	else if (graphics::getKeyState(graphics::SCANCODE_6))
	{
		if (!m_toggle_timer->IsRunning())
		{
			std::cout << "Teleporting to Level 6" << std::endl;
			m_player->setLeft(32.0f - 64.0f + LEVEL_OFFSET_X * 6);
			m_player->setTop(68.0f - 64.0f);
			m_player->updateAreaDimensions();
			m_player->init();
			m_toggle_timer->Reset();
		}
	}
	
	m_toggle_timer->Update(deltaTime);

	m_current_level_index = (int)((m_player->getLeft()) / (LEVEL_MAP_WIDTH * TILE_WIDTH));

	for (int i = 0; i < m_parallax_backgrounds.size(); i++)
	{
		m_parallax_backgrounds[i]->update(dt);
	}

	if (m_current_level_index - 1 >= 0)
	{
		m_levels[m_current_level_index - 1]->update(deltaTime);
	}
	
	m_levels[m_current_level_index]->update(deltaTime);
	
	if (m_current_level_index + 1 < LEVELS_COUNT)
	{
		m_levels[m_current_level_index + 1]->update(deltaTime);
	}

	m_player->update(deltaTime);

	if (m_current_level_index - 1 >= 0)
	{
		for (int i = 0; i < m_levels_enemies[m_current_level_index - 1].size(); i++)
		{
			m_levels_enemies[m_current_level_index - 1][i]->update(deltaTime);
		}
	}

	for (int i = 0; i < m_levels_enemies[m_current_level_index].size(); i++)
	{
		m_levels_enemies[m_current_level_index][i]->update(deltaTime);
	}

	if (m_current_level_index + 1 < LEVELS_COUNT)
	{
		for (int i = 0; i < m_levels_enemies[m_current_level_index + 1].size(); i++)
		{
			m_levels_enemies[m_current_level_index + 1][i]->update(deltaTime);
		}
	}
}

void GameState::init()
{
	m_assets_path = "assets/";

	m_textures_path = "textures/";
	m_sounds_path = "sounds/";

	m_is_debug_mode = false;
	m_toggle_timer = new Timer(0.5f);

	// Create Level 0

	m_levels_path = m_assets_path + "levels/";
	m_levels_enemies.resize(LEVELS_COUNT);
	for (int i = 0; i < LEVELS_COUNT; i++)
	{
		m_level_names.push_back("level" + std::to_string(i));
		m_level_paths.push_back(m_levels_path + "level" + std::to_string(i) + "/");
	}
		
	group_names  = std::vector<std::string>{ GROUP_NAME_ENVIRONMENT, GROUP_NAME_COLLISION};
	group_indices = std::vector<int>{ 0, 0,
									 0, 0,
									 0, 0,
									 0, 0,
									 0, 1,
									 1 };

	layer_names = std::vector<std::string>{ LAYERS_ENVIRONMENT_ROCKSBACK, LAYERS_ENVIRONMENT_ROCKSFORE,
											  LAYERS_ENVIRONMENT_SMALLTREES, LAYERS_ENVIRONMENT_BIGTREES,
											LAYERS_ENVIRONMENT_BUSHES, LAYERS_ENVIRONMENT_GRASS,
											LAYERS_ENVIRONMENT_FENCES, LAYERS_ENVIRONMENT_BRIDGES,
											LAYERS_ENVIRONMENT_SPIKES, LAYERS_COLLISION_SPIKES,
											LAYERS_COLLISION_SOLIDTILES
											   };
											  
										  
	m_tilesets_path = m_assets_path + m_textures_path + "tiles/";

	tileset_paths = std::vector<std::string>{ m_tilesets_path + TILESET_FOREST + "/",
											  m_tilesets_path + TILESET_TREES + "/",
											  m_tilesets_path + TILESET_COLLISION_TILE + "/"};
	tileset_max_indices = std::vector<int>{ TILESET_FOREST_TEXTURES_MAX, TILESET_TREES_TEXTURES_MAX, TILESET_COLLISION_TILE_MAX };

	createTilesets(tileset_paths, tileset_max_indices);

	tileset_collisiontile_path = m_tilesets_path + "collision_tile/";
	tileset_forest_path = m_tilesets_path + "forest/";
	tileset_trees_path = m_tilesets_path + "trees/";

	tileset_indices = std::vector<int>{ 0, 0,
									   1, 1,
									   0, 0,
									   0, 0, 
									   0, 2,
									   2 };
	
	m_parallax_path = m_assets_path + m_textures_path + "parallax/";

	parallax_names = std::vector<std::string>{ PARALLAX_NAME_0, PARALLAX_NAME_1,
											 PARALLAX_NAME_2, PARALLAX_NAME_3 };

	parallax_speeds_x = std::vector<float>{ PARALLAX_NAME_0_SPEED_X, PARALLAX_NAME_1_SPEED_X,
										 PARALLAX_NAME_2_SPEED_X, PARALLAX_NAME_3_SPEED_X };

	parallax_speeds_y = std::vector<float>{ PARALLAX_NAME_0_SPEED_Y, PARALLAX_NAME_1_SPEED_Y,
										 PARALLAX_NAME_2_SPEED_Y, PARALLAX_NAME_3_SPEED_Y };


	m_knight_path = m_assets_path + m_textures_path + "knight/";
	m_skeleton_path = m_assets_path + m_textures_path + "skeleton/";

	// textures
	//		knight
	//			Animations...
	//		skeleton
	//			Animations...
	//		parallax
	//		tiles
	//			collision_tile
	//			forest
	//			trees

	player_anim_directories = std::vector<std::string>{ m_knight_path + KNIGHT_ANIM_ATTACKCOMBO2HIT + "/",
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
												  m_knight_path + KNIGHT_ANIM_TURN_ARROUND + "/"
												};
	player_animation_names = std::vector<std::string>{ KNIGHT_ANIM_ATTACKCOMBO2HIT,
													 KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT,
													 KNIGHT_ANIM_CROUCHIDLE,
													 KNIGHT_ANIM_CROUCHATTACK,
													 KNIGHT_ANIM_CROUCHTRANSITION,
													 KNIGHT_ANIM_CROUCHWALK,
													 KNIGHT_ANIM_DASH,
													 KNIGHT_ANIM_DEATH,
													 KNIGHT_ANIM_DEATHNOMOVEMENT,
													 KNIGHT_ANIM_FALL,
													 KNIGHT_ANIM_HIT,
													 KNIGHT_ANIM_IDLE,
													 KNIGHT_ANIM_JUMP,
													 KNIGHT_ANIM_JUMPFALLINBETWEEN,
													 KNIGHT_ANIM_RUN, 
													 KNIGHT_ANIM_TURN_ARROUND
												   };

	player_animation_frames = std::vector<unsigned int>{
														KNIGHT_ANIM_ATTACKCOMBO2HIT_FRAMES,
														KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT_FRAMES,
														KNIGHT_ANIM_CROUCHIDLE_FRAMES,
														KNIGHT_ANIM_CROUCHATTACK_FRAMES,
														KNIGHT_ANIM_CROUCHTRANSITION_FRAMES,
														KNIGHT_ANIM_CROUCHWALK_FRAMES,
														KNIGHT_ANIM_DASH_FRAMES,
														KNIGHT_ANIM_DEATH_FRAMES,
														KNIGHT_ANIM_DEATHNOMOVEMENT_FRAMES,
														KNIGHT_ANIM_FALL_FRAMES,
														KNIGHT_ANIM_HIT_FRAMES,
														KNIGHT_ANIM_IDLE_FRAMES,
														KNIGHT_ANIM_JUMP_FRAMES,
														KNIGHT_ANIM_JUMPFALLINBETWEEN_FRAMES,
														KNIGHT_ANIM_RUN_FRAMES,
														KNIGHT_ANIM_TURN_ARROUND_FRAMES,
													  };

	skeleton_anim_directories = std::vector<std::string>{ m_skeleton_path + SKELETON_ANIM_ATTACK + "/",
														m_skeleton_path + SKELETON_ANIM_DEATH + "/",
														m_skeleton_path + SKELETON_ANIM_HIT + "/",
														m_skeleton_path + SKELETON_ANIM_IDLE + "/",
														m_skeleton_path + SKELETON_ANIM_WALK + "/"
													  };

	skeleton_animation_names  = std::vector<std::string>{ SKELETON_ANIM_ATTACK,
													   SKELETON_ANIM_DEATH,
													   SKELETON_ANIM_HIT,
													   SKELETON_ANIM_IDLE,
													   SKELETON_ANIM_WALK
													 };

	skeleton_animation_frames = std::vector<unsigned int>{ SKELETON_ANIM_ATTACK_FRAMES,
														 SKELETON_ANIM_DEATH_FRAMES,
														 SKELETON_ANIM_HIT_FRAMES,
														 SKELETON_ANIM_IDLE_FRAMES,
														 SKELETON_ANIM_WALK_FRAMES
													   };

	other_directories = std::vector<std::string>{
												 m_parallax_path,

												 tileset_collisiontile_path,
												 tileset_forest_path,
												 tileset_trees_path
											   };

	preLoadTextures(player_anim_directories);
	preLoadTextures(skeleton_anim_directories);
	preLoadTextures(other_directories);

	for (int i = 0; i < LEVELS_COUNT; i++)
	{
		m_levels.push_back(new Level(GameState::inst(),
			i,
			m_level_names[i],
			LEVEL_MAP_WIDTH,
			LEVEL_MAP_HEIGHT,
			m_level_paths[i],
			m_parallax_path,
			tileset_indices,
			group_names,
			group_indices,
			layer_names,
			parallax_names,
			parallax_speeds_x,
			parallax_speeds_y)
		);
	}

	player_sounds_path = m_assets_path + m_sounds_path + "knight/";
	player_textures_path = m_assets_path + m_textures_path + "knight/";

	m_player = new Player(GameState::inst(),
							player_sounds_path,
							player_textures_path,
						  player_animation_names,
						  player_anim_directories, 
						  player_animation_frames,
						  10.0f,
						  128.0f,
						  128.0f,
						  48.0f - 64.0f, 260.0f - 64.0f,
						  "Player1");

	enemy_sounds_path = m_assets_path + m_sounds_path + "skeleton/";
	enemy_textures_path = m_assets_path + m_textures_path + "skeleton/";

	m_levels_enemies[0].push_back(new Enemy(GameState::inst(),
									enemy_sounds_path,
									enemy_textures_path,
									skeleton_animation_names,
									skeleton_anim_directories,
									skeleton_animation_frames,
									10.0f,
									128.0f, 128.0f,
									368.0f - 64.0f, 260.0f - 64.0f,
									"Enemy1"));
	m_levels_enemies[0].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		592.0f - 64.0f, 260.0f - 64.0f,
		"Enemy2"));
	m_levels_enemies[0].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		624.0f - 64.0f, 260.0f - 64.0f,
		"Enemy3"));
	// No enemies for level 1
	m_levels_enemies[2].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		208.0f - 64.0f + 2 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy4"));
	m_levels_enemies[2].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		240.0f - 64.0f + 2 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy5"));
	m_levels_enemies[2].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		272.0f - 64.0f + 2 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy6"));

	m_levels_enemies[2].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		592.0f - 64.0f + 2 * LEVEL_OFFSET_X, 96.0f - 64.0f,
		"Enemy7"));
	m_levels_enemies[2].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		672.0f - 64.0f + 2 * LEVEL_OFFSET_X, 96.0f - 64.0f,
		"Enemy8"));
	// Level 3 no enemies
	// Level 4 no enemies
	m_levels_enemies[5].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		192.0f - 64.0f + 5 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy9"));
	m_levels_enemies[5].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		352.0f - 64.0f + 5 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy10"));
	m_levels_enemies[5].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		496.0f - 64.0f + 5 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy11"));
	m_levels_enemies[5].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		640.0f - 64.0f + 5 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy12"));
	m_levels_enemies[5].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		768.0f - 64.0f + 5 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy13"));
	m_levels_enemies[6].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		176.0f - 64.0f + 6 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy14"));
	m_levels_enemies[6].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		288.0f - 64.0f + 6 * LEVEL_OFFSET_X, 260.0f - 64.0f,
		"Enemy15"));
	m_levels_enemies[6].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		320.0f - 64.0f + 6 * LEVEL_OFFSET_X, 100.0f - 64.0f,
		"Enemy16"));
	m_levels_enemies[6].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		400.0f - 64.0f + 6 * LEVEL_OFFSET_X, 100.0f - 64.0f,
		"Enemy17"));
	m_levels_enemies[6].push_back(new Enemy(GameState::inst(),
		enemy_sounds_path,
		enemy_textures_path,
		skeleton_animation_names,
		skeleton_anim_directories,
		skeleton_animation_frames,
		10.0f,
		128.0f, 128.0f,
		720.0f - 64.0f + 6 * LEVEL_OFFSET_X, 100.0f - 64.0f,
		"Enemy18"));


	Camera::inst()->setZoom(1.0f);
	Camera::inst()->setBounds(0.0f, (float)(LEVELS_COUNT * (LEVEL_MAP_WIDTH * TILE_WIDTH) - CANVAS_WIDTH), 0.0f, (float)(LEVEL_MAP_HEIGHT * TILE_HEIGHT) - CANVAS_HEIGHT);

	m_current_level_index = 0;

	for (int i = 0; i < LEVELS_COUNT; i++)
	{
		m_levels[i]->init();
	}

	m_player->init();

	m_parallax_backgrounds.resize(parallax_names.size());

	for (int i = 0; i < m_parallax_backgrounds.size(); i++)
	{
		m_parallax_backgrounds[i] = new ParallaxBackground(GameState::inst(),
			parallax_names[i],
			m_parallax_path,
			(float)PARALLAX_WIDTH, (float)PARALLAX_HEIGHT,
			0.0f, 0.0f,
			(float)(50.0f * TILE_WIDTH), (float)(20.0f * TILE_HEIGHT),
			parallax_speeds_x[i], parallax_speeds_y[i],
			true, false);

		m_parallax_backgrounds[i]->init();
	}
	
	for (int i = 0; i < m_levels_enemies.size(); i++)
	{
		for (int j = 0; j < m_levels_enemies[i].size(); j++)
		{
			m_levels_enemies[i][j]->init();
		}
	}
}

void GameState::draw()
{
	m_current_level_index = (int)((m_player->getLeft()) / (LEVEL_MAP_WIDTH * TILE_WIDTH));

	for (int i = 0; i < m_parallax_backgrounds.size(); i++)
	{
		m_parallax_backgrounds[i]->draw();
	}

	if (m_current_level_index - 1 >= 0)
	{
		m_levels[m_current_level_index - 1]->draw();
	}

	m_levels[m_current_level_index]->draw();

	if (m_current_level_index + 1 < LEVELS_COUNT)
	{
		m_levels[m_current_level_index + 1]->draw();
	}

	if (m_current_level_index - 1 >= 0)
	{
		for (int i = 0; i < m_levels_enemies[m_current_level_index - 1].size(); i++)
		{
			m_levels_enemies[m_current_level_index - 1][i]->draw();
		}
	}

	for (int i = 0; i < m_levels_enemies[m_current_level_index].size(); i++)
	{
		m_levels_enemies[m_current_level_index][i]->draw();
	}

	if (m_current_level_index + 1 < LEVELS_COUNT)
	{
		for (int i = 0; i < m_levels_enemies[m_current_level_index + 1].size(); i++)
		{
			m_levels_enemies[m_current_level_index + 1][i]->draw();
		}
	}

	m_player->draw();
}

void GameState::preLoadTextures(const std::vector<std::string>& directories)
{
	// copy and remove slash
	std::vector<std::string> dirs(directories.size());
	for (int i = 0; i < directories.size(); i++)
	{
		dirs[i] = directories[i].substr(0, directories[i].length() - 1);
	}


	for (int i = 0; i < dirs.size(); i++)
	{
		graphics::preloadBitmaps(dirs[i]);
	}
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

void GameState::checkCollisionsWithGround(Area & area)
{
	m_current_level_index = (int)((m_player->getLeft()) / (LEVEL_MAP_WIDTH * TILE_WIDTH));

	if (m_current_level_index - 1 >= 0)
	{
		m_levels[m_current_level_index - 1]->checkCollisions(area);
	}

	m_levels[m_current_level_index]->checkCollisions(area);

	if (m_current_level_index + 1 < LEVELS_COUNT)
	{
		m_levels[m_current_level_index + 1]->checkCollisions(area);
	}
}

void GameState::checkCollisionWithPlayer(Area& area)
{
	if (collide(*(m_player->m_hurt_box), area))
	{
		area.resolveCollision(*(m_player->m_hurt_box));
	}
}

void GameState::checkCollisionsWithEnemies(Area& area)
{
	m_current_level_index = (int)((m_player->getLeft() + 58.0f) / (LEVEL_MAP_WIDTH * TILE_WIDTH));

	if (m_current_level_index - 1 >= 0)
	{
		for (int i = 0; i < m_levels_enemies[m_current_level_index - 1].size(); i++)
		{
			if (collide(*(m_levels_enemies[m_current_level_index - 1][i]->m_hurt_box), area))
			{
				area.resolveCollision(*(m_levels_enemies[m_current_level_index - 1][i]->m_hurt_box));
			}
		}
	}

	for (int i = 0; i < m_levels_enemies[m_current_level_index].size(); i++)
	{
		if (collide(*(m_levels_enemies[m_current_level_index][i]->m_hurt_box), area))
		{
			area.resolveCollision(*(m_levels_enemies[m_current_level_index][i]->m_hurt_box));
		}
	}

	if (m_current_level_index + 1 < LEVELS_COUNT)
	{
		for (int i = 0; i < m_levels_enemies[m_current_level_index + 1].size(); i++)
		{
			if (collide(*(m_levels_enemies[m_current_level_index + 1][i]->m_hurt_box), area))
			{
				area.resolveCollision(*(m_levels_enemies[m_current_level_index + 1][i]->m_hurt_box));
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

bool GameState::collide(Area& a, Area& b)
{

	if (a.getRight() > b.getLeft() && a.getLeft() < b.getRight() &&
		a.getBottom() > b.getTop() && a.getTop() < b.getBottom())
	{
		return true;
	}

	return false;
}
