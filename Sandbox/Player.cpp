#include "Player.h"
#include "GameState.h"
#include "GraphicsConstants.h"
#include "Animation.h"
#include "Timer.h"
#include "Enemy.h"
#include "Area.h"
#include "Camera.h"
#include <iostream>

Player::Player(GameState* gs,
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
	m_sounds_path = sounds_path;
	m_textures_path = textures_path;

	this->m_texture_width = width_pixels;
	this->m_texture_half_width = width_pixels / 2.0f;
	this->m_texture_height = height_pixels;
	this->m_texture_half_height = height_pixels / 2.0f;

	m_ground_collider = new Area(21.0f, 16.0f, left_pixels + 44.0f, top_pixels + 64.0f, std::bind(&Player::ground_collider_callback, this, std::placeholders::_1), Area::AreaType::COLLIDER, Area::OriginType::PLAYER, this);
	m_hurt_box = new Area(8.0f, 31.0f, left_pixels + 58.0f, top_pixels + 42.0f, std::bind(&Player::hurt_box_callback, this, std::placeholders::_1), Area::AreaType::HURTBOX, Area::OriginType::PLAYER, this);
	m_hit_box = new Area(66.0f, 43.0f, left_pixels + 51.0f, top_pixels + 37.0f, std::bind(&Player::hit_box_callback, this, std::placeholders::_1), Area::AreaType::HITBOX, Area::OriginType::PLAYER, this);
	m_hit_box->m_is_active = false;
	m_jump_timer = new Timer(1.2f);
	m_invincibility_timer = new Timer(1.5f);
	m_attack_timer = new Timer(1.0f);

	m_hurt_sound_timer = new Timer(1.5f);
	m_attack_sound_timer = new Timer(0.5f, false, std::bind(&Player::attack_sound_timer_callback, this));
	m_attack_sound_timer->Stop();
}

void Player::attack_sound_timer_callback()
{
	if (m_is_enemy_hit)
	{
		graphics::playSound("assets/sounds/AttackHit2.wav", 0.3f, false);
		m_is_enemy_hit = false;
	}
	else
	{
		graphics::playSound("assets/sounds/AttackMiss2.wav", 0.3f, false);
	}
}

void Player::ground_collider_callback(Area& other)
{
	
	switch (other.m_type)
	{
	case Area::AreaType::TILE:
		switch (other.m_origin)
		{
		case Area::OriginType::LEVEL:
			m_is_grounded = true;
			break;
		}
		break;
	case Area::AreaType::SPIKE:
		switch (other.m_origin)
		{
		case Area::OriginType::LEVEL:
			m_is_grounded = true;
			break;
		}
		break;
	}
}

void Player::hurt_box_callback(Area& other)
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
			if (!m_hurt_sound_timer->IsRunning())
			{
				graphics::playSound("assets/sounds/Sspike.wav", 0.6f);
				m_hurt_sound_timer->Reset();
			}
			takeDmg(SPIKE_DMG);
			correctPos(other);
			break;
		}

		break;
	case Area::AreaType::HITBOX:

		switch (other.m_origin)
		{
		case Area::OriginType::ENEMY:
			takeDmg(static_cast<Enemy&>(*(other.m_origin_ptr)).getDmg());
			break;
		}

		break;
	}
}


void Player::hit_box_callback(Area& other)
{
	switch (other.m_type)
	{
	case Area::AreaType::HURTBOX:

		switch (other.m_origin)
		{
		case Area::OriginType::ENEMY:
			if (m_hit_box->m_is_active && static_cast<Enemy&>(*(other.m_origin_ptr)).m_can_interact)
			{
				m_is_enemy_hit = true;
				static_cast<Enemy&>(*(other.m_origin_ptr)).takeDmg(m_dmg);
			}
			break;
		}

		break;
	}
}

void Player::update(float dt) 
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
	updateState();
	updateAnimation();
	updateTimers(dt);
	updateMovement(dt);
	updateAreaDimensions(); // called before checking for collisions as we first move everything then check for collisions
	checkCollisions();
	
	if (m_is_attacking)
	{
		if (!m_attack_sound_timer->IsRunning() && m_is_first_hit)
		{
			m_attack_sound_timer->Reset();
			if (m_is_enemy_hit)
			{
				graphics::playSound("assets/sounds/AttackHit1.wav", 0.3f, false);
			}
			else
			{
				graphics::playSound("assets/sounds/AttackMiss1.wav", 0.3f, false);
			}
			m_is_first_hit = false;
		}
	}
	
	GameObject::update(dt);
}

