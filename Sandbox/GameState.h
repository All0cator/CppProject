#pragma once

#include <string>
#include "Timer.h"
#include <unordered_map>

#define SETCOLOR(c, r, g, b) {c[0]=r; c[1]=g; c[2]=b;}

class Player;
class Platform;

class GameState
{
private:

	GameState();
	static GameState * m_instance;
	std::string m_assets_path;
	std::string m_textures_path;
	std::string m_sounds_path;
	int m_window_width;
	int m_window_height;
	float m_canvas_width;
	float m_canvas_height;
	std::string m_window_title;
	
	// Maps index to graphic tile
	std::unordered_map<int, std::string > tiles;

	Timer * timer;
	
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