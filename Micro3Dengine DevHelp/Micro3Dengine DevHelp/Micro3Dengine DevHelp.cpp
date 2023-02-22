// Micro3Dengine DevHelp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "models.h"
#include "VirtualTFT.h"
#include "Applicaiton.h"

#include "../../Micro3Dengine/object3d.h"
#include "../../Micro3Dengine/Matrix.h"
#include "../../Micro3Dengine/Face.h"
#include "../../Micro3Dengine/Scene.h"
#include "../../Micro3Dengine/AirplaneObj.h"

#include "../../Micro3Dengine/AirPlane.h"	// TODO move out from this folder

#include "MeshHelper.h"
#include <iostream>

#include <Windows.h>
using namespace std;

void Init();
void Loop();
void UpdateObjects(float ellapsed);

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	Init();
	Loop();
}

// ******************************************************************************************************************
// Memroy allocation in embedded style no dynamic memory

Application<float> app;
VirtualTFT tft(320, 240);
Scene<float> scene(320, 240);

DynamicMesh<float> mesh(scene, app);
AirplaneObj<float> airplaneObj;
Airplane<float> airplane;


// Declare the 3D object(s) we want to render
// Micro3Dengine is for Micro Controllers so in this example we are not using any dynamic memory allocation 
Object3D<float> bridgeObject(&bridgeVectors[0], _countof(bridgeVectors), bridgeFaces, _countof(bridgeFaces));
Object3D<float>* cubes[20];

void Init()
{
	tft.Init();
	scene.SetRenderer(&tft);
	scene.AddObject(&bridgeObject);
	bridgeObject.SetPosition(0, 0, 2000);
	bridgeObject.SetRotation(0, 0, 0);
	bridgeObject.SetScale(10, 10, -10);
	bridgeObject.SetColor(Color(255, 100, 100));

	airplaneObj.SetPosition(0, -13, 32);
	airplaneObj.SetScale(1, 1, 1);
	airplaneObj.SetRotation(0, 0, 0);
	scene.AddObject(&airplaneObj);

	
	for (int i = 0; i < 10; i++) {
		cubes[i] = new Object3D<float>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces));
		cubes[i]->SetColor(Color(100, 240, 100));
		cubes[i]->SetScale(4, 4, 4);
		scene.AddObject(cubes[i]);
	}
}

void Loop()
{
	Vector3D<float> planeRotVect = airplane.RotationVect();

	int i = 0;
	float zr = 0;
	while (app.Run())
	{
		app.HandleEvents(airplane);			// Move plane
		
		Vector3D<float> cameraRot = scene.Camera().RotationVect();
		Vector3D<float> planeRot;
	
		scene.Camera().Position() = airplane.Position();			// Move and rotate scene camera according to airplane position and orientation
		auto airplaneRot = airplane.RotationMatrix().ToEulerAngles();
		scene.Camera().SetRotation(airplaneRot.X, airplaneRot.Y, airplaneRot.Z);

		auto difference =  airplaneRot - planeRotVect;
		planeRotVect += difference / 50;
		airplaneObj.SetRotation(difference.X, difference.Y, difference.Z);

	 	mesh.UpdateMesh();
		
		zr += 0.2f;
		UpdateObjects(zr);
		scene.RenderObjects();
	}
}

void UpdateObjects(float ellapsed) {
	Vector3D<float> pos;
	for (int i = 0; i < 10; i++)
	{
		pos.Z = 4000;
		pos.X = cos((ellapsed + i * 36) * 1.0f * M_PI / 180) * 150;
		pos.Y = sin((ellapsed + i * 36) * 1.0f * M_PI / 180) * 150;
		
		cubes[i]->SetRotation(ellapsed, ellapsed, 0);
		cubes[i]->SetPosition(pos);
	}
}

// If you want to understand the whole process the below link is very, very usefull 
// http://www.opengl-tutorial.org/hu/beginners-tutorials/tutorial-3-matrices/