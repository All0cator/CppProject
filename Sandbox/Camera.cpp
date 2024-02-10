#include "Camera.h"
#include "GraphicsConstants.h"

Camera* Camera::m_instance = nullptr;

Camera* Camera::inst()
{
	if (Camera::m_instance == nullptr)
	{
		Camera::m_instance = new Camera();
	}

	return Camera::m_instance;
}

void Camera::setBounds(float min_x, float max_x, float min_y, float max_y)
{
	this->m_min_x = min_x;
	this->m_max_x = max_x;
	this->m_min_y = min_y;
	this->m_max_y = max_y;
}

void Camera::setFocalPointX(float focal_point_x)
{
	this->m_focal_point_x = focal_point_x - WINDOW_WIDTH / 2.0f;
	
	if (this->m_focal_point_x > m_max_x)
	{
		this->m_focal_point_x = m_max_x;
	}

	if (this->m_focal_point_x < m_min_x)
	{
		this->m_focal_point_x = m_min_x;
	}
}

void Camera::setFocalPointY(float focal_point_y)
{
	this->m_focal_point_y = focal_point_y - WINDOW_HEIGHT / 2.0f;
	if (this->m_focal_point_y > m_max_y)
	{
		this->m_focal_point_y = m_max_y;
	}

	if (this->m_focal_point_y < m_min_y)
	{
		this->m_focal_point_y = m_min_y;
	}
}

Camera::~Camera()
{
}

Camera::Camera()
{
	m_focal_point_x = 0.0f;
	m_focal_point_y = 0.0f;
}

float Camera::getFocalPointX()
{
	return m_focal_point_x;
}

float Camera::getFocalPointY()
{
	return m_focal_point_y;
}

float Camera::getMinX()
{
	return m_min_x;
}

float Camera::getMaxX()
{
	return m_max_x;
}

float Camera::getMinY()
{
	return m_min_y;
}

float Camera::getMaxY()
{
	return m_max_y;
}
