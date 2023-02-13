#pragma once

#include "SDL.h"
#include "../../Micro3Dengine/Micro3Dengine/Camera.h"

template<class numT>
class Camera;

template<class numT>
class Application
{
public:
	Application() :
		run(true), x(0), y(0), z(0),
		xStep(0), yStep(0), zStep(0),
		roll(0),yaw(0), pitch(0),
		rollStep(0), yawStep(0),
		speed (0)
	{}	

	bool HandleEvents(Camera<numT> & camera);
	
	bool Run() { return run; }

	float X() { return x; }
	float Y() { return y; }
	float Z() { return z; }

	float Yaw()  { return yaw; }
	float Roll() { return roll; }
	float Pitch() { return pitch; }
private:
	float xStep, yStep, zStep;
	float yawStep, rollStep;

	float x, y, z;
	float yaw, roll, pitch;
	
	float speed;
	bool run;
};