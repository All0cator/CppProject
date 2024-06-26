#include "Enemy.h"
#include "GameState.h"
#include "GraphicsConstants.h"
#include "Animation.h"
#include "Timer.h"
#include "Player.h"
#include "Area.h"
#include "Camera.h"

Enemy::Enemy(GameState* gs,
			 const std::string& sounds_path,
			 const std::string& textures_path,
			 const std::vector<std::string>& animation_names,
			 const std::vector<std::string>& animation_directories,
			 const std::vector<unsigned int>& frames_per_animation,
			 float animation_speed_FPS,
			 float width_pixels,
			 float height_pixels,
			 float left_pixels,
			 float top_pixels,
			 const std::string& name,
			 float R,
			 float G,
			 float B) 
	: GameObject(gs, name),
	  Actor(animation_names, animation_directories, frames_per_animation, animation_speed_FPS),
	  Box(width_pixels, height_pixels, left_pixels, top_pixels, R, G, B) 
{
	m_textures_path = textures_path;
	m_sounds_path = sounds_path;

	this->m_texture_width = width_pixels;
	this->m_texture_half_width = width_pixels / 2.0f;
	this->m_texture_height = height_pixels;
	this->m_texture_half_height = height_pixels / 2.0f;

	m_hurt_box = new Area(22.0f, 31.0f, left_pixels + 58.0f, top_pixels + 46.0f, std::bind(&Enemy::hurt_box_callback, this, std::placeholders::_1), Area::AreaType::HURTBOX, Area::OriginType::ENEMY, this);
	m_hit_box = new Area(40.0f, 31.0f, left_pixels + 54.0f, top_pixels + 47.0f, std::bind(&Enemy::hit_box_callback, this, std::placeholders::_1), Area::AreaType::HITBOX, Area::OriginType::ENEMY, this);
	m_notice_area = new Area(width_pixels * 1.5f, height_pixels * 1.5f, left_pixels - 0.75f * width_pixels, top_pixels - 0.75f * height_pixels, std::bind(&Enemy::noticeAreaCallback, this, std::placeholders::_1), Area::AreaType::COLLIDER, Area::OriginType::ENEMY, this);

	m_invincibility_timer = new Timer(1.5f);
	m_sound_timer = new Timer(1.5f);
}

void Enemy::hurt_box_callback(Area& other)
{
	switch (other.m_type)
	{
	case Area::AreaType::TILE:

		switch (other.m_origin)
		{
		case Area::OriginType::LEVEL:
			correctPos(other);
			break;
		}

		break;
	case Area::AreaType::SPIKE:
		switch (other.m_origin)
		{
		case Area::OriginType::LEVEL:
			correctPos(other);
			break;
		}
		break;
	case Area::AreaType::HITBOX:

		switch (other.m_origin)
		{
		case Area::OriginType::PLAYER:
			takeDmg(static_cast<Player&>(*other.m_origin_ptr).getDmg());
			break;
		}

		break;
	}
}

void Enemy::hit_box_callback(Area& other)
{
	switch (other.m_type)
	{
	case Area::AreaType::HURTBOX:

		switch (other.m_origin)
		{
		case Area::OriginType::PLAYER:
			if (static_cast<Player&>(*(other.m_origin_ptr)).m_can_interact)
			{
				m_is_attacking = true;
				static_cast<Player&>(*other.m_origin_ptr).takeDmg(m_dmg);
			}
			break;
		}

		break;
	}
}

void Enemy::noticeAreaCallback(Area& other)
{
	switch (other.m_type)
	{
	case Area::AreaType::HURTBOX:
		
		switch (other.m_origin)
		{
		case Area::OriginType::PLAYER:

			if (static_cast<Player&>(*(other.m_origin_ptr)).m_can_interact)
			{
				m_orientation_x = static_cast<Player&>(*(other.m_origin_ptr)).getLeft() - this->getLeft() > 0.0f ? 1 : -1;
				m_is_moving = true;
				m_velocity_x = 50.0f;
			}
			flipAreasX();

			break;
		}
		
		break;
	}
}

void Enemy::update(float dt)
{
	if (m_is_disabled) return;

	if (m_movement_state != State::DEAD)
	{
		updateInput();
		if (m_velocity_y >= 0.0f)
		{
			m_direction_y = 1.0f;
		}
		else
		{
			m_direction_y = -1.0f;
		}
	}
	m_state->checkCollisionWithPlayer(*this->m_notice_area);
	updateState();
	updateAnimation();
	updateTimers(dt);
	updateMovement(dt);
	updateAreaDimensions();
	checkCollisions();

	GameObject::update(dt);
}

