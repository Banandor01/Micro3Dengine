#include "Applicaiton.h"

#include "../../Micro3Dengine/EngineConfig.h"
#include "../../Micro3Dengine/Interfaces/MovableBase.h"

template class Application<NUMBERTYPE>;

template<class numT>
inline Application<numT>::Application() :
	run(true),
	t(0), ts(0),
	rollStep(0), yawStep(0), pitchStep(0),
	speed(0)
{}

template<class numT>
bool Application<numT>::HandleEvents(Airplane<numT>& player) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {

	case SDL_QUIT:
		run = false;
		break;
	case SDL_KEYUP:
		yawStep = 0; rollStep = 0; pitchStep = 0;
		ts = 0; speedStep = 0;
		break;
	case SDL_KEYDOWN:

		switch (event.key.keysym.sym) {
		case SDLK_1:
			break;
		case SDLK_2:
			break;

		case SDLK_UP:	 pitchStep = 0.8f;
			break;
		case SDLK_DOWN:  pitchStep = -0.8f;
			break;

		case SDLK_LEFT:  rollStep = +0.8f;
			break;
		case SDLK_RIGHT: rollStep = -0.8f;
			break;

		case SDLK_a: yawStep = -0.8f;
			break;
		case SDLK_d: yawStep = 0.8f;
			break;

		case SDLK_w: speedStep = 0.01f;
			break;
		case SDLK_s: speedStep = -0.01f;
			break;
		case SDLK_x: speed = 0;
			break;

		case SDLK_g: ts = 0.4f;
			break;
		case SDLK_h: ts = -0.4f;
			break;
		case SDLK_SPACE:
		    player.Fire();
			break;
		
		
		default:;
		}
	}

	if (yawStep != 0 || rollStep != 0 || pitchStep != 0) {
		player.Roll(rollStep);
		player.Pitch(pitchStep);
		player.Yaw(yawStep);
	}
	
	if (speedStep > 0) { player.SpeedUp(); }
	else  if (speedStep <0) {
		player.SpeedDown();
	}

	player.Update();

	return true;
}
