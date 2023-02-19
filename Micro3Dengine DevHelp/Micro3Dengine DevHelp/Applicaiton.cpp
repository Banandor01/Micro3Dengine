#include "Applicaiton.h"

#include "../../Micro3Dengine/EngineConfig.h"
#include "../../Micro3Dengine/Camera.h"

template class Application<NUMBERTYPE>;

template<class numT>
inline Application<numT>::Application() :
	run(true),
	xStep(0), zStep(0),
	roll(0), yaw(0), pitch(0), t(0),
	rollStep(0), yawStep(0), pitchStep(0),
	speed(0), ts(0)
{}

template<class numT>
bool Application<numT>::HandleEvents(Camera<numT>& camera) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {

	case SDL_QUIT:
		run = false;
		break;
	case SDL_KEYUP:
		xStep = zStep;
		yawStep = 0; zStep = 0;
		rollStep = 0; pitchStep = 0;
		ts = 0;
		break;
	case SDL_KEYDOWN:

		switch (event.key.keysym.sym) {
		case SDLK_1:
			break;
		case SDLK_2:
			break;

		case SDLK_UP:	 pitchStep = 0.4f;
			break;
		case SDLK_DOWN:  pitchStep = -0.4f;
			break;
		case SDLK_LEFT:  rollStep = +0.2f;
			break;
		case SDLK_RIGHT: rollStep = -0.2f;
			break;

		case SDLK_a: yawStep = -0.4f;
			break;
		case SDLK_d: yawStep = 0.4f;
			break;

		case SDLK_w: zStep = 0.4f;
			break;
		case SDLK_s: zStep = -0.4f;
			break;
		case SDLK_x: speed = 0;
			break;

		case SDLK_g: ts = 0.4f;
			break;
		case SDLK_h: ts = -0.4f;
			break;
		default:;
		}
	}

	if (speed <= 2.5f && speed >= -1.4f) (speed += zStep);
	if (speed >= 2.5f) speed = 2.5f;
	if (speed <= -1.4) speed = -1.4;

	roll += rollStep;
	yaw += yawStep; // +roll / 200;
	pitch += pitchStep;
	t += ts;

	camera.SetRotation(Pitch(), Yaw(), Roll());
	camera.UpdateMatrix();
	camera.GoForward(speed, 0);

	return true;
}
