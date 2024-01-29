#pragma once

#include "GameObject.h"
#include "Actor.h"
#include "Box.h"

class Enemy : public GameObject, public Actor, public Box
{
private:
	float m_base_dmg;
	float m_dmg;

public:
	Enemy(GameState* gs,
		  const std::string& sounds_path,
		  const std::string& textures_path,
		  const std::vector<std::string>& animation_names,
		  const std::vector<unsigned int>& frames_per_animation,
		  float animation_speed_FPS,
		  float width_pixels,
		  float height_pixels,
		  float x_center_pixels,
		  float y_center_pixels,
		  const std::string& name,
		  float R = 1.0f,
		  float G = 0.0f,
		  float B = 0.0f);

	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;

	float getDmg();

	virtual ~Enemy();
};