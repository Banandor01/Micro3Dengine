
#include "EngineConfig.h"
#include "Face.h"

template class Face3D<NUMBERTYPE>;

template<class numT>
Face3D<numT>::Face3D(Vector3D<numT>& v1, Vector3D<numT>& v2, Vector3D<numT>& v3, Color* color) :
	vector1(&v1), vector2(&v2), vector3(&v3), color(color)
{}

template<class numT>
Face3D<numT>::Face3D() : color(nullptr) 
{
	vector1 = vector2 = vector3 = nullptr;
}

template<class numT>
Vector3D<numT> Face3D<numT>::CalcualteNormal() {
	Vector3D<numT> lineA = *vector2 - *vector1;
	Vector3D<numT> lineB = *vector3 - *vector1;

	normalVector = lineB.CrossProduct(lineA);
	normalVector.Normalize();
	return normalVector;
}

/// <summary>
/// Face
/// </summary>
Face::Face(int i1, int i2, int i3) :
	index1(i1),
	index2(i2),
	index3(i3)
{}
