#include "Actor.h"
#include "Animation.h"
#include "Timer.h"

#include <iostream>

Actor::Actor(const std::vector<std::string>& animation_names,
			 const std::vector<std::string>& animation_directories,
			 const std::vector<unsigned int>& frames_per_animation,
			 float animation_speed_FPS)
{
	this->m_animations = std::vector<Animation*>(animation_names.size());

	for (int i = 0; i < animation_names.size() && i < frames_per_animation.size(); i++)
	{
		this->m_animations[i] = new Animation(frames_per_animation[i], animation_directories[i]);
		this->m_animation_name_to_index[animation_names[i]] = i;
	}

	this->m_time_per_frame_seconds = 1.0f / animation_speed_FPS;
	this->m_frame_timer = new Timer(this->m_time_per_frame_seconds, true, std::bind(&Actor::updateCurrentFrameIndex, this), Timer::TimeUnit::SECONDS);
	this->m_current_frame_index = 0;

	resetAnimationConstants("NULL");
}

Actor::~Actor()
{
	for (int i = 0; i < this->m_animations.size(); i++)
	{
		delete this->m_animations[i];
	}
	delete this->m_frame_timer;
}

void Actor::resetAnimationConstants(const std::string& animation_name)
{
	this->m_current_frame_index = 0;
	this->m_frame_timer->Reset(0.0f, true);
	this->m_current_animation_name = animation_name;
	if (m_animation_name_to_index.find(animation_name) != m_animation_name_to_index.end())
	{
		this->m_current_animation = m_animations[m_animation_name_to_index[animation_name]];
	}
}

bool Actor::playAnimation(const std::string& animation_name)
{
	if (animation_name != m_current_animation_name)
	{
		resetAnimationConstants(animation_name);
	}

	if (m_current_frame_index >= m_current_animation->m_num_frames)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Actor::updateAnimationTimer(float dt)
{
	m_frame_timer->Update(dt, Timer::TimeUnit::SECONDS);

}

void Actor::updateCurrentFrameIndex()
{
	this->m_current_frame_index++;

	if (m_current_animation)
	{
		if (this->m_current_frame_index >= m_current_animation->m_num_frames)
		{
			this->m_current_frame_index = 0;
		}
	}
}

const std::string& Actor::getCurrentAnimationName()
{
	return this->m_current_animation_name;
}

unsigned int Actor::getCurrentFrameIndex()
{
	return m_current_frame_index;
}

bool Actor::animationFinished()
{
	if (!m_current_animation) return true;

	return m_current_frame_index >= m_current_animation->m_num_frames;
}

const std::string& Actor::getCurrentFrame()
{
	if (!m_current_animation) return NULLString;
	return m_current_animation->m_frames[m_current_frame_index].m_path_to_frame;
}
