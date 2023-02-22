#pragma once

#include "SDL.h"

template<class numT>
class MovableBase;

template<class numT>
class Application
{
public:
	Application();

	bool HandleEvents(MovableBase<numT> & player);
	bool Run() { return run; }

private:
	numT yawStep, rollStep, pitchStep;
	numT ts, t; // just for test
	numT speedStep;
	numT speed;

	bool run;
};