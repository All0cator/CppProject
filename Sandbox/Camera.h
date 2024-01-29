#pragma once
/* Singleton class */
class Camera
{
private:
	static Camera * m_instance;

	// Offsets the objects drawn
	float m_focal_point_x;
	float m_focal_point_y;

	// Scales the objects
	float m_zoom;

	float m_min_x;
	float m_max_x;
	float m_min_y;
	float m_max_y;
public:
	static Camera * inst();

	void setBounds(float min_x, float max_x, float min_y, float max_y);
	void setZoom(float zoom);
	float getFocalPointX();
	float getFocalPointY();
	float getZoom();
	~Camera();
private:
	Camera();
};