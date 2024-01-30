#pragma once

// Box class contains the
#include "sgg/graphics.h"

class Box
{	
public:
	static enum Type { STATIC, DYNAMIC, AREA };
	static enum SubType { TILE, SPIKE, PLAYER, ENEMY, RECTANGLE /*, HITBOX*/ };
	
	Type m_type;
	SubType m_sub_type;

	float m_width_pixels;
	float m_height_pixels;

	float m_top;
	float m_left;
	float m_right;
	float m_bottom;

	// Debug members
	graphics::Brush m_debug_box_brush;

public:
	// The reason we input pixels is because we want pixel level control of collision
	// For example we want the knight to be 21x36 pixels canvas units does not make our life easy here
	// So we have to input the box's data in pixels

	Box(float width_pixels, float height_pixels, float left_pixels, float top_pixels, 
		Type type, SubType sub_type);
	
	// outline_color contains 3 float in range [0.0f, 1.0f] or [0.0f, 255.0f] in the format R, G, B
	// in case we want to set outline color
	Box(float width_pixels, float height_pixels, float left_pixels, float top_pixels, 
		Type type, SubType sub_type, 
		float R, float G, float B);
	virtual ~Box();

	void setOutlineParameters(float R = 1.0f, float G = 0.0f, float B = 0.0f, float opacity = 1.0f, float width = 1.0f);

	virtual void resolveCollision(Box& other) = 0;
};