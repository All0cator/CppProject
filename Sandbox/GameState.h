#pragma once

#include <string>
#include "Timer.h"
#include "Constants.h"
#include <unordered_map>
#include <vector>

class Player;
class Platform;
class Level;
class Box;

class GameState
{
private:

	GameState();
	static GameState * m_instance;
	std::string m_assets_path;
	std::string m_textures_path;
	std::string m_sounds_path;
	std::string m_levels_path;
	std::string m_tilesets_path;
	int m_window_width;
	int m_window_height;
	float m_canvas_width;
	float m_canvas_height;
	std::string m_window_title;
	
	// Maps index to graphic tile
	std::unordered_map<int, std::string > tiles;

	Timer * timer;

	Level* m_current_level;
	
	Player * m_player;

	// Player constants


	// Platform constants
	Platform* m_platform;

	std::vector<Box&> m_collision_group_dynamic;
	std::vector<Box&> m_collision_group_all;

	float m_min_right;
	float m_max_left;
	float m_min_bottom;
	float m_max_top;

public:
	float m_correction_x;
	float m_correction_y;

public:
	static GameState * inst();

	void update(float dt);
	void checkCollision();
	void init();
	void draw();

	void preLoadTextures(const std::vector<std::string>& directories);
	bool collide(Box& a, Box& b);
	void testCollisions();

	std::string getTexturesPath();
	std::string getSoundsPath();
	int getWindowWidth(); // In pixels
	int getWindowHeight(); // In pixels
	float getCanvasWidth(); // In canvas Units
	float getCanvasHeight(); // In canvas Units
	std::string getWindowTitle();
};