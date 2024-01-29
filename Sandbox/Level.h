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

	//std::string m_sounds_path;
	std::string m_level_path;
	std::string m_parallax_path;
	std::vector<std::string> m_layer_tilesets_path;
	std::vector<std::string> m_layer_names;
	std::vector<std::string> m_parallax_names;
	std::vector<float> m_parallax_speeds_x;
	std::vector<float> m_parallax_speeds_y;

	//bool m_is_debug_mode;

public:
	Level(GameState* gs, 
		  const std::string& name = "",
		  const std::string& level_path,
		  const std::string& parallax_path,
		  const std::vector<std::string>& layer_tileset_paths,
		  const std::vector<std::string>& layer_names,
		  const std::vector<std::string>& parallax_names,
		  const std::vector<float>& parallax_speeds_x,
		  const std::vector<float>& parallax_speeds_y);
	virtual ~Level();
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;

	void preLoadTextures(const std::string& levelPath,
						 const std::string& parallaxPath);
	void parseLevelLayers();
	void playAmbience(float volume);
};