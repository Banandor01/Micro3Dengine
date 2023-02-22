#pragma once

#include "../Matrix.h"

template <class numT>
class MovableBase {
public:

	virtual void Yaw(numT step) {}
	virtual void Roll(numT step) {}
	virtual void Pitch(numT step) {}
	
	virtual void GoForward(numT steps) {}

    Mat33<numT>& RotationMatrix() { return rotationMat; }
	Vector3D<numT>& RotationVect() { return rotationVect; }
	Vector3D<numT>& Position() { return position; }
protected:
	Vector3D<numT> position;
	Vector3D<numT> rotationVect;
	Mat33<numT>	   rotationMat;
};