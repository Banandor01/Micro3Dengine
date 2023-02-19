#pragma once

#include "Matrices.h"

template<class numT>
class Camera
{
public:
	Camera() : position(0, 0, 0) {}

	void SetPosition(const Vector3D<numT>& pos);
	void SetRotation(numT x, numT y, numT z);
	void GoForward(numT zStep, numT xStep);
	void UpdateMatrix();	// calculate Matrix
	
	Mat33<numT>& GetRotationMatrix();
	Vector3D<numT>& GetRotationVect();
	Vector3D<numT>& Position();
	Mat44<numT>& GetMatrix();
private:
	void LookDirection(Vector3D<numT> pos, Vector3D<numT> direction, Vector3D<numT> up);
	Mat44<numT> matrix4;
	Vector3D<numT> position;
	Vector3D<numT> rotVect;
	Mat33<numT> rotation;
};
