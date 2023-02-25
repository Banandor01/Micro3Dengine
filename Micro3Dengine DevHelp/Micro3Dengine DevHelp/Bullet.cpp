#include "Bullet.h"

template class Bullet<float>;

template<class numT>
void Bullet<numT>::ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
								 Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling) {
	
	this->position += speed;
	
	if (visible) {
		Object3D<numT>::ObjectToWorld(camera, rotatedVerts, num, facesOut, facesNum, backfaceCulling);
	}
}