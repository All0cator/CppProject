#include "Player.h"
#include "GameState.h"

Player::Player(GameState* gs, 
			   const std::string& sounds_path,
			   const std::string& textures_path,
			   const std::string& name) : GameObject(gs, name)
{
	m_full_textures_path = m_state->inst()->getTexturesPath() + textures_path;
	m_full_sounds_path = m_state->inst()->getSoundsPath() + sounds_path;
}

void Player::update(float dt) 
{
	// Left movement of player
	if (graphics::getKeyState(graphics::SCANCODE_A))
	{
		m_translation_x = -m_velocity * dt;
		m_pos_x += m_translation_x;
	}

	// Right movement of player
	if (graphics::getKeyState(graphics::SCANCODE_D))
	{
		m_translation_x = m_velocity * dt;
		m_pos_x += m_translation_x;
	}

	// Up movement of player
	if (graphics::getKeyState(graphics::SCANCODE_W))
	{
		m_translation_y = -m_velocity * dt;
		m_pos_y += m_translation_y;
	}

	// Down movement of player
	if (graphics::getKeyState(graphics::SCANCODE_S))
	{
		m_translation_y = m_velocity * dt;
		m_pos_y += m_translation_y;
	}

}

void Player::init() 
{
	m_texture_size_width = 512;
	m_texture_size_height = 512;
	m_scale_x = 0.25f;
	m_scale_y = 0.25f;


	m_translation_x = 0.0f;
	m_translation_y = 0.0f;

	float canvas_width = m_state->inst()->getCanvasWidth();
	float canvas_height = m_state->inst()->getCanvasHeight();
	int window_width = m_state->inst()->getWindowWidth();
	int window_height = m_state->inst()->getWindowHeight();

	m_pos_x = canvas_width / 2.0f + m_translation_x;
	m_pos_y = canvas_height / 2.0f + m_translation_y;

	m_size_width = (float)m_texture_size_width / window_width *
		canvas_width * m_scale_x;
	m_size_height = (float)m_texture_size_height / window_height *
		canvas_height * m_scale_y;

	m_velocity = 3.0f;

	SETCOLOR(m_brush.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush.fill_opacity = 1.0f;
	m_brush.outline_opacity = 0.0f;
	m_brush.texture = m_full_textures_path;
}

void Player::draw() 
{
	graphics::drawRect(m_pos_x, m_pos_y,
		m_size_width, m_size_height,
		m_brush);
}

Player::~Player() 
{
}