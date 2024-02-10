#include "ParallaxBackground.h"
#include "GraphicsConstants.h"
#include "Camera.h"
#include <iostream>
#include "GameState.h"

ParallaxBackground::ParallaxBackground(GameState * gs,
									   const std::string& name,
									   const std::string& parallax_path,
									   float width_pixels, float height_pixels, 
									   float pos_x_pixels, float pos_y_pixels, 
									   float map_width_pixels, float map_height_pixels,
									   float horizontal_speed, float vertical_speed, 
									   bool mirror_x, bool mirror_y)
	: GameObject(gs, name)
{
	this->m_parallax_path = parallax_path + name + ".png";
	this->m_width_pixels = width_pixels;
	this->m_height_pixels = height_pixels;
	this->m_width_canvas = 512.0f;
	this->m_half_width_canvas = this->m_width_canvas / 2.0f;
	this->m_height_canvas = 512.0f;
	this->m_half_height_canvas = this->m_height_canvas / 2.0f;
	this->m_pos_x_pixels = pos_x_pixels;
	this->m_pos_y_pixels = pos_y_pixels;
	this->m_map_width_pixels = map_width_pixels;
	this->m_map_height_pixels = map_height_pixels;
	this->m_horizontal_speed = horizontal_speed;
	this->m_vertical_speed = vertical_speed;
	this->m_mirror_x = mirror_x;
	this->m_mirror_y = mirror_y;
}

ParallaxBackground::~ParallaxBackground()
{

}

void ParallaxBackground::update(float dt)
{


	GameObject::update(dt);
}

void ParallaxBackground::init()
{
	SETCOLOR(m_brush.fill_color, 1.0f, 1.0f, 1.0f);
	m_brush.fill_opacity = 1.0f;
	m_brush.outline_opacity = 0.0f;
	m_brush.texture = m_parallax_path;

	GameObject::init();
}

void ParallaxBackground::draw()
{	
	float x_pos_start = m_pos_x_pixels - Camera::inst()->getFocalPointX();
	float y_pos_start = m_pos_y_pixels - Camera::inst()->getFocalPointY();

	int window_width_pixels = m_state->getWindowWidth();
	int window_height_pixels = m_state->getWindowHeight();



	while (x_pos_start < m_pos_x_pixels * 2.0f)
	{
		graphics::drawRect(x_pos_start + m_width_pixels / 2.0f, y_pos_start + m_height_pixels / 2.0f, m_width_pixels, m_height_pixels, m_brush);
		x_pos_start += m_width_pixels;
	}

	graphics::drawRect(x_pos_start + m_width_pixels / 2.0f, y_pos_start + m_height_pixels / 2.0f, m_width_pixels, m_height_pixels, m_brush);


	GameObject::draw();
}
