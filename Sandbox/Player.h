#pragma once

#include "GameObject.h"
#include "Actor.h"
#include "Box.h"

class Timer;
class Area;

class Player : public GameObject, public Actor, public Box
{

public:
	static enum State { DEAD, HIT, TURNING_ARROUND, GROUND, TRANSITION_CROUCH, CROUCH, AIR, TRANSITION_FALL, FALL };
private:

	State m_movement_state;
	State m_previous_movement_state;

	std::string m_full_textures_path;
	std::string m_full_sounds_path;
	int m_texture_size_width;
	int m_texture_size_height;
	float m_scale_x;
	float m_scale_y;

	Area* m_ground_collider;
	Timer* m_jump_timer;
	Timer* m_invincibility_timer;

	float m_base_hp;
	float m_base_dmg;

	float m_hp;
	float m_dmg;

	float m_direction_x;
	float m_direction_y;
	float m_direction_length;

	int m_orientation_x; // Controls flipping of sprite -1 is left 1 is right
	int m_orientation_y; // -1 is top 1 is bottom

	float m_size_width;
	float m_size_height;

	float m_pos_x;
	float m_pos_y;

	float m_velocity_y;
	float m_velocity_x;

	float m_acceleration_y;

	bool m_is_moving;
	bool m_is_jumping;
	bool m_is_grounded;
	bool m_is_crouched;
	bool m_transitioning_crouch;
	bool m_is_attacking;
	bool m_can_interact;
	bool m_is_disabled;
	bool m_animation_end;
	bool m_is_turning_arround;
	bool m_is_flickering;

	graphics::Brush m_brush;

public:
	Player(GameState* gs,
		   const std::string& sounds_path,
		   const std::string& textures_path,
		   const std::vector<std::string>& animation_names,
		   const std::vector<unsigned int>& frames_per_animation,
		   float animation_speed_FPS,
		   float width_pixels,
		   float height_pixels,
		   float left_pixels,
		   float top_pixels,
		   const std::string& name,
		   float R = 0.0f,
		   float G = 0.0f,
		   float B = 1.0f);
	virtual void update(float dt) override;
	void updateInput();
	void updateState();
	void updateAnimation();
	void updateTimers(float dt);
	void updateMovement(float dt);
	void takeDmg(float ammount);
	void correctPos(Box& other);
	void collidedWithGround(Box& other);
	virtual void init() override;
	virtual void draw() override;
	virtual ~Player();
	float getDmg();
	virtual void resolveCollision(Box& other) override;
protected:
	
};