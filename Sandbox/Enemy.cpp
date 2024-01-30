#include "Enemy.h"
#include "GameState.h"
#include "GraphicsConstants.h"
#include "Animation.h"
#include "Timer.h"
#include "Player.h"
#include "Area.h"

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
	m_full_textures_path = m_state->inst()->getTexturesPath() + textures_path;
	m_full_sounds_path = m_state->inst()->getSoundsPath() + sounds_path;
}

void Enemy::update(float dt)
{
	if (m_is_disabled) return;

	if (m_movement_state != State::DEAD)
	{
		updateInput();
	}
	updateState();
	updateAnimation();
	updateTimers(dt);
	updateMovement(dt);

	GameObject::update(dt);
}

void Enemy::updateInput()
{

}

void Enemy::updateState()
{
}

void Enemy::updateAnimation()
{
}

void Enemy::updateTimers(float dt)
{
}

void Enemy::updateMovement(float dt)
{
}

void Enemy::takeDmg(float ammount)
{

}

void Enemy::correctPos(Box& other)
{

}

void Enemy::init()
{

	GameObject::init();
}

void Enemy::draw()
{
	if (m_is_disabled) return;

	m_brush.texture = getCurrentFrame().m_path_to_frame;

	graphics::setScale((float)m_orientation_x, 1.0f);

	graphics::drawRect(m_pos_x, m_pos_y,
		m_size_width, m_size_height,
		m_brush);

	graphics::resetPose();

	GameObject::draw();
}

float Enemy::getDmg()
{
	return m_dmg;
}

Enemy::~Enemy()
{
	delete m_invincibility_timer;
	delete m_front_collider;
}
