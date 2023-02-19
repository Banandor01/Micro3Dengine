#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Matrices.h"
#include "Face.h"

template<class T>
class Vector3D;
template<class T>
class Camera;
class Face;


/// <summary>
/// Base class of all 3D object 
/// </summary>
template<class numT>
class Renderable 
{
public:
	Renderable();

	void SetRotation(numT x, numT y, numT z);
	void SetRotation(Vector3D<numT> rvect);
	void SetPosition(numT x, numT y, numT z);
	void SetPosition(Vector3D<numT> positionVector);
	void SetScale(numT x, numT y, numT z);
	void SetScale(Vector3D<numT> scaleVector);
	void SetColor(Color color) { this->color = color; }
	Color& GetColor() { return color; }
	Vector3D<numT>& Position() { return position; }
	
	void UpdateModellToWorldMatrix();	// Calculate the modell to world matrix according to the Object's position, scale and rotation
	static Vector3D<numT> CalcNormals(const Vector3D<numT>& p1, const Vector3D<numT>& p2, const Vector3D<numT>& p3);	// calculate normal of given face

	// virtual methods
	// Apply Rotation, Sacling and translation inorder to move model into world space with set orreintation
	virtual void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
								Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling = ture) = 0;
protected:
	Vector3D<numT> position;
	Vector3D<numT> rotation;
	Vector3D<numT> scale;	
	Mat44<numT> m2w;	// Modell to world matrix

	Color red;			// used for clip testing 
	Color blue;			// used for clip testing
	Color color;
};


/// <summary>
/// Represent a rendereble 3D object with its vericies and faces
/// </summary>
/// <typeparam name="numT"></typeparam>
template <class numT>
class Object3D : public Renderable<numT> {
public:
	Object3D (const Vector3D<numT> * verts1, unsigned int vertN1, 
			  const Face * faces1, unsigned int faceN1);

	void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
					   Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling = ture);

private:
	const    Face* faces;			// the mesh of the objects
	const    Vector3D<numT>* verts;
	unsigned int faceN;
	unsigned int vertN;	
};

#endif

