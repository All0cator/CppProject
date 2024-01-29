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

Box::Box(float width, float height, float x_center, float y_center, float R, float G, float B)
{
	// Todo
	// First we need to clamp values to a valid range what this means is
	// Check if color values are < 0.0f if so make them 0.0f if they are > 255.0f make them 255.0f
	
	
	// Check if colors have values > 1.0f if so normalize them (Divide with 255.0f)

	// Call contructor without colors

	// Call setOutlineParameters with R, G, B values
}

Box::~Box()
{}

void Box::setOutlineParameters(float R, float G, float B, float opacity, float width)
{
	SETCOLOR(this->m_debug_box_brush.outline_color, R, G, B);
	this->m_debug_box_brush.outline_opacity = opacity;
	this->m_debug_box_brush.outline_width = width; 
}

