#pragma once
#include "Core.h"
#include "cmathutils.h"

extern const unsigned int e_SCREEN_WIDTH;
extern const unsigned int e_SCREEN_HEIGHT;

struct CameraData
{
	mat4 m_view;
	mat4 m_projection;
};

class Camera : public Core
{
private:
	CameraData m_data;
	Camera() {}
protected:
	bool init()
	{
		m_data.m_view = mat4MakeIdentity();
		m_data.m_projection
			= getOrtho(0, e_SCREEN_WIDTH, 0, e_SCREEN_HEIGHT, 0, 100);
		return true;
	}
public:
	static Camera getInstance() { static Camera c; return c; }
	CameraData getCameraData() const { return m_data; }
	void setCameraData(const CameraData &a_data) { m_data = a_data; }
};