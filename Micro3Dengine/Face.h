#pragma once

#include "Vectors.h"
#include "Color.h"

struct Face {
public:
	Face(int i1, int i2, int i3) :
	index1(i1),
	index2(i2),
	index3(i3) 
	{}

	unsigned int index1;
	unsigned int index2;
	unsigned int index3;
};

template<class numT>
class Face3D
{
public:
	Face3D() : color(nullptr) {
		vector1 = vector2 = vector3 = nullptr;
		
	}
	Face3D(Vector3D<numT>& v1, Vector3D<numT>& v2, Vector3D<numT>& v3, Color* color) :
		vector1(v1), vector1(v2), vector1(v3), color(color)
	{}

	Vector3D<numT> CalcualteNormal() {
		Vector3D<numT> lineA = *vector2 - *vector1;
		Vector3D<numT> lineB = *vector3 - *vector1;
		
		normalVector = lineB.CrossProduct(lineA);
		normalVector.Normalize();
		return normalVector;
	}
	
// They should not be public, they public only for performance reson
public:
	Vector3D<numT>* vector1;
	Vector3D<numT>* vector2;
	Vector3D<numT>* vector3;

	Vector3D<numT> normalVector;

	Color*  color;
};

