#include "Area.h"

Area::Area(float width_pixels, float height_pixels, 
		   float left_pixels, float top_pixels, 
		   std::function<void(Box&)> signal_callback, 
		   SubType sub_type)
	: Box(width_pixels, height_pixels, left_pixels, top_pixels, Type::AREA, sub_type)
{

}

void Area::flipX()
{
	m_left = m_left - m_x_axis - m_width_pixels;
}

void Area::updatePositions(float new_left, float new_top, float new_x_axis)
{
	m_left = new_left;
	m_top = new_top;
	m_bottom = new_top + m_height_pixels;
	m_right = new_left + m_width_pixels;
	m_x_axis = new_x_axis;
}



Area::~Area()
{}

void Area::resolveCollision(Box& other)
{
	if (m_signal_callback)
	{
		m_signal_callback(other);
	}
}
