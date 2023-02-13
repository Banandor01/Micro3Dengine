
#ifndef OBJECT3D_C
#define OBJECT3D_C

#include "object3d.h"
#include "Vectors.h"
#include "Matrices.h"
#include "Face.h"
#include "Camera.h"

template<class numT>
Object3D<numT>::Object3D(const Vector3D<numT>* verts1, unsigned int vertN1, const Face* faces1, unsigned int faceN1) :
	verts(verts1),	vertN(vertN1),
	faces(faces1),	faceN(faceN1),
	rotation(0, 0, 0),
	scale(1, 1, 1),
	position(0,0,0)
{
	red = Color(255, 10, 10);
	blue = Color(10, 10, 255);
}

template<class numT>
void Object3D<numT>::SetRotation(numT x, numT y, numT z) {
	rotation.X = x;
	rotation.Y = y;
	rotation.Z = z;
}

template<class numT>
void Object3D<numT>::SetRotation(Vector3D<numT> rvect) {
	rotation.X = rvect.X;
	rotation.Y = rvect.Y;
	rotation.Z = rvect.Z;
}

template<class numT>
void Object3D<numT>::SetPosition(numT x, numT y, numT z)
{
	position.X = x;
	position.Y = y;
	position.Z = z;
}

template<class numT>
void Object3D<numT>::SetPosition(Vector3D<numT> positionVector)
{
	position = positionVector;
}
template<class numT>
void Object3D<numT>::SetScale(numT x, numT y, numT z)
{
	scale.X = x;
	scale.Y = y;
	scale.Z = z;
}

template<class numT>
void Object3D<numT>::SetScale(Vector3D<numT> scaleVector) {
	scale = scaleVector;
}

template<class numT>
void Object3D<numT>::UpdateModellToWorldMatrix()
{	
	m2w.SetRotation(rotation.X, rotation.Y, rotation.Z);
	m2w.Set(3, 0,position.X);
	m2w.Set(3, 1,position.Y);
	m2w.Set(3, 2,position.Z);
}

template <class numT>
void Object3D<numT>::ObjectToWorld(Camera<numT> *camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
								   Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling)
{
		
#ifndef ONPC
	numT* verts1 = (numT*)verts;
#endif

	unsigned offset = num;
	numT xv, yv, zv;

	UpdateModellToWorldMatrix();

	// scale, rotate and move object according to its properties 
	// TODO merge this opeariotns to one matrix
	for (unsigned i = 0; i < vertN; i++)
	{
#ifndef ONPC
		xv = pgm_read_float(verts1) * scale.x;  verts1++;
		yv = pgm_read_float(verts1) * scale.y;  verts1++;
		zv = pgm_read_float(verts1) * scale.z;  verts1++;
#else 
		xv = verts[i].X * scale.X;
		yv = verts[i].Y * scale.Y;
		zv = verts[i].Z * scale.Z;
#endif
		Vector3D<numT> vect(xv, yv, zv);
		vect = vect * m2w;

		if (camera != nullptr) {
			vect = vect * camera->GetMatrix();
		}
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

template < class numT >
Vector3D<numT> Object3D<numT>::CalcNormals(const Vector3D<numT>& p1, const Vector3D<numT>& p2, const Vector3D<numT>& p3)
{
	Vector3D<numT> U = (p2 - p1);
	Vector3D<numT> V = (p3 - p1);
	Vector3D<numT> surfaceNormal;

	surfaceNormal.x = (U.y * V.z) - (U.z * V.y);
	surfaceNormal.y = (U.z * V.x) - (U.x * V.z);
	surfaceNormal.z = (U.x * V.y) - (U.y * V.x);

	return surfaceNormal.Normalize();
}

#endif

