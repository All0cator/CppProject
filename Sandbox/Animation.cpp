#include "Animation.h"

Animation::Animation(unsigned int num_frames)
{
	this->m_num_frames = num_frames;
	this->m_is_flipped = false;

	this->m_frames = new Frame[this->m_num_frames];
	for (unsigned int i = 0; this->m_num_frames; i++)
	{
		this->m_frames[i].m_frame_name = 
	}
}

Animation::~Animation()
{

}