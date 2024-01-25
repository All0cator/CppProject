#pragma once

#include <string>
#include "Timer.h"
#include "Constants.h"
#include <unordered_map>

class Player;
class Platform;
class Level;

class GameState
{
private:

	GameState();
	static GameState * m_instance;
	std::string m_assets_path;
	std::string m_textures_path;
	std::string m_sounds_path;
	std::string m_levels_path;
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

	Platform* m_platform;

	// Platform constants

public:
	static GameState * inst();

	void update(float dt);
	void init();
	void draw();

	std::string getTexturesPath();
	std::string getSoundsPath();
	int getWindowWidth(); // In pixels
	int getWindowHeight(); // In pixels
	float getCanvasWidth(); // In canvas Units
	float getCanvasHeight(); // In canvas Units
	std::string getWindowTitle();
};