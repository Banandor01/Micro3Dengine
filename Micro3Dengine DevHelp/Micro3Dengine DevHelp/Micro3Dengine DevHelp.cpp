// Micro3Dengine DevHelp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "models.h"
#include "VirtualTFT.h"
#include "Applicaiton.h"

#include "../../Micro3Dengine\object3d.h"
#include "../../Micro3Dengine\Matrices.h"
#include "../../Micro3Dengine\Face.h"
#include "../../Micro3Dengine\Scene.h"

#include <Windows.h>

void Init();
void Loop();

int WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,
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

void Init()
{
	tft.Init();
	
	scene.SetScene(&tft);
	scene.AddObject(&bridgeObject);

	for (int i = 0; i < 10; i++) {
		cubes[i] = new Object3D<float>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces));
		
		cubes[i]->SetColor(Color(100,240,100));
		scene.AddObject(cubes[i]);
	}

	const float toRad = M_PI / 180;

	for (int i = 0; i  < 180; i+=2) {
		float x =  cos(i * 2 * toRad) * 80;
	    float x2 = cos(i * 2 * toRad) * 60;
		float z =  100 + sin(i *2  * toRad) * 200;
		float z2 =  100 + sin(i * 2 * toRad) * 300;

		cubes2[i] = new Object3D<float>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces));
		cubes2[i]->SetPosition(x2, -5, z);
		cubes2[i]->SetColor(Color(50, 240, 240));
		cubes2[i]->SetScale(0.5f, -0.5f, 0.5f);
		scene.AddObject(cubes2[i]);

		cubes2[i+1] = new Object3D<float>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces));
		cubes2[i+1]->SetPosition(x, -5, z2);
		cubes2[i+1]->SetColor(Color(50, 100, 240));
		cubes2[i+1]->SetScale(0.5f, -0.5f, 0.5f);
		scene.AddObject(cubes2[i+1]);
	}

	
	bridgeObject.SetColor(Color(100, 100, 255));
}

void Loop()
{
	float zr = 0;
	Matrix3x3<float> camera;

	while (app.Run()) 
	{
					
		scene.SetCameraRotation(0, app.Roll(), 0);
		app.HandleEvents(scene.Camera());
		
		//scene.SetCameraPosition(app.X(), 0, app.Y());
				
		zr += 1.0f;
		
		// The 3 lines below demonstrate how to use the engine, set properties like pos, scale, rotation and after that call scene.RenderObject merthod
		bridgeObject.SetRotation(0, 90, 0); 
		bridgeObject.SetPosition(-70, -6, 50);  
		bridgeObject.SetScale(3, 4, 15);

//		Matrix3x3<float> fo;
//		fo.CreateRotationMatrix(0, 0,0);
		Vector3D<float> pos;

		for (int i = 0; i < 10; i++) {

			pos.Y = 20; 
			pos.X = sin((zr/10 + i * 20) * 1.0f * M_PI / 180) * 12;
			pos.Z = cos((zr/10 + i * 20) * 1.0f * M_PI / 180) * 25;
			pos = pos;  // *fo; // take the cube positions to bridgeObject coordinate system TODO Matrix * Matrix multiplication should be implemented
			pos = bridgeObject.Position() + pos;

			cubes[i]->SetRotation(zr/20, zr/20, zr/20);  // +i * 45, zr + i * 45, zr + i * 45);
			cubes[i]->SetPosition(pos);
			cubes[i]->SetScale(0.5, -0.5, 0.5);
		}

		for (int i = 0; i < 180; i++) {

			cubes2[i]->SetRotation(0,  zr/2 , 0);

		}

		scene.RenderObjects();
		
	}
}

// If you want to understand the whole process the below link is very, very usefull 
// http://www.opengl-tutorial.org/hu/beginners-tutorials/tutorial-3-matrices/


