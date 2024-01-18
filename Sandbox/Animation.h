#pragma once

#include "Frame.h"

class Animation
{
public:
	bool m_is_flipped;
	unsigned int m_num_frames;
	Frame* m_frames;

public:
	Animation();
	virtual ~Animation();
};