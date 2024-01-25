#include "Level.h"

Level::Level(GameState* gs,
			 const std::string& name = "",
			 const std::string& levelPath,
			 const std::string& parallaxPath,
			 std::vector<std::string> groupNames,
			 std::vector<std::string> layerNames,
			 std::vector<std::string>)
	: GameObject(gs, name)
{
	preLoadTextures(levelPath, parallaxPath);
}

Level::~Level()
{
}

void Level::update(float dt)
{
}

void Level::init()
{
}

void Level::draw()
{
}
