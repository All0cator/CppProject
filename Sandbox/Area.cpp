#include "Area.h"
#include "GameObject.h"

Area::Area(float width_pixels, float height_pixels, 
		   float left_pixels, float top_pixels, 
		   std::function<void(Area&)> signal_callback, 
		   AreaType type,
		   OriginType origin,
		   GameObject* origin_ptr)
	: Box(width_pixels, height_pixels, left_pixels, top_pixels)
{
	m_signal_callback = signal_callback;
	m_type = type;
	m_origin = origin;
	m_origin_ptr = origin_ptr;
	m_x_axis = (left_pixels + (left_pixels + width_pixels)) / 2.0f;
	m_is_active = true;
}

void Area::flipX()
{
	if (getLeft() > m_x_axis)
	{
		setLeft(getLeft() - (getLeft() - m_x_axis) - m_width_pixels);
	}
	else
	{
		setLeft(getLeft() + (m_x_axis - getLeft()) + m_width_pixels);
	}
}

void Area::updatePositions(float new_left, float new_top, float new_x_axis)
{
	setLeft(new_left);
	setTop(new_top);
	m_x_axis = new_x_axis;
}

Area::~Area()
{}

void Area::resolveCollision(Area& other)
{
	if (m_signal_callback)
	{
		m_signal_callback(other);
	}
}
