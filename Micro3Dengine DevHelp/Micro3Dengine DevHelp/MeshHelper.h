#pragma once

#include "../../Micro3Dengine\object3d.h"
#include "../../Micro3Dengine\Matrices.h"
#include "../../Micro3Dengine\Face.h"
#include "../../Micro3Dengine\Scene.h"

#include <vector>
#include "perlin.h"


void CreateOneMeshSquare(Scene<float> & scene, Vector3D<float>& pos, unsigned offsetx, unsigned offsetz, float * terrain)
{
	auto vects = new std::vector<Vector3D<float>>();
	for (int z = 0; z < 11; z++) {
		for (int x = 0; x < 11; x++) {
			float y = terrain[offsetx + x + offsetz*50 + z*50];
			vects->push_back(Vector3D<float>(-50 + x * 10, y, -50 + z * 10));
		}
	}

	auto faces = new std::vector<Face>();
	for (int z = 0; z < 10; z++) {
		for (int x = 0; x < 10; x++) {
			faces->push_back(Face(z * 11 + x, z * 11 + x + 1,
				z * 11 + 11 + x));
			faces->push_back(Face(z * 11 + x + 1,
				z * 11 + 11 + x + 1, z * 11 + 11 + x));
		}
	}

	auto mesh = new Object3D<float>(&vects->at(0), vects->size(), &faces->at(0), faces->size());

	scene.AddObject(mesh);
	mesh->SetColor(Color(255, 255, 50));
	mesh->SetScale(1, 1, 1);
	mesh->SetRotation(0, 0, 0);
	mesh->SetPosition(pos);

}

void CreateMesh(Scene<float> & scene)
{
	Perlin perlin(2, 5, 60, 123);

	float terrain[3000];
	for (unsigned i=0; i < 51; i++) {
		for (unsigned j = 0; j < 51; j++) {
			terrain[i +j *50] = perlin.Get((float)i / 50, (float)j / 50) +10;
		}
	}

	for (unsigned i = 0; i < 30; i++) {
		for (unsigned j = 22; j < 28; j++) {
			terrain[j + i * 50] = 0;
		}
	}

	for (int x = 0; x < 5; x++) {
		for (int z = 0; z < 5; z++) {
			auto v = Vector3D<float>(-200 + x * 100, 0, 50 + z * 100);
			CreateOneMeshSquare(scene, v, x * 10, z * 10, terrain);
		}
	}
}

// For testing
void CrateSimplePlane(Scene<float> & scene) {
	auto vects = new std::vector<Vector3D<float>>();
	unsigned maxZ = 2;
	unsigned maxX = 2;
	for (int z = 0; z < maxZ; z++) {
		for (int x = 0; x < maxX; x++) {
			vects->push_back(Vector3D<float>(-25 + x * 50, -5, -25 + z * 50));
		}
	}

	auto faces = new std::vector<Face>();
	for (int z = 0; z < maxZ - 1; z++) {
		for (int x = 0; x < maxX - 1; x++) {
			faces->push_back(Face(z * maxZ + x, z * maxZ + x + 1,
				z * maxZ + maxZ + x));
			faces->push_back(Face(z * maxZ + x + 1, z * maxZ + maxZ + x + 1,
				z * maxZ + maxZ + x));
		}
	}

	auto mesh = new Object3D<float>(&vects->at(0), vects->size(), &faces->at(0), faces->size());

	scene.AddObject(mesh);
	mesh->SetColor(Color(200, 200, 100));
	mesh->SetScale(1, 1, 1);
	mesh->SetRotation(-30, 0, 0);
	mesh->SetPosition(0, 0, 50);
}

/*
void CreateObjects()
{

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
*/