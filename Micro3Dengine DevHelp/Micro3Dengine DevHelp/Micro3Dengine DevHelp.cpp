// Micro3Dengine DevHelp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "models.h"
#include "VirtualTFT.h"
#include "Applicaiton.h"

#include "../../Micro3Dengine\object3d.h"
#include "../../Micro3Dengine\Matrices.h"
#include "../../Micro3Dengine\Face.h"
#include "../../Micro3Dengine\Scene.h"


#include <vector>
#include <Windows.h>


using namespace std;

void Init();
void Loop();
void CreateObjects();

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nShowCmd)
{
	Init();
	Loop();

	std::getchar();
}

// ******************************************************************************************************************
// Embedded device memory allocations and functions  

Application<float> app;
VirtualTFT tft(320, 240);
Scene<float> scene(320, 240);

// Declare the 3D object(s) we want to render
// Micro3Dengine is for Micro Controllers so in this example we are not using any dynamic memory allocation 
Object3D<float> bridgeObject(&bridgeVectors[0], _countof(bridgeVectors), bridgeFaces, _countof(bridgeFaces));
Object3D<float>* cubes[20];
Object3D<float>* cubes2[500];

// just for test on PC
vector<Vector3D<float>> roadVectors;
vector<Face> roadFaces;

void Init()
{
	tft.Init();
	scene.SetScene(&tft);
	scene.AddObject(&bridgeObject);
	CreateObjects();
}

void Loop()
{
	float zr = 0;
	
	scene.SetCameraPosition(-70, 0, 100);
	while (app.Run())
	{
		app.HandleEvents(scene.Camera());
		scene.SetCameraRotation(0, app.Yaw(), app.Roll());

		zr += 0.5f;
		Vector3D<float> pos;
		for (int i = 0; i < 10; i++)
		{
			pos.Z = 0;
			pos.X = cos((zr + i * 20) * 1.0f * M_PI / 180) * 25;
			pos.Y = sin((zr + i * 20) * 1.0f * M_PI / 180) * 35;

			pos = Vector3D<float>(70, -12, 50) + pos;

			cubes[i]->SetRotation(zr / 3, zr / 3, 0);
			cubes[i]->SetPosition(pos);
			cubes[i]->SetScale(0.5, -0.5, 0.5);
		}

		scene.RenderObjects();
	}
}

// If you want to understand the whole process the below link is very, very usefull 
// http://www.opengl-tutorial.org/hu/beginners-tutorials/tutorial-3-matrices/


void CreateObjects()
{
	for (int i = 0; i < 10; i++) {
		cubes[i] = new Object3D<float>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces));

		cubes[i]->SetColor(Color(100, 240, 100));
		scene.AddObject(cubes[i]);
	}

	const float toRad = M_PI / 180;

	for (int i = 0; i < 180; i += 2) {
		float x = cos(i * 2 * toRad) * 90 + cos(i * 10 * toRad) * 5;
		float x2 = cos(i * 2 * toRad) * 50 + sin(i * 10 * toRad) * 5;
		float z = 100 + sin(i * 2 * toRad) * 250;
		float z2 = 100 + sin(i * 2 * toRad) * 200;

		roadVectors.push_back(Vector3D<float>(x, -15, z));
		roadVectors.push_back(Vector3D<float>(x2, -15, z2));

		cubes2[i] = new Object3D<float>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces));
		cubes2[i]->SetPosition(x2, -11, z2);
		cubes2[i]->SetColor(Color(100, 100, 100));
		cubes2[i]->SetScale(0.5f, -1.0f, 0.5f);
		scene.AddObject(cubes2[i]);

		cubes2[i + 1] = new Object3D<float>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces));
		cubes2[i + 1]->SetPosition(x, -11, z);
		cubes2[i + 1]->SetColor(Color(100, 100, 100));		
		cubes2[i + 1]->SetScale(0.5f, -1.0f, 0.5f);
		scene.AddObject(cubes2[i + 1]);
	}

	bridgeObject.SetRotation(0, 0, 0);
	bridgeObject.SetPosition(-70, -25, 50);
	bridgeObject.SetScale(4, 8, 18);
	bridgeObject.SetColor(Color(200, 100, 100));

	for (int i = 0; i < 178; i += 2) {
		roadFaces.push_back(Face(i + 1, i, i + 2));
		roadFaces.push_back(Face(i + 3, i + 1, i + 2));
	}

	roadFaces.push_back(Face(179, 178, 0));
	roadFaces.push_back(Face(179, 0, 1));

	auto road = new Object3D<float>(&roadVectors[0], roadVectors.size(),
									&roadFaces[0], roadFaces.size());

	scene.AddObject(road);
	road->SetColor(Color(150, 250, 250));
}