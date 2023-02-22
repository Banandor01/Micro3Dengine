#pragma once

#include "interfaces/MovableBase.h"

template<class numT>
class Airplane : public MovableBase<numT> {
public:
	void Roll(numT step) override;
	void Yaw(numT step) override;
	void Pitch(numT step) override;
	void GoForward(numT step) override;
};