#include "Animation.h"

Animation::Animation(unsigned int num_frames, const std::string& path_to_animation)
{
	this->m_num_frames = num_frames;
	this->m_frames = new Frame[this->m_num_frames];

	for (int i = 0; i < this->m_num_frames; i++)
	{
		this->m_frames[i].m_path_to_frame = path_to_animation + std::to_string(i) + ".png";
	}
}

Animation::~Animation()
{
	delete m_frames;
}