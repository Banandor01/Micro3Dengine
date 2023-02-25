#pragma once

#include "Renderable.h"

/// <summary>
/// Represent a rendereble 3D object with its vericies and faces
/// </summary>
template <class numT>
class Object3D : public Renderable<numT> {
public:
	Object3D (const Vector3D<numT> * verts1, unsigned int vertN1, 
			  const Face * faces1, unsigned int faceN1);
	
	void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
					   Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling = ture) override;

protected:
	const    Face* faces;			// the mesh of the objects
	const    Vector3D<numT>* verts;
	unsigned int faceN;
	unsigned int vertN;	
};