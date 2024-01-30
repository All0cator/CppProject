#include "Box.h"
#include "GraphicsConstants.h"
#include <iostream>
#include "GameObject.h"

Box::Box(float width_pixels, float height_pixels, float left_pixels, float top_pixels, Type type, SubType sub_type)
{
	if (width_pixels <= 0.0f || height_pixels <= 0.0f)
	{
		std::cout << "Error: Negative width and height gived to Box: (W) : " << width_pixels << " (H) : " << height_pixels << std::endl;
	}

	this->m_type = type;
	this->m_sub_type = sub_type;

	this->m_width_pixels = width_pixels;
	this->m_height_pixels = height_pixels;

	this->m_top = left_pixels;
	this->m_left= top_pixels;
	this->m_right = left_pixels + width_pixels;
	this->m_bottom = top_pixels + height_pixels;

	setOutlineParameters(1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
}

Box::Box(float width_pixels, float height_pixels, float left_pixels, float top_pixels, Type type, SubType sub_type, float R, float G, float B)
	: Box(width_pixels, height_pixels, left_pixels, top_pixels, type, sub_type)
{
	// Todo
	// First we need to clamp values to a valid range what this means is
	// Check if color values are < 0.0f if so make them 0.0f if they are > 255.0f make them 255.0f
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

	// Call setOutlineParameters with R, G, B values

	setOutlineParameters(R, G, B, 1.0f, 1.0f);
}

Box::~Box()
{}

void Box::setOutlineParameters(float R, float G, float B, float opacity, float width)
{
	SETCOLOR(this->m_debug_box_brush.outline_color, R, G, B);
	this->m_debug_box_brush.outline_opacity = opacity;
	this->m_debug_box_brush.outline_width = width; 
}

