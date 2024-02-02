#pragma once


#include <unordered_map>
class Animation;
class Timer;
class Frame;
#include <string>
#include <vector>

const std::string NULLString = "NULL";

class Actor
{
protected:
	std::vector<Animation *> m_animations;
	Animation* m_current_animation;
	std::string m_current_animation_name;
	unsigned int m_current_frame_index;
	Timer* m_frame_timer;
	float m_time_per_frame_seconds;

	// Maps a state to an index in the animations array eg. m_animation_name_to_index["idle"] = 0
	std::unordered_map<std::string, unsigned int> m_animation_name_to_index;
private:
	void resetAnimationConstants(const std::string & animation_name);
public:
	Actor(const std::vector<std::string>& animation_names,
		  const std::vector<std::string>& animation_directories,
		  const std::vector<unsigned int>& frames_per_animation,
		  float animation_speed_FPS);
	virtual ~Actor();
	bool playAnimation(const std::string& animation_name);
	// Accumulates time into timer, Advances frame index by 1 
	void updateAnimationTimer(float dt);
	void updateCurrentFrameIndex();
	const std::string& getCurrentAnimationName();
	unsigned int getCurrentFrameIndex();
	bool animationFinished();
	const std::string& getCurrentFrame();
};