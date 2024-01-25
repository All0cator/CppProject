#pragma once

// Box class contains the
#include "sgg/graphics.h"

class Box
{
protected:
	// Box's data is in canvas Units

	float m_half_width;
	float m_half_height;

	// Coordinates
	float m_x_center;
	float m_y_center;

	// Debug members
	graphics::Brush m_debug_box_brush;

public:
	// The reason we input pixels is because we want pixel level control of collision
	// For example we want the knight to be 21x36 pixels canvas units does not make our life easy here
	// So we have to input the boxe's data in pixels

	Box(float width_pixels, float height_pixels, float x_center_pixels, float y_center_pixels);
	
	// outline_color contains 3 float in range [0.0f, 1.0f] or [0.0f, 255.0f] in the format R, G, B
	// in case we want to set outline color
	Box(float width_pixels, float height_pixels, float x_center_pixels, float y_center_pixels, float R, float G, float B);
	virtual ~Box();

	void setOutlineParameters(float R = 1.0f, float G = 0.0f, float B = 0.0f, float opacity = 1.0f, float width = 1.0f);
};