void Player::updateInput()
{
	m_is_crouched = false;
	// Left movement of player
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		m_is_moving = true;
		if (m_orientation_x != -1)
		{
			m_is_turning_arround = true;
		}
		m_direction_x = -1.0f;
		m_velocity_x = 90.0f;
	}
	else if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		m_is_moving = true;
		if (m_orientation_x != 1)
		{
			m_is_turning_arround = true;
		}
		m_direction_x = 1.0f;
		m_velocity_x = 90.0f;
	}
	else
	{
		m_is_moving = false;
		m_direction_x = 0.0f;
	}

	// Up movement of player
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		if (m_is_grounded)
		{
			m_is_jumping = true;
			m_velocity_y = -150.0f;
			m_is_grounded = false;
		}
	}

	if (!m_jump_timer->IsRunning())
	{
		m_is_jumping = false;
		m_jump_timer->Reset();
	}

	// Down movement of player
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		if (m_is_grounded)
		{
			m_is_crouched = true;
		}

		m_velocity_y = 90.0f;
		m_is_jumping = false;

		m_orientation_y = 1;
	}

	if (!m_attack_timer->IsRunning())
	{
		m_is_attacking = false;
	}

	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		if (!m_is_attacking)
		{
			m_attack_timer->Reset();
			m_is_attacking = true;
			m_is_first_hit = true;
		}
	}
}

void Player::updateState()
{
	if (m_movement_state == State::DEAD) return;

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

	// Dead frames
	if (m_is_attacking && !m_animation_end)
	{
		m_hit_box->m_is_active = true;
		return;
	}
	if (m_movement_state == State::TRANSITION_FALL && !m_animation_end)
	{
		return;
	}
	if (m_movement_state == State::TRANSITION_CROUCH && !m_animation_end) return;

	if (m_is_turning_arround)
	{
		m_previous_movement_state = m_movement_state;
		m_movement_state = State::TURNING_ARROUND;
		return;
	}

	if(m_is_grounded)
	{
		if (m_is_crouched)
		{
			if (m_movement_state == State::GROUND)
			{
				m_previous_movement_state = m_movement_state;
				m_movement_state = State::TRANSITION_CROUCH;
				return;
			}

			m_previous_movement_state = m_movement_state;
			m_movement_state = State::CROUCH;
			return;
		}
		else
		{
			if (m_movement_state == State::CROUCH)
			{
				m_previous_movement_state = m_movement_state;
				m_movement_state = State::TRANSITION_CROUCH;
				return;
			}
			m_previous_movement_state = m_movement_state;
			m_movement_state = State::GROUND;
			return;
		}
	}
	else
	{
		if (m_is_jumping)
		{
			m_previous_movement_state = m_movement_state;
			m_movement_state = State::AIR;
			return;
		}
		else
		{
			if (m_previous_movement_state == State::AIR)
			{
				m_previous_movement_state = m_movement_state;
				m_movement_state = State::TRANSITION_FALL;
				return;
			}
			else
			{
				m_previous_movement_state = m_movement_state;
				m_movement_state = State::FALL;
				return;
			}
		}
	}
}

