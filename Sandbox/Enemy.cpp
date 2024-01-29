#include "Enemy.h"

Enemy::Enemy(GameState* gs,
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
			 float R,
			 float G,
			 float B) 
	: GameObject(gs, name),
	  Actor(animation_names, frames_per_animation, animation_speed_FPS),
	  Box(width_pixels, height_pixels, x_center_pixels, y_center_pixels, R, G, B) 
{

}

void Enemy::update(float dt)
{


	GameObject::update(dt);
}

void Enemy::init()
{

	GameObject::init();
}

void Enemy::draw()
{

	GameObject::draw();
}

float Enemy::getDmg()
{
	return m_dmg;
}

Enemy::~Enemy()
{
}
