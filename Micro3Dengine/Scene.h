#pragma once

#include "Camera.h"
#include "Face.h"
#include "object3d.h"

#include "../Micro3Dengine DevHelp/Micro3Dengine DevHelp/VirtualTFT.h"
#include "../Micro3Dengine DevHelp/Micro3Dengine DevHelp/ArrowModell.h"

#define MAXOBJECTS 1000
#define MAXFACES  100000

template<class numT>
class Scene 
{
	Camera<numT> camera;
public:
	Scene() : objectsNumber(0),
		cameraObject(&Cubevectors2[0], _countof(Cubevectors2), &cubeFaces2[0], _countof(cubeFaces2))
	{}
	Scene(unsigned width, unsigned height) :
		cameraObject(&Cubevectors2[0], _countof(Cubevectors2), &cubeFaces2[0], _countof(cubeFaces2))
	{
		objectsNumber = 0;
		matrix.CreatePerspective(90, width, height, 0.1, 1000);
	};
	Scene(VirtualTFT* renderer) : renderer(renderer) ,
		cameraObject(&Cubevectors2[0], _countof(Cubevectors2), &cubeFaces2[0], _countof(cubeFaces2)) 
	{
		objectsNumber = 0;
		matrix.CreatePerspective(90, renderer->Width(), renderer->Height(), 0.1, 1000);
	}

	void SetRenderer(VirtualTFT* tft) { renderer = tft;	}

	// Camera handling
	void SetCameraRotation(numT x, numT y, numT z) { camera.SetRotation(x, y, z); }
	void SetCameraPosition(numT x, numT y, numT z) { camera.SetPosition(Vector3D<numT>(x, y, z)); }
	Camera<numT>& Camera() { return camera; }
	
	// Object handling
	void AddObject(Renderable<numT>* objectToAdd);
	void RemoveObject(Renderable<numT>* objectToRemove);
	
	// The magic happens here 
	void RenderObjects();

private:
	// we will store the rotated vectors and faces in these arrays, again we are thinking it an embedded system, so no 
	// heap operation is used, not so beaty but safe
	Vector3D<numT> vectors[MAXFACES];
	Face3D <numT> faces[MAXFACES];
	Renderable<numT>* objects[MAXOBJECTS];
	unsigned objectsNumber;

	ProjectionMatrix<numT> matrix;
	VirtualTFT* renderer;

private:
	// helpers
	static int compare(const void* a, const void* b);
	void ShowInfo();
	Object3D<numT> cameraObject;
};
