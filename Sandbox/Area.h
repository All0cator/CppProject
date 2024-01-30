#pragma once

#include "Box.h"

class Area : public Box
{
public:
	float m_x_axis;
	std::function<void(Box&)> m_signal_callback;

public:
	Area(float width_pixels, float height_pixels, 
		 float left_pixels, float top_pixels, 
		 std::function<void(Box&)> signal_callback, 
		 SubType sub_type);

	void flipX();
	void updatePositions(float new_left, float new_top, float new_x_axis);
	virtual ~Area();
	virtual void resolveCollision(Box& other) override;
};
