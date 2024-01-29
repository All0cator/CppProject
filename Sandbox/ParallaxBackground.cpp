#include "ParallaxBackground.h"
#include "GraphicsConstants.h"

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


	GameObject::draw();
}
