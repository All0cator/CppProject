#pragma once

#include <string>
#include "Timer.h"
#include "Constants.h"
#include <unordered_map>
#include <vector>

class Player;
class Level;
class Area;
class Box;
class Tileset;
class Enemy;
class Timer;

class GameState
{
private:

	GameState();
	static GameState * m_instance;
	std::string m_assets_path;
	std::string m_textures_path;
	std::string m_sounds_path;
	std::string m_tilesets_path;


	std::string m_levels_path;
	std::string m_level0_path;
	std::vector<std::string> group_names;
	std::vector<int> group_indices;
	std::vector<std::string> layer_names;
	std::vector<std::string> tileset_paths;
	std::vector<int> tileset_max_indices;

	std::string tileset_collisiontile_path;
	std::string tileset_forest_path;
	std::string tileset_trees_path;
	std::vector<int> tileset_indices;

	std::string m_parallax_path;
	std::vector<std::string> parallax_names;
	std::vector<float> parallax_speeds_x;
	std::vector<float> parallax_speeds_y;
	std::string m_knight_path;
	std::string m_skeleton_path;

	std::vector<std::string> player_anim_directories;
	std::vector<std::string> player_animation_names;
	std::vector<unsigned int> player_animation_frames;
	std::vector<std::string> skeleton_anim_directories;
	std::vector<std::string> skeleton_animation_names;
	std::vector<unsigned int> skeleton_animation_frames;
	std::vector<std::string> other_directories;

	std::string player_sounds_path;
	std::string player_textures_path;

	std::string enemy_sounds_path;
	std::string enemy_textures_path;


	int m_window_width;
	int m_window_height;
	float m_canvas_width;
	float m_canvas_height;
	std::string m_window_title;

	Timer* m_toggle_timer;

	Level* m_current_level;
	
	Player * m_player;
	std::vector<Enemy*> m_enemies;
	std::vector<Level*> m_levels;
	std::vector<Tileset*> m_tilesets;

	float m_min_right;
	float m_max_left;
	float m_min_bottom;
	float m_max_top;


public:
	bool m_is_debug_mode;
	float m_correction_x;
	float m_correction_y;

public:
	static GameState * inst();
	~GameState();

	void update(float dt);
	void init();
	void draw();

	void preLoadTextures(const std::vector<std::string>& directories);
	void checkCollisionsWithGround(Area& area);
	void checkCollisionWithPlayer(Area& area);
	void checkCollisionsWithEnemies(Area& area);
	void createTilesets(const std::vector<std::string>& tileset_paths,
						const std::vector<int>& tileset_max_indices);
	void createLevels();
	bool collide(Area& a, Area& b);
	void testCollisions();

	std::string getTexturesPath();
	std::string getSoundsPath();
	Tileset* getTileset(int index);
	int getWindowWidth(); // In pixels
	int getWindowHeight(); // In pixels
	float getCanvasWidth(); // In canvas Units
	float getCanvasHeight(); // In canvas Units
	std::string getWindowTitle();
};