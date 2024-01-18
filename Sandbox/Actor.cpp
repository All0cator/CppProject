#include "Actor.h"

Actor::Actor(unsigned int num_animations,
			 const std::string* animations,
			 unsigned int * frames_per_animation,
			 float animation_speed_FPS)
{
	this->m_animations = new Animation*[num_animations];

	for (unsigned int i = 0; i < num_animations; i++)
	{
		this->m_animations[i] = new Animation();

		this->m_animation_states[animations[i]] = i;
	}
}

Actor::~Actor()
{
	delete [] this->m_animations;
}