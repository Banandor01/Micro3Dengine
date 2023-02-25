#pragma once

#include "Matrix.h"

template<class numT>
class Camera
{
public:
	Camera() : position(0, 0, 0) {}

	void SetPosition(const Vector3D<numT>& pos);
	void SetRotation(const Vector3D<numT> rotVect);
	void GoForward(numT zStep, numT xStep);
	void UpdateMatrix();	// calculate Matrix
	
	Mat33<numT>& RotationMatrix();
	Vector3D<numT>& RotationVect();
	Vector3D<numT>& Position();
	
	Mat44<numT>& GetMatrix();
private:
	void LookDirection(Vector3D<numT> pos, Vector3D<numT> direction, Vector3D<numT> up);
	Vector3D<numT> position;
	Vector3D<numT> rotVect;
	Mat33<numT> rotation;

	Mat44<numT> cameraMatrix;
};
