#pragma once

#include "Box.h"

class GameObject;

class Area : public Box
{
public:

	enum AreaType { TILE, SPIKE, HURTBOX, HITBOX, COLLIDER, TYPE_MAX };
	enum OriginType { LEVEL, PLAYER, ENEMY };

	AreaType m_type; // Which type this area
	OriginType m_origin; // Where is this area located
	GameObject* m_origin_ptr;

	float m_x_axis;
	std::function<void(Area&)> m_signal_callback;
	bool m_is_active;

public:
	Area(float width_pixels, float height_pixels, 
		 float left_pixels, float top_pixels, 
		 std::function<void(Area&)> signal_callback, 
		 AreaType type,
		 OriginType m_origin,
		 GameObject * m_origin_ptr);

	void flipX();
	void updatePositions(float new_left, float new_top, float new_x_axis);
	virtual ~Area();
	void resolveCollision(Area& other);
};
