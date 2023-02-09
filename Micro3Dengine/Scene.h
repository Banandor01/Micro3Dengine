#pragma once

#include "Camera.h"
#include "Face.h"

#include "object3d.h"

#define MAXOBJECTS 1000
#define MAXFACES  100000


// we will store the rotated vectors and faces in these arrays, again we are thinking it an embedded system, so no 
// heap operation is used, not so beaty but safe
template<class numT>
class Scene {

	Camera<numT> camera;
public:
	Scene(unsigned width, unsigned height)
	{
		objectsNumber = 0;
		matrix.CreatePerspective(90, width, height, 0.1, 1000);
	};
	Scene(VirtualTFT* renderer) : renderer(renderer) {
		Scene(renderer->Width, renderer->Height);
	}

	void SetScene(VirtualTFT * renderer) {
		this->renderer = renderer;
	}

	void SetCameraRotation(numT x, numT y, numT z) {
		camera.SetRotation(x, y, z);
	}

	void SetCameraPosition(numT x, numT y, numT z) {
		camera.SetPosition(Vector3D<numT>(-x, -y, -z));
	}

	Camera<numT>& Camera() { return camera; }

	void AddObject(Object3D<numT>* objectToAdd);
	void RemoveObject(Object3D<numT>* objectToRemove);
	void RenderObjects();

private:
	Vector3D<numT> vectors[MAXFACES];
	Face3D <numT> faces[MAXFACES];

	unsigned objectsNumber;
	Object3D<numT>* objects[MAXOBJECTS];

	ProjectionMatrix<float> matrix;

	VirtualTFT* renderer;
	
	// helpers
	static int compare(const void* a, const void* b)
	{
		auto face1 = (Face3D<float>*)a;
		auto face2 = (Face3D<float>*)b;

		auto f1 = (face1->vector1->Z + face1->vector2->Z + face1->vector3->Z) / 3;
		auto f2 = (face2->vector1->Z + face2->vector2->Z + face2->vector3->Z) / 3;

		if (f2 > f1) { return 1; }
		else { return -1; }

		return 0;
	}
};

template<class numT>
void Scene<numT>::AddObject(Object3D<numT>* objectToAdd) {
	// TODO sign the error
	if (objectsNumber < MAXOBJECTS) {
		objects[objectsNumber] = objectToAdd;
		objectsNumber++;
	}
}

template<class numT>
void Scene<numT>::RemoveObject(Object3D<numT>* objectToRemove) {
	unsigned i = 0;
	for (; i < objectsNumber; i++) {
		if (objects[i] == objectToRemove) {
			objectsNumber--;
			objects[i] = objects[objectsNumber];
			break;
		}
	}
}

template<class numT>
inline void Scene<numT>::RenderObjects() {

	unsigned faceN = 0;
	unsigned vectorsN = 0;

	for (unsigned i = 0; i < objectsNumber; i++) {
		objects[i]->ObjectToWorld(camera, vectors, vectorsN, faces, faceN, true);
	}
	qsort(faces, faceN, sizeof(Face3D<float>), Scene::compare);
	matrix.ProjectVectorsNoZnormalization(vectors, vectorsN);

	// From now we are in 2D space, we have faces (triangles) with normals and original z coordinates in their peaks 

	// Rendering faces
	// This is a simple frame buffer based rendering method, the scaneline algorith which is better for embedded system is comming soon
	renderer->ClearFrame(50, 50, 50);

	for (unsigned i = 0; i < faceN; i++)
	{
		float light = faces[i].normalVector.DotProduct(Vector3D<float>(0, 0, -1));
		if (light < 0.3f) light = 0.3f;

		Color color = *faces[i].color;
		renderer->FillTriangle<float>(faces[i], color.SetBrightness(light));
	}

	renderer->UpdateFrame();
}
