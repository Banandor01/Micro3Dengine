#pragma once

#include "..\..\Micro3Dengine\Micro3Dengine\EngineConfig.h"
#include "..\..\Micro3Dengine\Micro3Dengine\object3d.h"
#include "..\..\Micro3Dengine\Micro3Dengine\Vectors.h"
#include "..\..\Micro3Dengine\Micro3Dengine\Matrix.h"
#include "..\..\Micro3Dengine\Micro3Dengine\Face.h"
#include "..\..\Micro3Dengine\Micro3Dengine\Camera.h"

#include <vector>


template<class numT>
class TreeObj : public Object3D<numT>
{
public:
	TreeObj();
	//void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts,
	//				   unsigned int& num, Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling) override;

//	void UpdateModellToWorldMatrix() override;

private:
	static std::vector<Vector3D<numT>> verts;
	static std::vector<Face> faces;
};


