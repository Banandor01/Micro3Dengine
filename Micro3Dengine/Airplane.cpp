
#include "Airplane.h"
#include "EngineConfig.h"

template class Airplane<NUMBERTYPE>;

template<class numT>
void Airplane<numT>::Roll(numT step) {
	Mat33<numT> rot;
	rot.CreateRotationMatrix(0, 0, step);
	this->rotationMat = this->rotationMat * rot;
}

template<class numT>
void Airplane<numT>::Yaw(numT step) {
	Mat33<numT> rot;
	rot.CreateRotationMatrix(0, step, 0);
	this->rotationMat = this->rotationMat * rot;
}

template<class numT>
void Airplane<numT>::Pitch(numT step) {
	Mat33<numT> rot;
	rot.CreateRotationMatrix(step, 0, 0);
	this->rotationMat = this->rotationMat * rot;
}

template<class numT>
void Airplane<numT>::GoForward(numT step) {
	this->position += Vector3D<numT>(0, 0, step) * this->rotationMat;
}
