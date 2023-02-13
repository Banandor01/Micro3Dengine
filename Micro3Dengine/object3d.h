#ifndef OBJECT3D_H
#define OBJECT3D_H

template<class T>
class Vector3D;
template<class T>
class Camera;
struct Face;

#include "Matrices.h"
#include "Face.h"

/// <summary>
/// Represent a rendereble 3D object (a mesh) with its vericies and faces
/// </summary>
/// <typeparam name="numT"></typeparam>
template <class numT>
class Object3D {
public:
	Object3D (const Vector3D<numT> * verts1, unsigned int vertN1, 
			  const Face * faces1, unsigned int faceN1);
	
	void SetRotation(numT x, numT y, numT z);
	void SetRotation(Vector3D<numT> rvect);
	void SetPosition(numT x, numT y, numT z);
	void SetPosition(Vector3D<numT> positionVector);

	void SetScale(numT x, numT y, numT z);
	void SetScale(Vector3D<numT> scaleVector);

	void SetColor(Color color) { this->color = color; }
	
	// Calculate the modell to world matrix according to the Object's position, scale and rotation
	void UpdateModellToWorldMatrix();

	// Apply Rotation, Sacling and translation inorder to move model into world space with set orreintation
	void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
					   Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling = ture);
	

	Color& GetColor() { return color; }
	Vector3D<numT>& Position() { return position; }

	// calculate normal of given face
static Vector3D<numT> CalcNormals(const Vector3D<numT> &p1, const Vector3D<numT> &p2, const Vector3D<numT> &p3);

private:
	// the mesh of the objects
	const    Face* faces;
	const    Vector3D<numT>* verts;
	unsigned int faceN;
	unsigned int vertN;
	
	// Object properties
	Vector3D<numT> position;
	Vector3D<numT> rotation;
	Vector3D<numT> scale;
	// Modell to world matrix
	Mat44<numT> m2w;
	
	Color red;			// used for clip testing 
	Color blue;			// used for clip testing
	Color color;
};

// because tempalte class
#include "object3d.cpp"

#endif

