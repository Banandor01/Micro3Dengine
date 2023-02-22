
#include "EngineConfig.h"
#include "Camera.h"

template class Camera<NUMBERTYPE>;

template<class numT>
inline void Camera<numT>::SetPosition(const Vector3D<numT>& pos) {
	position = pos;
}

template<class numT>
void Camera<numT>::SetRotation(numT x, numT y, numT z)
{
	rotation.CreateRotationMatrix(x, y, z);
	rotVect.X = x; rotVect.Y = y; rotVect.Z = z;
}

template<class numT>
void Camera<numT>::GoForward(numT zStep, numT xStep)
{	
	position += Vector3D<numT>(xStep, 0, zStep) * rotation;
}

template<class numT>
void Camera<numT>::UpdateMatrix()
{
	auto up = Vector3D<numT>(0, 1, 0) * rotation;
	auto dir = Vector3D<numT>(0, 0, 1) * rotation;
	LookDirection(position, dir, up);
}

template<class numT>
inline Vector3D<numT>& Camera<numT>::Position() {
	return position;
}

template<class numT>
Mat44<numT> & Camera<numT>::GetMatrix() {
	return matrix4;
}

template<class numT>
Mat33<numT>& Camera<numT>::RotationMatrix() {
	return rotation;
}
template<class numT>
Vector3D<numT>& Camera<numT>::RotationVect() {
	return rotVect; 
}

template<class numT>
inline void Camera<numT>::LookDirection(Vector3D<numT> eye, Vector3D<numT> dir, Vector3D<numT> up)
{
	// Calculate new axises
	//Vector3D<float> zaxis = (at - eye).Normalize();
	Vector3D<numT> zaxis = dir.Normalize();
	Vector3D<numT> xaxis = up.CrossProduct(zaxis).Normalize();
	Vector3D<numT> yaxis = zaxis.CrossProduct(xaxis).Normalize();

	// Construc matrix	
	auto m = matrix4.Elements();
	
	m[0] = xaxis.X;	m[1] = xaxis.Y; m[2] =  xaxis.Z;  m[3] = -xaxis.DotProduct(eye);
	m[4] = yaxis.X;	m[5] = yaxis.Y; m[6] =  yaxis.Z;  m[7] = -yaxis.DotProduct(eye);
	m[8] = zaxis.X;	m[9] = zaxis.Y; m[10] = zaxis.Z;  m[11]= -zaxis.DotProduct(eye);

	m[12] = 0.0f;	m[13] = 0.0f;   m[14] = 0.0f;	 m[15]= 1;
}
