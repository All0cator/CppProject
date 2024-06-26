#include "Box.h"
#include "GraphicsConstants.h"
#include <iostream>
#include "GameObject.h"

Box::Box(float width_pixels, float height_pixels, float left_pixels, float top_pixels)
{
	if (width_pixels <= 0.0f || height_pixels <= 0.0f)
	{
		std::cout << "Error: Negative width and height gived to Box: (W) : " << width_pixels << " (H) : " << height_pixels << std::endl;
	}

	this->m_width_pixels = width_pixels;
	this->m_half_width_pixels = width_pixels / 2.0f;
	this->m_height_pixels = height_pixels;
	this->m_half_height_pixels = height_pixels / 2.0f;

	this->m_previous_top = top_pixels;
	this->m_previous_left = left_pixels;
	this->m_top = top_pixels;
	this->m_left= left_pixels;
	this->m_right = left_pixels + width_pixels;
	this->m_bottom = top_pixels + height_pixels;

	setOutlineParameters(1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
}

Box::Box(float width_pixels, float height_pixels, float left_pixels, float top_pixels, float R, float G, float B)
	: Box(width_pixels, height_pixels, left_pixels, top_pixels)
{
	if (R < 0.0f)
	{
		R = 0.0f;
	}
	else if (R > 255.0f)
	{
		R = 255.0f;
	}

	if (G < 0.0f)
	{
		G = 0.0f;
	}
	else if (G > 255.0f)
	{
		G = 255.0f;
	}

	if (B < 0.0f)
	{
		B = 0.0f;
	}
	else if (B > 255.0f)
	{
		B = 255.0f;
	}

	// Check if colors have values > 1.0f if so normalize them (Divide with 255.0f)

	if (R > 1.0f)
	{
		R = R / 255.0f;
	}

	if (G > 1.0f)
	{
		G = G / 255.0f;
	}

	if (B > 1.0f)
	{
		B = B / 255.0f;
	}
	setOutlineParameters(R, G, B, 1.0f, 1.0f);
}

Box::~Box()
{}

void Box::setLeftTop(float new_left, float new_top)
{
	setLeft(new_left);
	setTop(new_top);
}

void Box::setLeft(float new_left)
{
	m_previous_left = m_left;
	m_left = new_left;
	m_right = m_left + m_width_pixels;
}

void Box::setTop(float new_top)
{
	m_previous_top = m_top;
	m_top = new_top;
	m_bottom = m_top + m_height_pixels;
}

void Box::setBottom(float new_bottom)
{
	setTop(new_bottom - m_height_pixels);
}

void Box::setRight(float new_right)
{
	setLeft(new_right - m_width_pixels);
}

float Box::getPreviousTop()
{
	return m_previous_top;
}

float Box::getPreviousLeft()
{
	return m_previous_left;
}

float Box::getLeft()
{
	return m_left;
}

float Box::getTop()
{
	return m_top;
}

float Box::getBottom()
{
	return m_bottom;
}
float Box::getRight()
{
	return m_right;
}

void Box::setOutlineParameters(float R, float G, float B, float opacity, float width)
{
	SETCOLOR(this->m_debug_box_brush.outline_color, R, G, B);
	this->m_debug_box_brush.fill_opacity = 0.0f;
	this->m_debug_box_brush.outline_opacity = opacity;
	this->m_debug_box_brush.outline_width = width;
}

