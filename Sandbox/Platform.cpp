#include "GameState.h"
#include "Platform.h"

Platform::Platform(GameState* gs,
				   const std::string& sounds_path,
				   const std::string& textures_path,
				   const std::string& name) : GameObject(gs, name)
{
	m_full_textures_path = gs->inst()->getTexturesPath() + textures_path;
	m_full_sounds_path = gs->inst()->getSoundsPath() + sounds_path;
}

void Platform::update(float dt)
{

}

void Platform::init()
{
	m_texture_size_width = 32;
	m_texture_size_height = 32;
	m_scale_x = 3.0f;
	m_scale_y = 3.0f;

	m_translation_x = 0.0f;
	m_translation_y = 1.3f; // So that platform appears bellow player

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

	m_velocity = 0.0f;

	SETCOLOR(m_brush.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush.fill_opacity = 1.0f;
	m_brush.outline_opacity = 0.0f;
	m_brush.texture = m_full_textures_path;
}

void Platform::draw()
{
	graphics::drawRect(m_pos_x, m_pos_y,
		m_size_width, m_size_height,
		m_brush);
}

Platform::~Platform()
{

}