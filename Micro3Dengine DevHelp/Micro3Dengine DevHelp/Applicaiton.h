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
		run(true), x(0), y(0) ,
		xstep(0), ystep(0),
		roll(0), rs(0), 
		speed (0.1f)
	{}	

	bool HandleEvents(Camera<numT> & camera);
	
	bool Run() { return run; }
	float X() { return x; }
	float Y() { return y; }

	float Roll()  { return roll; }
	float Pitch() { return pitch; }

private:
	float xstep, ystep;
	float x, y;

	float ps, rs;
	float pitch, roll;
	
	float speed;
	bool run;
};


template<class numT>
bool Application<numT>::HandleEvents(Camera<numT>& camera) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {

	case SDL_QUIT:
		run = false;
		break;
	case SDL_KEYUP:
		xstep = ystep = rs = 0;
		break;
	case SDL_KEYDOWN:

		switch (event.key.keysym.sym) {
		case SDLK_1:
			break;
		case SDLK_2:
			break;

		case SDLK_UP: ystep = +0.002f;
			break;
		case SDLK_DOWN: ystep = -0.002f;
			break;
		case SDLK_LEFT: xstep = -0.1f;
			break;
		case SDLK_RIGHT: xstep = 0.1f;
			break;
		case SDLK_a:
			rs = 0.4f;
			break;
		case SDLK_d:
			rs = -0.4f;
			break;
		default:;
		}
	}

	if (speed <= 0.2f && speed >= 0) (speed += ystep);

	if (speed >= 0.2f) speed = 0.2f;
	if (speed <= 0) speed = 0;

	roll += rs;
	auto vec = Vector3D<numT>(xstep, 0, speed);
	camera.GoDirection(vec);

	x += xstep;
	y += ystep;
	return true;
}
