#pragma once

#include "Face.h"
#include "Vectors.h"
#include "object3d.h"


// we will store the rotated vectors and faces in these arrays, again we are thinking it an embedded system, so no 
// heap operation is used, not so beaty but safe
template<class numT>
class Scene {
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

	void AddObject(Object3D<numT>* objectToAdd) {
		// TODO check there is enough store in array
		objects[objectsNumber] = objectToAdd;
		objectsNumber++;
	}

	void RemoveObject(Object3D<numT>* objectToRemove) {
		unsigned i = 0;
		for (; i < objectsNumber; i++) {
			if (objects[i] == objectToRemove) {
				objectsNumber--;
				objects[i] = objects[objectsNumber];					
				break;
			}
		}
	}

	void RenderObjects() {

		unsigned faceN = 0;
		unsigned vectorsN = 0;

		for (unsigned i = 0; i < objectsNumber; i++) {
			objects[i]->ObjectToWorld(vectors, vectorsN, faces, faceN, true);
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
			if (light < 0) light = 0;
					
			Color color = *faces[i].color;
			renderer->FillTriangle<float>(faces[i], color.SetBrightness(light));
		}

		renderer->UpdateFrame();
	}

private:
	Vector3D<numT> vectors[500];
	Face3D <numT> faces[500];

	unsigned objectsNumber;
	Object3D<numT>* objects[20];

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
