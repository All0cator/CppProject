#include "GameState.h"
#include "Player.h"
#include "Platform.h"

#include <iostream>

GameState* GameState::m_instance = nullptr;

GameState::GameState()
{
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

	if (timer->IsRunning())
	{
		timer->Update(dt);
		std::cout << timer->GetAccumulatedTime() << std::endl;
	}

	m_player->update(deltaTime);
	m_platform->update(deltaTime);
}

void GameState::init()
{
	timer = new Timer(2.0f, false, nullptr);
	timer->Start();

	m_assets_path = "assets/";
	m_textures_path = "textures/";
	m_sounds_path = "sounds/";

	m_window_width = 800;
	m_window_height = 800;
	m_window_title = "Project Cpp";

	m_canvas_width = 10.0f;
	m_canvas_height = 10.0f;

	m_player = new Player(GameState::inst(), "player/", "player/boy2.png", "Player");
	m_platform = new Platform(GameState::inst(), "", "blocks/red_block.png", "Platform");

	m_player->init();
	m_platform->init();
}

void GameState::draw()
{
	m_platform->draw();
	m_player->draw();
}

std::string GameState::getTexturesPath()
{
	return m_assets_path + m_textures_path;
}

std::string GameState::getSoundsPath()
{
	return m_assets_path + m_sounds_path;
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