void Player::updateAnimation()
{
	switch (m_movement_state)
	{
	case State::DEAD:
		if (m_is_moving)
		{
			m_animation_end = playAnimation(KNIGHT_ANIM_DEATH);
		}
		else
		{
			m_animation_end = playAnimation(KNIGHT_ANIM_DEATHNOMOVEMENT);
		}

		if (m_animation_end)
		{
			m_is_disabled = true;
		}

		break;
	case State::HIT:
		m_animation_end = playAnimation(KNIGHT_ANIM_HIT);
		if (m_animation_end)
		{
			m_is_flickering = false;
		}
		break;
	case State::TURNING_ARROUND:
		if (m_previous_movement_state == State::GROUND)
		{
			m_animation_end = playAnimation(KNIGHT_ANIM_TURN_ARROUND);

			if (m_animation_end)
			{
				m_orientation_x *= -1;
				m_is_turning_arround = false;
			}
		}
		else
		{
			m_orientation_x *= -1;
			m_is_turning_arround = false;
		}
		
		break;
	case State::TRANSITION_CROUCH:
		m_animation_end = playAnimation(KNIGHT_ANIM_CROUCHTRANSITION);
		break;
	case State::CROUCH:

		if (m_is_attacking)
		{
			m_animation_end = playAnimation(KNIGHT_ANIM_CROUCHATTACK);
		} 
		else if (m_is_moving)
		{
			m_animation_end = playAnimation(KNIGHT_ANIM_CROUCHWALK);
		}
		else
		{
			m_animation_end = playAnimation(KNIGHT_ANIM_CROUCHIDLE);
		}
		break;
	case State::GROUND:
		if (m_is_attacking)
		{
			if (m_is_moving)
			{
				m_animation_end = playAnimation(KNIGHT_ANIM_ATTACKCOMBO2HIT);
			}
			else
			{
				m_animation_end = playAnimation(KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT);
			}
		}
		else
		{
			if (m_is_moving)
			{
				m_animation_end = playAnimation(KNIGHT_ANIM_RUN);
			}
			else
			{
				m_animation_end = playAnimation(KNIGHT_ANIM_IDLE);
			}
		}
		break;
	case State::AIR:
		if (m_is_attacking)
		{
			if (m_is_moving)
			{
				m_animation_end = playAnimation(KNIGHT_ANIM_ATTACKCOMBO2HIT);
			}
			else
			{
				m_animation_end = playAnimation(KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT);
			}
		}
		else
		{
			m_animation_end = playAnimation(KNIGHT_ANIM_JUMP);
		}
		
		break;
	case State::TRANSITION_FALL:
		m_animation_end = playAnimation(KNIGHT_ANIM_JUMPFALLINBETWEEN);
		break;
	case State::FALL:
		if (m_is_attacking)
		{
			if (m_is_moving)
			{
				if (m_current_animation_name != KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT)
				{
					m_animation_end = playAnimation(KNIGHT_ANIM_ATTACKCOMBO2HIT);
				}
			}
			else
			{
				if (m_current_animation_name != KNIGHT_ANIM_ATTACKCOMBO2HIT)
				{
					m_animation_end = playAnimation(KNIGHT_ANIM_ATTACKCOMBONOMOVEMENT);
				}
			}
		}
		else
		{
			m_animation_end = playAnimation(KNIGHT_ANIM_FALL);
		}
		break;
	}
}

void Player::updateTimers(float dt)
{
	updateAnimationTimer(dt);
	m_jump_timer->Update(dt);
	m_invincibility_timer->Update(dt);
	m_attack_timer->Update(dt);
	
	m_hurt_sound_timer->Update(dt);
	m_attack_sound_timer->Update(dt);
}

void Player::updateMovement(float dt)
{
	// Normalize movement direction if it is not 0
	if (m_direction_x != 0.0f && m_direction_y != 0.0f)
	{
		m_direction_length = std::sqrt(m_direction_x * m_direction_x + m_direction_y * m_direction_y);
		m_direction_x = m_direction_x / m_direction_length;
		m_direction_y = m_direction_y / m_direction_length;
	}

	m_x_axis_correction = true;
	setLeft(getLeft() + m_velocity_x * m_direction_x * dt);
	
	if (getLeft() + 58.0f < 0.0f)
	{
		setLeft(0.0f - 58.0f);
	}
	else if (getRight() - 58.0f > LEVELS_COUNT * (LEVEL_MAP_WIDTH * TILE_WIDTH))
	{
		setRight(LEVELS_COUNT * (LEVEL_MAP_WIDTH * TILE_WIDTH) + 58.0f);
	}

	updateAreaDimensions();
	m_state->checkCollisionsWithGround(*this->m_hurt_box);


	m_x_axis_correction = false;
	setTop(getTop() + 0.5f * m_acceleration_y * dt * dt + m_velocity_y * dt);

	updateAreaDimensions();
	m_state->checkCollisionsWithGround(*this->m_hurt_box);



	Camera::inst()->setFocalPointX(getLeft() + m_texture_half_width);
	Camera::inst()->setFocalPointY(getTop() + m_texture_half_height);

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

	if (m_velocity_y >= 0.0f)
	{
		m_direction_y = 1.0f;
	}
	else
	{
		m_direction_y = -1.0f;
	}
}

void Player::updateAreaDimensions()
{
	m_new_x_axis = (this->getLeft() + this->getRight()) / 2.0f;

	m_ground_collider->updatePositions(this->getLeft() + 44.0f, this->getTop() + 64.0f, m_new_x_axis);
	m_hurt_box->updatePositions(this->getLeft() + 58.0f, this->getTop() + 46.0f, m_new_x_axis);
	m_hit_box->updatePositions(this->getLeft() + 51.0f, this->getTop() + 37.0f, m_new_x_axis);

	if (m_orientation_x == -1)
	{
		m_ground_collider->flipX();
		m_hit_box->flipX();
	}
}

