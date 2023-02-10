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
		roll(0),yaw(0),
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

private:
	float xStep, yStep, zStep;
	float yawStep, rollStep;

	float x, y, z;
	float yaw, roll;
	
	float speed;
	bool run;
};


template<class numT>
bool Application<numT>::HandleEvents(Camera<numT>& camera) {
	SDL_Event event;
	SDL_PollEvent(&event);

	float posy = 0;

	switch (event.type) {

	case SDL_QUIT:
		run = false;
		break;
	case SDL_KEYUP:
		xStep = zStep = yStep = 0;
		yawStep = 0;
		rollStep = 0;
		break;
	case SDL_KEYDOWN:

		switch (event.key.keysym.sym) {
		case SDLK_1:
			break;
		case SDLK_2:
			break;
		
		//
		case SDLK_UP:	 zStep = +0.01f;
			break;
		case SDLK_DOWN:  zStep = -0.01f;
			break;
		case SDLK_LEFT:  rollStep = -0.3f;
			break;
		case SDLK_RIGHT: rollStep = 0.3f;
			break;
		
		//		
		case SDLK_a:
			yawStep = 0.4f;
			break;
		case SDLK_d:
			yawStep = -0.4f;
			break;
		case SDLK_w:
			yStep = 0.4f;
			break;
		case SDLK_s:
			yStep = -0.4f;
			break;
		default:;
		}
	}

	if (speed <= 0.2f && speed >= -0.1f) (speed += zStep);
	if (speed >= 0.2f) speed = 0.2f;
	if (speed <= -0.1) speed = -0.1;

	roll += rollStep;
	yaw -= -yawStep + roll / 100;

	x += xStep;
	y += yStep;
	z += zStep;

	auto vec = Vector3D<numT>(xStep, 0, speed);
	camera.GoDirection(vec);

	camera.Position().Y -= yStep;
	
	return true;
}
