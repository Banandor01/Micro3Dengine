// Micro3Dengine DevHelp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>

#include "models.h"
#include "VirtualTFT.h"

#include "../../Micro3Dengine\object3d.h"
#include "../../Micro3Dengine\Matrices.h"
#include "../../Micro3Dengine\Face.h"
#include "../../Micro3Dengine\Scene.h"

void Init();
void Loop();

int main(int argc, char* argvp[])
{
	Init();
	Loop();

	std::getchar();
}


// ******************************************************************************************************************
// Embedded device memory allocations and functions  


VirtualTFT tft(320, 240);
Scene<float> scene(320, 240);

// Declare the 3D object(s) we want to render
// Micro3Dengine is for Micro Controllers so in this example we are not using any dynamic memory allocation 
Object3D<float> bridgeObject(&bridgeVectors[0], _countof(bridgeVectors), bridgeFaces, _countof(bridgeFaces));
Object3D<float>* cubes[20];

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
	bridgeObject.SetColor(Color(100, 100, 255));
}

void Loop()
{
	float zr = 0;
	while (true) {

		zr += 0.6f;
		
		// The 3 lines below demonstrate how to use the engine, set properties like pos, scale, rotation and after that call scene.RenderObject merthod
		bridgeObject.SetRotation(zr/3, zr, zr / 2);
		bridgeObject.SetPosition(sin(zr * M_PI / 180) * 25, cos(zr * 1.5f * M_PI / 180) * 10, 50 + cos(zr * M_PI / 180) * 20);
		bridgeObject.SetScale(3, 3, 3);

		// The above lines are made just for demo or fun... The linear algebra is cool

		Matrix3x3<float> fo;
		fo.CreateRotationMatrix(zr, zr, zr / 2);
		Vector3D<float> pos;

		for (int i = 0; i < 10; i++) {

			pos.X = 0; 
			pos.Y = sin((zr*2 + i * 20) * 1.0f * M_PI / 180) * 12;
			pos.Z = cos((zr * 2 + i * 20) * 1.0f * M_PI / 180) * 25;
			pos = pos * fo; // take the cube positions to bridgeObject coordinate system TODO Matrix * Matrix multiplication should be implemented
			pos = bridgeObject.Position() + pos;

			cubes[i]->SetRotation(zr + i * 45, zr + i *45, zr + i *45);
			cubes[i]->SetPosition(pos);
			cubes[i]->SetScale(0.5, -0.5, 0.5);
		}

		scene.RenderObjects();

		SDL_Delay(5);
	}
}

// If you want to understand the whole process the below link is very, very usefull 
// http://www.opengl-tutorial.org/hu/beginners-tutorials/tutorial-3-matrices/


