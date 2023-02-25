
#include "EngineConfig.h"

#include "Renderable.h"
#include "Face.h"
#include "Camera.h"

template class Renderable<NUMBERTYPE>;

template<class numT>
inline Renderable<numT>::Renderable() :
	rotation(0, 0, 0),
	scale(1, 1, 1),
	position(0, 0, 0)
{}

template<class numT>
void Renderable<numT>::SetRotation(Vector3D<numT> rvect) {
	rotation.X = rvect.X;
	rotation.Y = rvect.Y;
	rotation.Z = rvect.Z;
	rotationMat.CreateRotationMatrix(rvect.X, rvect.Y, rvect.Z);
}

template<class numT>
void Renderable<numT>::SetRotation(numT x, numT y, numT z)
{
	rotation.X = x;
	rotation.Y = y;
	rotation.Z = z;
	rotationMat.CreateRotationMatrix(x, y, z);
}

template<class numT>
void Renderable<numT>::SetPosition(numT x, numT y, numT z)
{
	position.X = x;
	position.Y = y;
	position.Z = z;
}

template<class numT>
void Renderable<numT>::SetPosition(Vector3D<numT> positionVector)
{
	position = positionVector;
}
template<class numT>
void Renderable<numT>::SetScale(numT x, numT y, numT z)
{
	scale.X = x;
	scale.Y = y;
	scale.Z = z;
}

template<class numT>
void Renderable<numT>::SetScale(Vector3D<numT>& scaleVector) {
	scale = scaleVector;
}

template<class numT>
void Renderable<numT>::UpdateModellToWorldMatrix()
{
	auto el = m2w.Elements();

	Mat33<numT> scaleMat;
	scaleMat.m00 = scale.X;
	scaleMat.m11 = scale.Y;
	scaleMat.m22 = scale.Z;

    Mat33<numT>	rMat = rotationMat *  scaleMat;

	el[0] = rMat.m00;
	el[1] = rMat.m10;
	el[2] = rMat.m20;
	el[3] = position.X;

	el[4] = rMat.m01;
	el[5] = rMat.m11;
	el[6] = rMat.m21;
	el[7] = position.Y;

	el[8] = rMat.m02;
	el[9] = rMat.m12;
	el[10] = rMat.m22;
	el[11] = position.Z;

	el[12] = 0;
	el[13] = 0;
	el[14] = 0;
	el[15] = 1;
}
