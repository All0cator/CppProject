#pragma once

#include "GameObject.h"
#include "Actor.h"
#include "Box.h"

class Timer;
class Area;

class Enemy : public GameObject, public Actor, public Box
{
public:
	enum State { DEAD, IDLE, WALK, HIT, ATTACK };

private:

	State m_movement_state;

	std::string m_textures_path;
	std::string m_sounds_path;

	float m_texture_width;
	float m_texture_half_width;
	float m_texture_height;
	float m_texture_half_height;

	float m_scale_x;
	float m_scale_y;
	
	bool m_x_axis_correction;

public:
	Area* m_side_collider;
	Area* m_hurt_box;
	Area* m_hit_box;
	Area* m_notice_area;
private:
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
	float m_max_velocity_y;

	float m_acceleration_y;

	bool m_is_moving;
	bool m_is_attacking;
	bool m_animation_end;
	bool m_can_interact;
	bool m_is_disabled;
	bool m_is_flickering;

	graphics::Brush m_brush;

	float m_new_x_axis;

public:
	Enemy(GameState* gs,
		const std::string& sounds_path,
		const std::string& textures_path,
		const std::vector<std::string>& animation_names,
		const std::vector<std::string>& animation_directories,
		const std::vector<unsigned int>& frames_per_animation,
		float animation_speed_FPS,
		float width_pixels,
		float height_pixels,
		float left_pixels,
		float top_pixels,
		const std::string& name,
		float R = 1.0f,
		float G = 0.0f,
		float B = 0.0f);

	void side_collider_callback(Area& other);
	void hurt_box_callback(Area& other);
	void hit_box_callback(Area& other);
	void noticeAreaCallback(Area& other);

	virtual void update(float dt) override;
	void updateInput();
	void updateState();
	void updateAnimation();
	void updateTimers(float dt);
	void updateMovement(float dt);
	void updateAreaDimensions();
	void checkCollisions();
	void flipAreasX();
	void takeDmg(float ammount);
	void correctPos(Area& other);
	virtual void init() override;
	virtual void draw() override;
	virtual ~Enemy();
	float getDmg();
};