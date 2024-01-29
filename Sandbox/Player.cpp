#include "Player.h"
#include "GameState.h"
#include "GraphicsConstants.h"
#include "Animation.h"
#include "Timer.h"
#include "Enemy.h"

Player::Player(GameState* gs,
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
			   float B = 0.0f)
	: GameObject(gs, name),
	  Actor(animation_names, frames_per_animation, animation_speed_FPS),
	  Box(width_pixels, height_pixels, x_center_pixels, y_center_pixels, R, G, B)
{
	m_full_textures_path = m_state->inst()->getTexturesPath() + textures_path;
	m_full_sounds_path = m_state->inst()->getSoundsPath() + sounds_path;
}

void Player::update(float dt) 
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
	}
	else if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		m_is_moving = true;
		if (m_orientation_x != 1)
		{
			m_is_turning_arround = true;
		}
		m_direction_x = 1.0f;
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
			m_direction_y = -1.0f;
			m_orientation_y = -1;
		}
	}

	// Down movement of player
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		if (m_is_grounded)
		{
			m_is_crouched = true;
		}

		m_is_jumping = false;
		m_direction_y = 1.0f;
		m_orientation_y = 1;
	}

	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		m_is_attacking = true;
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

	// Dead frames
	if (m_movement_state == State::TRANSITION_FALL && !m_animation_end) return;
	if (m_movement_state == State::TRANSITION_CROUCH && !m_animation_end) return;
	if (m_is_attacking && !m_animation_end) return;

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
			if (m_movement_state != State::CROUCH)
			{
				m_movement_state = State::TRANSITION_CROUCH;
				return;
			}
			m_movement_state = State::CROUCH;
			return;
		}
		else
		{
			if (m_movement_state == State::CROUCH)
			{
				m_movement_state = State::TRANSITION_CROUCH;
				return;
			}

			m_movement_state = State::GROUND;
			return;
		}
	}
	else
	{
		if (m_is_jumping)
		{
			m_movement_state = State::AIR;
			return;
		}
		else
		{
			if (m_movement_state == State::AIR)
			{
				m_movement_state = State::TRANSITION_FALL;
				return;
			}
			else
			{
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
		m_animation_end = playAnimation(KNIGHT_ANIM_FALL);
		break;
	}
}

void Player::updateTimers(float dt)
{
	m_jump_timer->Update(dt);
	m_invincibility_timer->Update(dt);
}

void Player::updateMovement(float dt)
{
	// Normalize movement direction if it is not 0
	if (m_direction_x != 0.0f || m_direction_y != 0.0f)
	{
		m_direction_length = std::sqrt(m_direction_x * m_direction_x + m_direction_y * m_direction_y);
		m_direction_x = m_direction_x / m_direction_length;
		m_direction_y = m_direction_y / m_direction_length;
	}


	m_pos_x += m_velocity_x * m_direction_x * dt;
	m_pos_y += m_velocity_y * m_direction_y * dt;
	// updating velocity for x makes movement slippery
	m_velocity_y += m_acceleration_y * dt;
}

void Player::init() 
{
	m_movement_state = State::GROUND;
	m_previous_movement_state = State::GROUND;

	m_texture_size_width = 120;
	m_texture_size_height = 80;
	m_scale_x = 0.25f;
	m_scale_y = 0.25f;

	m_base_hp = 100.0f;
	m_base_dmg = 50.0f;
	
	m_hp = m_base_hp;
	m_dmg = m_base_dmg;

	m_orientation_x = 1.0f;
	m_orientation_y = 0.0f;
	m_direction_x = 0.0f;

	m_velocity_x = 5.0f;
	m_velocity_y = 5.0f;
	m_acceleration_y = 6.0f;
	m_velocity_y = m_acceleration_y;

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

	float canvas_width = GameObject::m_state->inst()->getCanvasWidth();
	float canvas_height = GameObject::m_state->inst()->getCanvasHeight();
	int window_width = GameObject::m_state->inst()->getWindowWidth();
	int window_height = GameObject::m_state->inst()->getWindowHeight();

	m_pos_x = canvas_width / 2.0f + m_translation_x;
	m_pos_y = canvas_height / 2.0f + m_translation_y;

	m_size_width = (float)m_texture_size_width / window_width *
		canvas_width * m_scale_x;
	m_size_height = (float)m_texture_size_height / window_height *
		canvas_height * m_scale_y;

	SETCOLOR(m_brush.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush.fill_opacity = 1.0f;
	m_brush.outline_opacity = 0.0f;
	m_brush.texture = m_full_textures_path;

	m_ground_collider = new Box(m_half_width, 8.0f, m_pos_x, m_pos_y);
	m_jump_timer = new Timer(1.0f);
	m_invincibility_timer = new Timer(0.5f);

	GameObject::init();
}

void Player::draw() 
{
	if (m_is_disabled) return;

	m_brush.texture = getCurrentFrame().m_path_to_frame;
	if (m_is_flickering)
	{
		m_brush.fill_opacity = std::cos(std::fmod(m_invincibility_timer->GetAccumulatedTime(), 1.0f));
	}

	graphics::setScale((float)m_orientation_x, 1.0f);

	graphics::drawRect(m_pos_x, m_pos_y,
		m_size_width, m_size_height,
		m_brush);

	graphics::resetPose();

	GameObject::draw();
}

Player::~Player() 
{
	delete m_ground_collider;
	delete m_jump_timer;
	delete m_invincibility_timer;
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

void Player::correctPos(Box & other)
{
	m_pos_x -= m_orientation_x * GameObject::m_state->inst()->m_correction_x;
	m_pos_y -= m_orientation_y * GameObject::m_state->inst()->m_correction_y;

	m_is_grounded = true;
}

void Player::resolveCollision(Box& other)
{
	switch (other.m_type)
	{
	case Type::STATIC:

		switch (other.m_sub_type)
		{
		case SubType::TILE:
			correctPos(other);
			break;
		case SubType::SPIKE:
			takeDmg(SPIKE_DMG);
			correctPos(other);
			break;
		}

		break;
	case Type::DYNAMIC:

		switch (other.m_sub_type)
		{
		case SubType::ENEMY:
			takeDmg(static_cast<Enemy&>(other).getDmg());
			break;
		case SubType::PLAYER:
			break;
		}

		break;
	}
}