void Enemy::updateInput()
{
	m_is_moving = false;

	if (m_orientation_x > 0.0f)
	{
		m_direction_x = 1.0f;
	}
	else // m_orientation_x < 0.0f
	{
		m_direction_x = -1.0f;
	}
}
#include <iostream>
void Enemy::updateState()
{
	if (m_hp <= 0.0f)
	{
		m_movement_state = State::DEAD;
		m_can_interact = false;
		return;
	}
	m_hit_box->m_is_active = false;

	if (m_is_flickering)
	{
		m_movement_state = State::HIT;
		return;
	}


	if (m_is_attacking) 
	{ 
		m_movement_state = State::ATTACK;  
		m_is_moving = false;
		m_hit_box->m_is_active = true; 
		return; 
	}

	if (m_is_moving)
	{
		m_movement_state = State::WALK;
	}
	else
	{
		m_movement_state = State::IDLE;
	}
}

void Enemy::updateAnimation()
{
	switch (m_movement_state)
	{
	case State::DEAD:
		m_animation_end = playAnimation(SKELETON_ANIM_DEATH);

		if (m_animation_end) m_is_disabled = true;

		break;
	case State::IDLE:
		m_animation_end = playAnimation(SKELETON_ANIM_IDLE);
		break;
	case State::WALK:
		m_animation_end = playAnimation(SKELETON_ANIM_WALK);
		break;
	case State::HIT:
		m_animation_end = playAnimation(SKELETON_ANIM_HIT);
		if (m_animation_end)
		{
			m_is_flickering = false;
		}
		break;
	case State::ATTACK:
		m_animation_end = playAnimation(SKELETON_ANIM_ATTACK);
		if (m_animation_end)
		{
			m_is_attacking = false;
		}
		break;
	}
}

void Enemy::updateTimers(float dt)
{
	updateAnimationTimer(dt);
	m_invincibility_timer->Update(dt);
	m_sound_timer->Update(dt);
}

void Enemy::updateMovement(float dt)
{
	// Normalize movement direction if it is not 0
	if (m_direction_x != 0.0f || m_direction_y != 0.0f)
	{
		m_direction_length = std::sqrt(m_direction_x * m_direction_x + m_direction_y * m_direction_y);
		m_direction_x = m_direction_x / m_direction_length;
		m_direction_y = m_direction_y / m_direction_length;
	}
	if (!m_is_moving) return;

	m_x_axis_correction = true;
	setLeft(getLeft() + m_velocity_x * m_direction_x * dt);
	updateAreaDimensions();
	m_state->checkCollisionsWithGround(*this->m_hurt_box);


	m_x_axis_correction = false;
	setTop(getTop() + 0.5f * m_acceleration_y * dt * dt + m_velocity_y * dt);
	updateAreaDimensions();
	m_state->checkCollisionsWithGround(*this->m_hurt_box);

	// updating velocity for x makes movement slippery
	m_velocity_y += m_acceleration_y * dt;

	if (m_velocity_y > m_max_velocity_y)
	{
		m_velocity_y = m_max_velocity_y;
	}
	else if (m_velocity_y < -m_max_velocity_y)
	{
		m_velocity_y = -m_max_velocity_y;
	}
}

void Enemy::updateAreaDimensions()
{
	m_new_x_axis = (this->getLeft() + this->getRight()) / 2.0f;

	m_hurt_box->updatePositions(this->getLeft() + 58.0f, this->getTop() + 46.0f, m_new_x_axis);
	m_hit_box->updatePositions(this->getLeft() + 54.0f, this->getTop() + 47.0f, m_new_x_axis);
	m_notice_area->updatePositions(this->getLeft() -  0.25f * m_texture_width, this->getTop() - 0.25f * m_texture_height, m_new_x_axis);

	if (m_orientation_x == -1)
	{
		m_hit_box->flipX();
		m_notice_area->flipX();
	}
}

void Enemy::checkCollisions()
{
	m_state->checkCollisionWithPlayer(*m_hit_box);
	m_state->checkCollisionWithPlayer(*m_hurt_box);
}

void Enemy::flipAreasX()
{
	m_hit_box->flipX();
	m_notice_area->flipX();
}

void Enemy::takeDmg(float ammount)
{
	if (!m_can_interact) return;

	if (!m_invincibility_timer->IsRunning())
	{
		if (!m_sound_timer->IsRunning())
		{
			graphics::playSound("assets/sounds/Sdeath.wav", 1.0f, false);
			m_sound_timer->Reset();
		}
		m_hp -= ammount;
		m_is_flickering = true;
		m_invincibility_timer->Start();
	}
}

void Enemy::correctPos(Area& other)
{
	if (m_x_axis_correction)
	{
		if (m_direction_x > 0.0f)
		{
			this->setLeft(this->getLeft() - (m_hurt_box->getRight() - other.getLeft()));
			m_hurt_box->setRight(other.getLeft());
			m_velocity_x = 0.0f;
		}
		else if (m_direction_x < 0.0f)
		{
			this->setLeft(this->getLeft() + (other.getRight() - m_hurt_box->getLeft()));
			m_hurt_box->setLeft(other.getRight());
			m_velocity_x = 0.0f;
		}
	}
	else
	{
		if (m_velocity_y > 0.0f)
		{
			this->setTop(this->getTop() - (m_hurt_box->getBottom() - other.getTop()));
			m_hurt_box->setBottom(other.getTop());
			m_velocity_y = 0.0f;
		}
		else if (m_velocity_y < 0.0f)
		{
			this->setTop(this->getTop() + (other.getBottom() - m_hurt_box->getTop()));
			m_hurt_box->setTop(other.getBottom());
			m_velocity_y = 0.0f;
		}
	}
}

