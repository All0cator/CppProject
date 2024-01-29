#include "Camera.h"

Camera* Camera::inst()
{
	if (m_instance != nullptr)
	{
		return m_instance;
	}
	
	m_instance = new Camera();

	return m_instance;
}

Camera::~Camera()
{
}

Camera::Camera()
{
}
