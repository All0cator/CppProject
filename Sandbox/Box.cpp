#include "Box.h"
#include "Constants.h"
#include <iostream>

Box::Box(float width_pixels, float height_pixels, float x_center_pixels, float y_center_pixels)
{
	if (width_pixels <= 0.0f || height_pixels <= 0.0f)
	{
		std::cout << "Error: Negative width and height gived to Box: (W) : " << width_pixels << " (H) : " << height_pixels << std::endl;
	}

	// Converts pixels to canvas units boolean parameter means clamp value to window's edges
	float width_canvas_units = graphics::windowToCanvasX(width_pixels, false);
	float height_canvas_units = graphics::windowToCanvasY(height_pixels, false);

	float x_center_canvas_units = graphics::windowToCanvasX(x_center_pixels, false);
	float y_center_canvas_units = graphics::windowToCanvasY(y_center_pixels, false);

	this->m_half_width = width_canvas_units / 2.0f;
	this->m_half_height = height_canvas_units / 2.0f;

	this->m_x_center = x_center_canvas_units;
	this->m_y_center = y_center_canvas_units;

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

