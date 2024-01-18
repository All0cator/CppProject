#pragma once

#include "Animation.h"
#include <unordered_map>
class Timer;

class Actor
{
protected:
	Animation ** m_animations;
	unsigned int m_current_frame_index;
	Timer* m_fps;

	// Maps a state to an index in the animations array eg. m_animation_states["idle"] = 0
	std::unordered_map<std::string, unsigned int> m_animation_states;
public:
	Actor(unsigned int num_animations, 
		  const std::string * animations,
		  float animation_speed_FPS);
	virtual ~Actor();
	void FlipAnimation();
	void SetupAnimationStates(const std::string* states);
	// Accumulates time into timer, Advances frame index by 1 
	void UpdateAnimation();
	unsigned int GetCurrentFrameIndex();
};