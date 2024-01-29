#pragma once


#include <unordered_map>
class Animation;
class Timer;
class Frame;
#include <string>

class Actor
{
protected:
	Animation ** m_animations;
	unsigned int m_current_frame_index;
	Timer* m_fps;

	// Maps a state to an index in the animations array eg. m_animation_states["idle"] = 0
	std::unordered_map<std::string, unsigned int> m_animation_states;
public:
	Actor(const std::vector<std::string>& animation_names,
		  const std::vector<unsigned int>& frames_per_animation,
		  float animation_speed_FPS);
	virtual ~Actor();
	void flipAnimation();
	bool playAnimation(const std::string& animation_name);
	void setupAnimationStates(const std::string* states);
	// Accumulates time into timer, Advances frame index by 1 
	void updateAnimation();
	unsigned int getCurrentFrameIndex();
	const Frame& getCurrentFrame();
};