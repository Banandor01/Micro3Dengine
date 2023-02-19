#pragma once

#include "Vectors.h"
#include "Color.h"


class Face {
public:
	Face() {}
	Face(int i1, int i2, int i3);

	unsigned int index1;
	unsigned int index2;
	unsigned int index3;
};

template<class numT>
class Face3D
{
public:
	Face3D();
	Face3D(Vector3D<numT>& v1, Vector3D<numT>& v2, Vector3D<numT>& v3, Color* color);
	Vector3D<numT> CalcualteNormal();
	
public:
	// They should not be public, they public only for performance reson
	Vector3D<numT>* vector1;
	Vector3D<numT>* vector2;
	Vector3D<numT>* vector3;
	Vector3D<numT> normalVector;
	Color*  color;
};
