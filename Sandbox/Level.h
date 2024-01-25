#pragma once

#include "GameObject.h"

class ParallaxBackground;
class Layer;

class Level : public GameObject
{
private:
	std::vector<ParallaxBackground*> m_parallax_backgrounds;
	std::vector<Layer*> m_environment_layers;
	//std::vector<Layer*> collision_layers;

	std::string m_sounds_path;
	std::string m_level_path;

public:
	Level(GameState* gs, 
		  const std::string& name = "",
		  const std::string& levelPath,
		  const std::string& parallaxPath,
		  std::vector<std::string> groupNames,
		  std::vector<std::string> layerNames,
		  std::vector<std::string> parallaxNames);
	virtual ~Level();
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;

	void preLoadTextures();
	void parseLevelLayers();
	void playAmbience(float volume);
};