void Enemy::init()
{
	m_movement_state = State::IDLE;

	m_base_hp = 100.0f;
	m_base_dmg = 30.0f;

	m_hp = m_base_hp;
	m_dmg = m_base_dmg;

	m_orientation_x = -1;
	m_orientation_y = 1;
	flipAreasX(); // Areas are set facing right at first but we flip sprite to left here so we need to flip all the areas accordingly
	m_direction_x = 0.0f;
	m_direction_y = 0.0f;

	m_velocity_x = 50.0f;
	m_acceleration_y = 150.0f;
	m_velocity_y = m_acceleration_y;
	m_max_velocity_y = 100.0f;

	m_is_moving = false;
	m_is_attacking = false;
	m_animation_end = false;
	m_can_interact = true;
	m_is_disabled = false;
	m_is_flickering = false;

	SETCOLOR(m_brush.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush.fill_opacity = 1.0f;
	m_brush.outline_opacity = 0.0f;
	m_brush.texture = m_textures_path + "Idle/0.png";

	m_invincibility_timer->Reset();

	GameObject::init();
}

void Enemy::draw()
{
	if (m_is_disabled) return;

	m_brush.texture = getCurrentFrame();

	if (m_is_flickering)
	{
		m_brush.fill_opacity = std::cos(std::fmod(m_invincibility_timer->GetAccumulatedTime(), 1.0f));
	}

	graphics::setScale((float)m_orientation_x, 1.0f);

	graphics::drawRect(graphics::windowToCanvasX(getLeft() - Camera::inst()->getFocalPointX() + m_texture_half_width, false),
		graphics::windowToCanvasY(getTop() - Camera::inst()->getFocalPointY() + m_texture_half_height, false),
		graphics::windowToCanvasX(m_texture_width, false),
		graphics::windowToCanvasY(m_texture_height, false),
		m_brush);

	graphics::resetPose();

	if (m_state->m_is_debug_mode)
	{
		// Draw the Areas also

		// Enemy Texture Box
		graphics::drawRect(graphics::windowToCanvasX(getLeft() - Camera::inst()->getFocalPointX() + m_texture_half_width, false),
			graphics::windowToCanvasY(getTop() - Camera::inst()->getFocalPointY() + m_texture_half_height, false),
			graphics::windowToCanvasX(m_texture_width, false),
			graphics::windowToCanvasY(m_texture_height, false),
			m_debug_box_brush);

		// Hurt Box
		graphics::drawRect(graphics::windowToCanvasX(m_hurt_box->getLeft() - Camera::inst()->getFocalPointX() + m_hurt_box->m_half_width_pixels, false),
			graphics::windowToCanvasY(m_hurt_box->getTop() - Camera::inst()->getFocalPointY() + m_hurt_box->m_half_height_pixels, false),
			graphics::windowToCanvasX(m_hurt_box->m_width_pixels, false),
			graphics::windowToCanvasY(m_hurt_box->m_height_pixels, false),
			m_hurt_box->m_debug_box_brush);

		// Hit Box
		graphics::drawRect(graphics::windowToCanvasX(m_hit_box->getLeft() - Camera::inst()->getFocalPointX() + m_hit_box->m_half_width_pixels, false),
			graphics::windowToCanvasY(m_hit_box->getTop() - Camera::inst()->getFocalPointY() + m_hit_box->m_half_height_pixels, false),
			graphics::windowToCanvasX(m_hit_box->m_width_pixels, false),
			graphics::windowToCanvasY(m_hit_box->m_height_pixels, false),
			m_hit_box->m_debug_box_brush);

		// Notice Area
		graphics::drawRect(graphics::windowToCanvasX(m_notice_area->getLeft() - Camera::inst()->getFocalPointX() + m_notice_area->m_half_width_pixels, false),
			graphics::windowToCanvasY(m_notice_area->getTop() - Camera::inst()->getFocalPointY() + m_notice_area->m_half_height_pixels, false),
			graphics::windowToCanvasX(m_notice_area->m_width_pixels, false),
			graphics::windowToCanvasY(m_notice_area->m_height_pixels, false),
			m_notice_area->m_debug_box_brush);
	}

	GameObject::draw();
}

float Enemy::getDmg()
{
	return m_dmg;
}

Enemy::~Enemy()
{
	delete m_invincibility_timer;
	delete m_sound_timer;
	delete m_hurt_box;
	delete m_hit_box;
	delete m_notice_area;
}