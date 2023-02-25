#pragma once

#include "EngineConfig.h"
#include "object3d.h"
#include "Face.h"
#include "Camera.h"

template class Object3D<NUMBERTYPE>;

template<class numT>
Object3D<numT>::Object3D(const Vector3D<numT>* verts1, unsigned int vertN1, const Face* faces1, unsigned int faceN1) :
	verts(verts1), vertN(vertN1),
	faces(faces1), faceN(faceN1)
{}

template <class numT>
void Object3D<numT>::ObjectToWorld(Camera<numT> *camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
								   Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling)
{
#ifndef ONPC
	numT* verts1 = (numT*)verts; 
#endif
	unsigned offset = num;
	this->UpdateModellToWorldMatrix();

	if (camera != nullptr) { this->m2w = camera->GetMatrix() * this->m2w; }
	
	for (unsigned i = 0; i < vertN; i++)
	{
#ifndef ONPC
		xv = pgm_read_float(verts1) * scale.x;  verts1++;
		yv = pgm_read_float(verts1) * scale.y;  verts1++;
		zv = pgm_read_float(verts1) * scale.z;  verts1++;
#endif
		Vector3D<numT>vect = verts[i] * this->m2w;
		rotatedVerts[offset+i] = vect;
	}
	num += vertN;

	// Create Faces
	for (unsigned int i = 0; i < faceN; i++)
	{
		Face3D<numT> face;
		face.vector1 = &rotatedVerts[faces[i].index1 + offset];
		face.vector2 = &rotatedVerts[faces[i].index2 + offset];
		face.vector3 = &rotatedVerts[faces[i].index3 + offset];
		
		// if the face is behind the camera we skip that face
		if (face.vector1->Z < 0.2f && face.vector2->Z < 0.2f && face.vector3->Z < 0.2f) { continue;	}
		// primitiv clipping TODO make a real plane clipping
		if (face.vector1->Z < 0.2f) { face.vector1->Z = 0.2f; }//face.color = &this->red; }
		if (face.vector2->Z < 0.2f) { face.vector2->Z = 0.2f; }//face.color = &this->red; }
		if (face.vector3->Z < 0.2f) { face.vector3->Z = 0.2f; }//face.color = &this->red; }			
		
		face.color = &this->color;

		Vector3D<numT> normal = face.CalcualteNormal();
		auto cameraToFace = *(face.vector1);

		if (backfaceCulling) {			
			if (normal.DotProduct(cameraToFace) < 0) {
				facesOut[facesNum] = face;
				facesNum++;
			}
		}
		else {
			facesOut[facesNum] = face;
			facesNum++;
		}
	}	
}