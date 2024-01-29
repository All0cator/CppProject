#include "Actor.h"

Actor::Actor(const std::vector<std::string>& animation_names,
			 const std::vector<unsigned int>& frames_per_animation,
			 float animation_speed_FPS)
{
	this->m_animations = new Animation*[animation_names.size()];

	for (unsigned int i = 0; i < animation_names.size(); i++)
	{
		this->m_animations[i] = new Animation();

		this->m_animation_states[animation_names[i]] = i;
	}
}

Actor::~Actor()
{
	delete [] this->m_animations;
	delete this->m_fps;
}

void Actor::flipAnimation()
{
}

bool Actor::playAnimation(const std::string& animation_name)
{
}

void Actor::setupAnimationStates(const std::string* states)
{
}

void Actor::updateAnimation()
{

}

unsigned int Actor::getCurrentFrameIndex()
{
	return m_current_frame_index;
}
