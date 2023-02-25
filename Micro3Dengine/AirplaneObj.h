#pragma once

#include "EngineConfig.h"
#include "object3d.h"
#include "Vectors.h"
#include "Matrix.h"
#include "Face.h"
#include "Camera.h"

#include <vector>

template<class numT>
class AirplaneObj : public Object3D<numT>
{
public:
	AirplaneObj();
	void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts,
				       unsigned int& num, Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling) override;

	void UpdateModellToWorldMatrix() override;
	
private:
	std::vector<Vector3D<numT>> verts;
	std::vector<Face> faces;	
};

