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

	m_side_collider = new Area(12.0f, 32.0f, left_pixels + 69.0f, top_pixels + 47.0f, std::bind(&Enemy::side_collider_callback, this, std::placeholders::_1), Area::AreaType::COLLIDER, Area::OriginType::ENEMY, this);
	m_hurt_box = new Area(22.0f, 32.0f, left_pixels + 55.0f, top_pixels + 47.0f, std::bind(&Enemy::hurt_box_callback, this, std::placeholders::_1), Area::AreaType::HURTBOX, Area::OriginType::ENEMY, this);
	m_hit_box = new Area(45.0f, 24.0f, left_pixels + 54.0f, top_pixels + 47.0f, std::bind(&Enemy::hit_box_callback, this, std::placeholders::_1), Area::AreaType::HITBOX, Area::OriginType::ENEMY, this);
	m_notice_area = new Area(width_pixels * 5.0f, height_pixels * 5.0f, left_pixels - 2.5f * width_pixels, top_pixels - 2.5f * height_pixels, std::bind(&Enemy::noticeAreaCallback, this, std::placeholders::_1), Area::AreaType::COLLIDER, Area::OriginType::ENEMY, this);

	m_invincibility_timer = new Timer(0.5f);
}

void Enemy::side_collider_callback(Area& other)
{
	switch (other.m_type)
	{
	case Area::AreaType::TILE:

		switch (other.m_origin)
		{
		case Area::OriginType::LEVEL:
			m_direction_x *= -1;
			break;
		}

		break;
	}
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
	case Area::AreaType::HURTBOX:

		switch (other.m_origin)
		{
		case Area::OriginType::PLAYER:
			static_cast<Player&>(*other.m_origin_ptr).takeDmg(m_dmg);
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
			static_cast<Player&>(*other.m_origin_ptr).takeDmg(m_dmg);
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

			m_orientation_x = static_cast<Player&>(*(other.m_origin_ptr)).getLeft() - this->getLeft() > 0.0f ? 1 : -1;
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
	}
	updateState();
	updateAnimation();
	updateTimers(dt);
	updateMovement(dt);
	updateAreaDimensions();
	checkCollisions();
	updateAreaDimensions(); // We might have moved in collisions so we need to adjust everything again

	GameObject::update(dt);
}

void Enemy::updateInput()
{
	m_direction_x = (float)m_orientation_x;
}

void Enemy::updateState()
{
	if (m_hp <= 0.0f)
	{
		m_movement_state = State::DEAD;
		m_can_interact = false;
		return;
	}

	if (m_is_flickering)
	{
		m_movement_state = State::HIT;
		return;
	}

	m_hit_box->m_is_active = false;

	if (m_is_attacking && !m_animation_end) 
	{ 
		m_movement_state = State::ATTACK;  
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
		break;
	case State::ATTACK:
		m_animation_end = playAnimation(SKELETON_ANIM_ATTACK);
		break;
	}
}

void Enemy::updateTimers(float dt)
{
	updateAnimationTimer(dt);
	m_invincibility_timer->Update(dt);
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


	setLeft(getLeft() + m_velocity_x * m_direction_x * dt);
	setTop(getTop() + m_velocity_y * m_direction_y * dt);
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

	m_side_collider->updatePositions(this->getLeft() + 69.0f, this->getTop() + 47.0f, m_new_x_axis);
	m_hurt_box->updatePositions(this->getLeft() + 55.0f, this->getRight() + 47.0f, m_new_x_axis);
	m_hit_box->updatePositions(this->getLeft() + 54.0f, this->getTop() + 47.0f, m_new_x_axis);
	m_notice_area->updatePositions(this->getLeft() - 2.5f * m_texture_width, this->getTop() - 2.5f * m_texture_height, m_new_x_axis);
}

void Enemy::checkCollisions()
{
	m_state->checkCollisionWithPlayer(*m_hit_box);
	m_state->checkCollisionWithPlayer(*m_hurt_box);
	m_state->checkCollisionsWithGround(*m_side_collider);
	m_state->checkCollisionWithPlayer(*m_notice_area);
}

void Enemy::flipAreasX()
{
	m_side_collider->flipX();
	m_hurt_box->flipX();
	m_hit_box->flipX();
	m_notice_area->flipX();
}

void Enemy::takeDmg(float ammount)
{
	if (!m_can_interact) return;

	if (!m_invincibility_timer->IsRunning())
	{
		m_hp -= ammount;
		m_is_flickering = true;
		m_invincibility_timer->Start();
	}
}

void Enemy::correctPos(Area& other)
{
	setLeft(getLeft() - m_orientation_x * GameObject::m_state->inst()->m_correction_x);
	setTop(getTop() - m_orientation_y * GameObject::m_state->inst()->m_correction_y);
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

	m_velocity_x = 90.0f;
	m_acceleration_y = 6.0f;
	m_velocity_y = m_acceleration_y;
	m_max_velocity_y = 6.0f;

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

	graphics::drawRect(graphics::windowToCanvasX(getLeft() + m_texture_half_width, false),
		graphics::windowToCanvasY(getTop() + m_texture_half_height, false),
		graphics::windowToCanvasX(m_texture_width, false),
		graphics::windowToCanvasY(m_texture_height, false),
		m_brush);

	graphics::resetPose();

	if (m_state->m_is_debug_mode)
	{
		// Draw the Areas also

		// Enemy Texture Box
		graphics::drawRect(graphics::windowToCanvasX(getLeft() + m_texture_half_width, false),
			graphics::windowToCanvasY(getTop() + m_texture_half_height, false),
			graphics::windowToCanvasX(m_texture_width, false),
			graphics::windowToCanvasY(m_texture_height, false),
			m_debug_box_brush);


		// Side Collider
		graphics::drawRect(graphics::windowToCanvasX(m_side_collider->getLeft() + m_side_collider->m_half_width_pixels, false),
			graphics::windowToCanvasY(m_side_collider->getTop() + m_side_collider->m_half_height_pixels, false),
			graphics::windowToCanvasX(m_side_collider->m_width_pixels, false),
			graphics::windowToCanvasY(m_side_collider->m_height_pixels, false),
			m_side_collider->m_debug_box_brush);


		// Hurt Box
		graphics::drawRect(graphics::windowToCanvasX(m_hurt_box->getLeft() + m_hurt_box->m_half_width_pixels, false),
			graphics::windowToCanvasY(m_hurt_box->getTop() + m_hurt_box->m_half_height_pixels, false),
			graphics::windowToCanvasX(m_hurt_box->m_width_pixels, false),
			graphics::windowToCanvasY(m_hurt_box->m_height_pixels, false),
			m_hurt_box->m_debug_box_brush);

		// Hit Box
		graphics::drawRect(graphics::windowToCanvasX(m_hit_box->getLeft() + m_hit_box->m_half_width_pixels, false),
			graphics::windowToCanvasY(m_hit_box->getTop() + m_hit_box->m_half_height_pixels, false),
			graphics::windowToCanvasX(m_hit_box->m_width_pixels, false),
			graphics::windowToCanvasY(m_hit_box->m_height_pixels, false),
			m_hit_box->m_debug_box_brush);

		// Notice Area
		graphics::drawRect(graphics::windowToCanvasX(m_notice_area->getLeft() + m_notice_area->m_half_width_pixels, false),
			graphics::windowToCanvasY(m_notice_area->getTop() + m_notice_area->m_half_height_pixels, false),
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
	delete m_side_collider;
	delete m_hurt_box;
	delete m_hit_box;
	delete m_notice_area;
}