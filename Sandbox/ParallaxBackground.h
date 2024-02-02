#pragma once

#include "GameObject.h"

class ParallaxBackground : public GameObject
{
private:

	float m_width_pixels;
	float m_height_pixels;

	float m_width_canvas;
	float m_half_width_canvas;
	float m_height_canvas;
	float m_half_height_canvas;

	float m_pos_x_pixels;
	float m_pos_y_pixels;
	
	float m_horizontal_speed;
	float m_vertical_speed;

	bool m_mirror_x;
	bool m_mirror_y;

	graphics::Brush m_brush;

	std::string m_parallax_path;
public:
	ParallaxBackground(GameState * gs,
					   const std::string& name,
					   const std::string& parallax_path,
					   float width_pixels, float height_pixels, 
					   float pos_x_pixels, float pos_y_pixels,
					   float horizontal_speed, float vertical_speed = 1.0f,
					   bool mirror_x = true, bool mirror_y = false);
	virtual ~ParallaxBackground();
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
};