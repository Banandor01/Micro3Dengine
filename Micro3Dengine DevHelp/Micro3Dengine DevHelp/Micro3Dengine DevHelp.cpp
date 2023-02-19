// Micro3Dengine DevHelp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "models.h"
#include "VirtualTFT.h"
#include "Applicaiton.h"

#include "../../Micro3Dengine\object3d.h"
#include "../../Micro3Dengine\Matrices.h"
#include "../../Micro3Dengine\Face.h"
#include "../../Micro3Dengine\Scene.h"

#include "MeshHelper.h"

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
// Embedded device memory allocations and functions  

Application<float> app;
VirtualTFT tft(320, 240);
Scene<float> scene(320, 240);
DynamicMesh<float> mesh(scene, app);



// Declare the 3D object(s) we want to render
// Micro3Dengine is for Micro Controllers so in this example we are not using any dynamic memory allocation 
Object3D<float> bridgeObject(&bridgeVectors[0], _countof(bridgeVectors), bridgeFaces, _countof(bridgeFaces));
Object3D<float>* cubes[20];

void Init()
{
	tft.Init();
	scene.SetRenderer(&tft);
	scene.AddObject(&bridgeObject);
	bridgeObject.SetPosition(0, 0, 50);
	bridgeObject.SetRotation(0, 0, 0);
	bridgeObject.SetScale(2, 2, 2);
	bridgeObject.SetColor(Color(255, 100, 100));
	
	for (int i = 0; i < 10; i++) {
		cubes[i] = new Object3D<float>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces));
		cubes[i]->SetColor(Color(100, 240, 100));
		cubes[i]->SetScale(4, -4, 4);
		scene.AddObject(cubes[i]);
	}
}

void Loop()
{
	float zr = 0;
	scene.SetCameraPosition(0, 5, 0);
	while (app.Run())
	{
		app.HandleEvents(scene.Camera());		// Handle key event and move and rotate the camera
		mesh.UpdateMesh();
		
		zr += 0.5f;
		UpdateObjects(zr);
		scene.RenderObjects();
	}
}

void UpdateObjects(float ellapsed) {
	Vector3D<float> pos;
	for (int i = 0; i < 10; i++)
	{
		pos.Z = cos((ellapsed + i * 20) * 1.0f * M_PI / 180) * 200;
		pos.X = cos((ellapsed * 2 + i * 20) * 1.0f * M_PI / 180) * 200;
		pos.Y = sin((ellapsed / 2 + i * 20) * 1.0f * M_PI / 180) * 100;
		pos = Vector3D<float>(0, 50, 450) + pos;

		cubes[i]->SetRotation(ellapsed / 3, ellapsed / 3, 0);
		cubes[i]->SetPosition(pos);
	}
}

// If you want to understand the whole process the below link is very, very usefull 
// http://www.opengl-tutorial.org/hu/beginners-tutorials/tutorial-3-matrices/