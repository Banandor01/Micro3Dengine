#pragma once

#include "SDL.h"
#include "../../Micro3Dengine/Micro3Dengine/Camera.h"

template<class numT>
class Camera;

template<class numT>
class Application
{
public:
	Application();

	bool HandleEvents(Camera<numT> & camera);

	bool Run() { return run; }
	numT Yaw()  { return yaw; }
	numT Roll() { return roll; }
	numT Pitch() { return pitch; }
	numT Rot() { return t; }			// only for tsting
		
private:
	numT xStep, zStep;
	numT yawStep, rollStep, pitchStep;
	numT yaw, roll, pitch;
	numT ts, t; // just for test
	numT speed;

	bool run;
};