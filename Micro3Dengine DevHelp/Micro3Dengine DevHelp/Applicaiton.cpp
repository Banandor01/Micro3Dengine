#include "Applicaiton.h"

#include "../../Micro3Dengine/Camera.h"

template class Application<float>;

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
		case SDLK_UP:	 zStep = +1.0f;
			break;
		case SDLK_DOWN:  zStep = -1.0f;
			break;
		case SDLK_LEFT:  rollStep = +0.2f;
			break;
		case SDLK_RIGHT: rollStep = -0.2f;
			break;

			//		
		case SDLK_a:
			yawStep = -0.4f;
			break;
		case SDLK_d:
			yawStep = 0.4f;
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
	yaw -= -yawStep  +roll / 200;
	pitch += yStep;

	camera.SetRotation(Pitch(), Yaw(),Roll());  
	camera.GoForward(speed, rollStep);
	camera.UpdateMatrix();

	return true;
}
