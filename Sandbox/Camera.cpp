#include "Camera.h"

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

void Camera::setZoom(float zoom)
{
	this->m_zoom = zoom;
}

void Camera::setFocalPointX(float focal_point_x)
{
	this->m_focal_point_x = focal_point_x;
}

void Camera::setFocalPointY(float focal_point_y)
{
	this->m_focal_point_y = focal_point_y;
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

float Camera::getZoom()
{
	return m_zoom;
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
