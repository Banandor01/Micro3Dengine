#pragma once

#include "../../Micro3Dengine\object3d.h"
#include "../../Micro3Dengine\Matrix.h"
#include "../../Micro3Dengine\Face.h"
#include "../../Micro3Dengine\Scene.h"

#include <vector> 
#include "perlin.h"
#include "Applicaiton.h"

template<class numT>
class SquareMesh;

template<class numT>
class DynamicMesh {
public:
	DynamicMesh(Scene<numT>& scene1, Application<numT> & application);
	void UpdateMesh();

private:
	const unsigned meshPointDistance;
	SquareMesh<numT> meshes[40];
	Perlin perlin;
	Scene<numT>& scene;
	Application<numT>& application;
	Vector3D<numT> fustrum[40];
	unsigned visibleMeshes;
};


template<class numT>
class SquareMesh : public Renderable<numT> {
public: 
	SquareMesh();

	void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
		Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling = true) override;

	void CreateMesh(Perlin& perlin, Vector3D<numT>& pos, int offsetx, int offsetz);

	void SetMeshPointDistance(unsigned distance);
	void Visible(bool visible);
private:

	int meshPointDistance;
	Vector3D<float> verticies[11 * 11];
	Face			faces[200];
	bool visible;

	int oldx, oldz;
};



