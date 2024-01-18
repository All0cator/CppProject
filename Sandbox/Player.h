#pragma once

#include "GameObject.h"
#include "Actor.h"

class Player : public GameObject, public Actor
{
private:

	std::string m_full_textures_path;
	std::string m_full_sounds_path;
	int m_texture_size_width;
	int m_texture_size_height;
	float m_scale_x;
	float m_scale_y;


	// Offset from starting position in Canvas Units

	// Translation is defined from upper left corner of window
	// which means positive x : right
	//			   negative x : left
	//			   positive y : down
	//			   negative y : up

	float m_translation_x;
	float m_translation_y;

	// Rotation could also be specified here

	float m_pos_x;
	float m_pos_y;

	float m_size_width;
	float m_size_height;

	float m_velocity = 0.001f;

	// Acceleration could also be specified here

	graphics::Brush m_brush;

public:
	Player(GameState* gs, 
		   const std::string& sounds_path,
		   const std::string& textures_path,
		   const std::string& name = "");
	virtual void update(float dt) override;
	virtual void init() override;
	virtual void draw() override;
	virtual ~Player();
protected:
	
};