void Player::checkCollisions()
{
	m_state->checkCollisionsWithEnemies(*m_hit_box);
	m_state->checkCollisionsWithEnemies(*m_hurt_box);
	m_state->checkCollisionsWithGround(*m_ground_collider);
}

void Player::init() 
{
	graphics::setFont("assets/orange juice 2.0.ttf");
	SETCOLOR(m_debug_text.fill_color, 1.0f, 1.0f, 1.0f);
	m_debug_text.fill_opacity = 1.0f;

	m_movement_state = State::GROUND;
	m_previous_movement_state = State::GROUND;

	m_base_hp = 300.0f;
	m_base_dmg = 50.0f;
	
	m_hp = m_base_hp;
	m_dmg = m_base_dmg;

	m_orientation_x = 1;
	m_orientation_y = 1;
	m_direction_x = 0.0f;
	m_direction_y = 1.0f;

	m_velocity_x = 90.0f;
	m_acceleration_y = 150.0f;
	m_velocity_y = m_acceleration_y;
	m_max_velocity_y = 100.0f;

	m_is_moving = false;
	m_is_jumping = false;
	m_is_grounded = false;
	m_is_crouched = false;
	m_transitioning_crouch = false;
	m_is_attacking = false;
	m_can_interact = true;
	m_is_disabled = false;
	m_is_turning_arround = false;
	m_is_flickering = false;
	m_is_enemy_hit = false;
	m_is_first_hit = true;

	SETCOLOR(m_brush.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush.fill_opacity = 1.0f;
	m_brush.outline_opacity = 0.0f;
	m_brush.texture = "assets\\textures\\knight\\Idle\\0.png";

	m_jump_timer->Reset();
	m_invincibility_timer->Reset();

	GameObject::init();
}

void Player::draw() 
{
	if (m_is_disabled) return;

	m_brush.texture = /*"assets\\textures\\knight\\Idle\\0.png";*/getCurrentFrame();
	
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

		// Draw the Areas also

	if (m_state->m_is_debug_mode)
	{
		// Player Texture Box
		graphics::drawRect(graphics::windowToCanvasX(getLeft() - Camera::inst()->getFocalPointX() + m_texture_half_width, false),
							graphics::windowToCanvasY(getTop() - Camera::inst()->getFocalPointY() + m_texture_half_height, false),
							graphics::windowToCanvasX(m_texture_width, false),
							graphics::windowToCanvasY(m_texture_height, false),
							m_debug_box_brush);


		// Ground Collider
		graphics::drawRect(graphics::windowToCanvasX(m_ground_collider->getLeft() - Camera::inst()->getFocalPointX() + m_ground_collider->m_half_width_pixels, false),
							graphics::windowToCanvasY(m_ground_collider->getTop() - Camera::inst()->getFocalPointY() + m_ground_collider->m_half_height_pixels, false),
							graphics::windowToCanvasX(m_ground_collider->m_width_pixels, false),
							graphics::windowToCanvasY(m_ground_collider->m_height_pixels, false),
							m_ground_collider->m_debug_box_brush);


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
	}

	GameObject::draw();
}

Player::~Player() 
{
	delete m_ground_collider;
	delete m_hurt_box;
	delete m_hit_box;
	delete m_jump_timer;
	delete m_hurt_sound_timer;
	delete m_attack_sound_timer;
	delete m_invincibility_timer;
	delete m_attack_timer;
}

void Player::takeDmg(float ammount)
{
	if (!m_can_interact) return;

	if (!m_invincibility_timer->IsRunning())
	{
		m_hp -= ammount;
		m_is_flickering = true;
		m_invincibility_timer->Start();
	}
}

void Player::correctPos(Area & other)
{

	if (m_x_axis_correction)
	{
		if (m_direction_x > 0.0f)
		{
			this->setLeft(this->getLeft() - (m_hurt_box->getRight() - other.getLeft()));
			m_hurt_box->setRight(other.getLeft());
			m_velocity_x = 0.0f;
		}
		else if(m_direction_x < 0.0f)
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

	m_is_grounded = true;
}

float Player::getDmg()
{
	return m_dmg;
}
