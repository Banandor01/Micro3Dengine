#pragma once

#include "Matrices.h"

template<class numT>
class Camera
{
public:
	Camera() : position(0, 0, 50)
	{ }

	void SetPosition(const Vector3D<numT>& const pos) {
		position = pos;
	}
	void SetRotation(numT x, numT y, numT z)
	{
		rotation.CreateRotationMatrix(x, y, z);
	}

	void GoDirection(Vector3D<numT>& vect) {
		vect = Vector3D<numT>(vect.X, vect.Y, -vect.Z);
	    auto dirvect = vect * rotation;
		
		position.X += -dirvect.X;
		position.Z += dirvect.Z;

	}

	Vector3D<numT> Position() const
	{
		return position;
	}

	Matrix3x3<numT> Rotation() const
	{
		return rotation;
	}
	
private:
	Vector3D<numT> position;
	Matrix3x3<numT> rotation;
};

