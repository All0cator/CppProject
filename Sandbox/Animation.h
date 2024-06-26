#pragma once

#include "Frame.h"

class Animation
{
public:
	unsigned int m_num_frames;
	Frame* m_frames;

public:
	Animation(unsigned int num_frames, const std::string& path_to_animation);
	virtual ~Animation();
};