
#include "EngineConfig.h"
#include "Scene.h"
#include "Camera.h"

template class Scene<NUMBERTYPE>;

template<class numT>
void Scene<numT>::RenderObjects() 
{
	camera.UpdateMatrix();
	unsigned faceN = 0;
	unsigned vectorsN = 0;
	
	for (unsigned i = 0; i < objectsNumber; i++) {
		objects[i]->ObjectToWorld(&camera, vectors, vectorsN, faces, faceN, true);
	}

	// Just for test
	cameraObject.SetScale(0.1f, 0.1f, 0.1f);
	cameraObject.SetPosition(2.3f, 0.9f, 2);
	cameraObject.SetRotation(-90, 0, -camera.RotationVect().Y);
	cameraObject.ObjectToWorld(nullptr, vectors, vectorsN, faces, faceN, true);
	// just for test end

	qsort(faces, faceN, sizeof(Face3D<float>), Scene::compare);
	matrix.ProjectVectorsNoZnormalization(vectors, vectorsN);

	// From now we are in 2D space, we have faces (triangles) with normals and original z coordinates in their peaks 

	// Rendering faces
	// This is a simple frame buffer based rendering method, the scaneline algorith which is better for embedded system is comming soon
	renderer->ClearFrame(50, 50, 50);

	for (unsigned i = 0; i < faceN; i++)
	{
		float light = faces[i].normalVector.DotProduct(Vector3D<numT>(0, 0.6f, -0.6f));
		if (light < 0.1f) light = 0.1;
		Color color = *faces[i].color;
		renderer->FillTriangle<float>(faces[i], color.SetBrightness(light));
	}

	ShowInfo();
	renderer->UpdateFrame();
}

template<class numT>
void Scene<numT>::ShowInfo() 
{
	unsigned w = 500 /10;
	unsigned h = 500 /10;
	unsigned h0 = h;
	
	
	renderer->DrawLine(270, h0, 319, h0,0,0,255);
	renderer->DrawLine(270, 0, 319, 0, 0, 0, 255);

	renderer->DrawLine(270, 0, 270, h0,0,0,255);
	renderer->DrawLine(319, 0, 319, h0,0,0,255);

	unsigned x = camera.Position().X / 100;
	unsigned z = camera.Position().Z / 100;

	renderer->DrawPixel( 295 + x, h0 - z, 255, 255, 255);

	x = 0;
	z = 2000 / 100;

	renderer->DrawPixel(295 + x, h0 - z, 255, 255, 255);

}

// helpers
template<class numT>
int Scene<numT>::compare(const void* a, const void* b)
{
	auto face1 = (Face3D<float>*)a;
	auto face2 = (Face3D<float>*)b;

	auto f1 = (face1->vector1->Z + face1->vector2->Z + face1->vector3->Z) / 3;
	auto f2 = (face2->vector1->Z + face2->vector2->Z + face2->vector3->Z) / 3;

	if (f2 > f1) { return 1; }
	else { return -1; }

	return 0;
}

template<class numT>
void Scene<numT>::AddObject(Renderable<numT>* objectToAdd) {
	// TODO show the error
	if (objectsNumber < MAXOBJECTS) {
		objects[objectsNumber] = objectToAdd;
		objectsNumber++;
	}
}

template<class numT>
void Scene<numT>::RemoveObject(Renderable<numT>* objectToRemove) {
	unsigned i = 0;
	for (; i < objectsNumber; i++) {
		if (objects[i] == objectToRemove) {
			objectsNumber--;
			objects[i] = objects[objectsNumber];
			break;
		}
	}
}