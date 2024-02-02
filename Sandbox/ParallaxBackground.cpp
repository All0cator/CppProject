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
									   float horizontal_speed, float vertical_speed, 
									   bool mirror_x, bool mirror_y)
	: GameObject(gs, name)
{
	this->m_parallax_path = parallax_path + name + ".png";
	this->m_width_pixels = width_pixels;
	this->m_height_pixels = height_pixels;
	this->m_width_canvas = 512.0f; //graphics::windowToCanvasX(m_width_pixels, false);
	this->m_half_width_canvas = this->m_width_canvas / 2.0f;
	this->m_height_canvas = 320.0f;//graphics::windowToCanvasY(m_height_pixels, false);
	this->m_half_height_canvas = this->m_height_canvas / 2.0f;
	this->m_pos_x_pixels = pos_x_pixels;
	this->m_pos_y_pixels = pos_y_pixels;
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
	m_brush.texture = m_parallax_path;

	GameObject::init();
}

void ParallaxBackground::draw()
{	
	float x_pos_start = Camera::inst()->getFocalPointX() - m_pos_x_pixels;
	float y_pos_start = Camera::inst()->getFocalPointY() - m_pos_y_pixels;

	int window_width_pixels = m_state->getWindowWidth();
	int window_height_pixels = m_state->getWindowHeight();

	float x_pos_pixels = (x_pos_start - (std::fmod(x_pos_start, m_width_pixels))) * m_horizontal_speed;
	float y_pos_pixels = (y_pos_start - (std::fmod(y_pos_start, m_height_pixels))) * m_vertical_speed;
	
	float x_pos_canvas = graphics::windowToCanvasX(x_pos_pixels, false);
	float y_pos_canvas = graphics::windowToCanvasY(y_pos_pixels, false);

	// Do the texture mirroring
	if (m_mirror_x || m_mirror_y)
	{
		while (y_pos_pixels < window_height_pixels)
		{
			while (x_pos_pixels < window_width_pixels)
			{

				if (m_mirror_x)
				{
					graphics::drawRect(x_pos_canvas + m_half_width_canvas, y_pos_canvas + m_half_height_canvas, m_width_canvas, m_height_canvas, m_brush);
					x_pos_pixels += (m_width_pixels) * m_horizontal_speed;
					x_pos_canvas = graphics::windowToCanvasX(x_pos_pixels, false);
				}
				else
				{
					break;
				}
			}

			x_pos_pixels = x_pos_start * m_horizontal_speed;
			x_pos_canvas = graphics::windowToCanvasX(x_pos_pixels, false);

			if (m_mirror_y)
			{

				graphics::drawRect(x_pos_canvas + m_half_width_canvas, y_pos_canvas + m_half_height_canvas, m_width_canvas, m_height_canvas, m_brush);
				y_pos_pixels += m_height_pixels * m_vertical_speed;
				y_pos_canvas = graphics::windowToCanvasY(y_pos_pixels, false);
			}
			else
			{
				//graphics::drawRect(x_pos_canvas + m_half_width_canvas, y_pos_canvas + m_half_height_canvas, m_width_canvas, m_height_canvas, m_brush);
				break;
			}
		}
	}
	else
	{
		// Draw the background normally as with any texture
		graphics::drawRect(x_pos_canvas + m_half_width_canvas, y_pos_canvas + m_half_height_canvas, m_width_canvas, m_height_canvas, m_brush);
	}

	GameObject::draw();
}
