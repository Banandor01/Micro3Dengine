
#ifndef OBJECT3D_C
#define OBJECT3D_C

#include "object3d.h"
#include "Vectors.h"
#include "Matrices.h"
#include "Face.h"

template<class numT>
Object3D<numT>::Object3D(const Vector3D<numT>* verts1, unsigned int vertN1, const Face* faces1, unsigned int faceN1) :
	verts(verts1),	vertN(vertN1),
	faces(faces1),	faceN(faceN1),
	orientation(0, 0, 0),
	scale(1, 1, 1),
	position(0,0,0)
{
}

template<class numT>
void Object3D<numT>::SetRotation(numT x, numT y, numT z) {
	orientation.X = x;
	orientation.Y = y;
	orientation.Z = z;
	rotationMatrix.CreateRotationMatrix(x, y, z);
}

template<class numT>
void Object3D<numT>::SetRotationMatrix(Matrix3x3<numT> & rotMatrix)
{
	rotationMatrix = rotationMatrix;
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

template <class numT>
void Object3D<numT>::ObjectToWorld(Vector3D<numT>* rotatedVerts, unsigned int& num,
								   Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling)
{
		
#ifndef ONPC
	numT* verts1 = (numT*)verts;
#endif

	unsigned offset = num;
	numT xv, yv, zv;

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
		vect = vect * rotationMatrix;

		rotatedVerts[offset+i].X = vect.X + position.X;
		rotatedVerts[offset+i].Y = vect.Y + position.Y;
		rotatedVerts[offset+i].Z = vect.Z + position.Z;
	}
	num += vertN;

	// Create Faces
	for (unsigned int i = 0; i < faceN; i++)
	{
		Face3D<numT> face;
		face.vector1 = &rotatedVerts[faces[i].index1+offset];
		face.vector2 = &rotatedVerts[faces[i].index2+offset];
		face.vector3 = &rotatedVerts[faces[i].index3+offset];

		face.color = &this->color;

		Vector3D<numT> normal = face.CalcualteNormal();
		if (backfaceCulling) {			
			if (normal.DotProduct(*face.vector1) < 0) {
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

