
#include "../../Micro3Dengine/EngineConfig.h"
#include "MeshHelper.h"

template class DynamicMesh<NUMBERTYPE>;
template class SquareMesh<NUMBERTYPE>;

template<class numT>
inline DynamicMesh<numT>::DynamicMesh(Scene<numT>& scene1, Application<numT>& application) :
	meshPointDistance(40),
	perlin(6, 14, 280, 125),
	scene(scene1),
	application(application),
	visibleMeshes(0)
{
	for (unsigned i = 0; i < 40; i++) {
			meshes[i].SetMeshPointDistance(meshPointDistance);
			meshes[i].SetColor(Color(100, 100, 255));
			meshes[i].Visible(false);
			scene.AddObject(&meshes[i]);
	}
	UpdateMesh();
}

template<class numT>
void DynamicMesh<numT>::UpdateMesh() {

	numT meshSize = meshPointDistance * 10;

	int zMeshIndex = round(scene.Camera().Position().Z / meshSize);
	int xMeshIndex = round(scene.Camera().Position().X / meshSize);

	Mat33<numT> rot;
	auto cv = scene.Camera().GetRotationVect();
	rot.CreateRotationMatrix(cv.X, cv.Y, cv.Z);
	Vector3D<numT> dir(0, 0, 1);
	dir = dir * rot;
	// dir = dir * scene.Camera().GetRotationMatrix();

	visibleMeshes = 0;
	for (int x = -3; x <= 3; x++) {
		for (int z = -3; z <= 3; z++) {
			Vector3D<numT> pos((x + xMeshIndex) * meshSize, -80, (z + zMeshIndex) * meshSize);
			auto toMesh = pos - scene.Camera().Position();

			toMesh.Normalize();
			if (visibleMeshes < 40 && ((z > -2 && z < 2 && x>-2 && x < 2) || dir.DotProduct(toMesh) > 0.4)) 
			{
				meshes[visibleMeshes].CreateMesh(perlin, pos, x + xMeshIndex, z + zMeshIndex);
				meshes[visibleMeshes].Visible(true);
				meshes[visibleMeshes].SetPosition(pos);
				visibleMeshes++;
			}
		}
	}
	for (unsigned i = visibleMeshes; i < 40; i++) { meshes[i].Visible(false); }
}

/// <summary>
/// Square mesh represent a square pice of the mesh
/// </summary>
/// <typeparam name="numT"></typeparam>
template<class numT>
inline SquareMesh<numT>::SquareMesh() :
	visible(true) ,
	oldx(10000), oldz(1000)
{
	this->SetColor(Color(255, 155, 150));
	this->SetScale(1, 1, 1);
	this->SetRotation(0, 0, 0);

}

template<class numT>
void SquareMesh<numT>::ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num, Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling) {

	if (!visible) return;

	unsigned offset = num;
	numT xv, yv, zv;
	this->UpdateModellToWorldMatrix();

	for (unsigned i = 0; i < 121; i++)
	{
		xv = verticies[i].X * this->scale.X;
		yv = verticies[i].Y * this->scale.Y;
		zv = verticies[i].Z * this->scale.Z;

		Vector3D<numT> vect(xv, yv, zv);
		vect = vect * this->m2w;

		if (camera != nullptr) {
			vect = vect * camera->GetMatrix();
		}
		rotatedVerts[offset + i] = vect;
	}
	num += 121;

	// Create Faces
	for (unsigned int i = 0; i < 200; i++)
	{
		Face3D<numT> face;
		face.vector1 = &rotatedVerts[faces[i].index1 + offset];
		face.vector2 = &rotatedVerts[faces[i].index2 + offset];
		face.vector3 = &rotatedVerts[faces[i].index3 + offset];

		// if the face is behind the camera we skip that face
		if (face.vector1->Z < 0.2f && face.vector2->Z < 0.2f && face.vector3->Z < 0.2f) { continue; }
		// primitiv clipping TODO make a real plane clipping
		if (face.vector1->Z < 0.2f) { face.vector1->Z = 0.2f; }//face.color = &this->red; }
		if (face.vector2->Z < 0.2f) { face.vector2->Z = 0.2f; }//face.color = &this->red; }
		if (face.vector3->Z < 0.2f) { face.vector3->Z = 0.2f; }//face.color = &this->red; }			

		face.color = &this->color;

		Vector3D<numT> normal = face.CalcualteNormal();
		auto cameraToFace = *(face.vector1);

		if (backfaceCulling) {
			if (normal.DotProduct(cameraToFace) < 0) {
				facesOut[facesNum] = face;
				facesNum++;
			}
		}
		else {
			facesOut[facesNum] = face;
			facesNum++;
		}
	}
}

template<class numT>
void SquareMesh<numT>::CreateMesh(Perlin& perlin, Vector3D<numT>& pos, int offsetx, int offsetz) {
	unsigned index = 0;

	if (oldx != offsetx || oldz != offsetz) 
	{
		oldx = offsetx;
		oldz = offsetz;
		int offset = meshPointDistance * 5;
		for (int z = 0; z < 11; z++) {
			for (int x = 0; x < 11; x++) {
				numT y = perlin.Get((numT)(100 + x + offsetx * 10) / 300.0f, (numT)(100 + z + offsetz * 10) / 300.0f);
				auto t = Vector3D<numT>(-offset + x * meshPointDistance, y, -offset + z * meshPointDistance);
				verticies[index++] = t;
			}
		}
		index = 0;
		for (int z = 0; z < 10; z++) {
			for (int x = 0; x < 10; x++) {
				faces[index++] = Face(z * 11 + x, z * 11 + x + 1, z * 11 + 11 + x);
				faces[index++] = Face(z * 11 + x + 1, z * 11 + 11 + x + 1, z * 11 + 11 + x);
			}
		}
	}
}

template<class numT>
inline void SquareMesh<numT>::SetMeshPointDistance(unsigned distance) {
	meshPointDistance = distance;
}

template<class numT>
inline void SquareMesh<numT>::Visible(bool visible) {
	this->visible = visible;
}



// For testing
/*
void CrateSimplePlane(Scene<float>& scene) {
	auto vects = new std::vector<Vector3D<float>>();
	unsigned maxZ = 2;
	unsigned maxX = 2;
	for (int z = 0; z < maxZ; z++) {
		for (unsigned x = 0; x < maxX; x++) {
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
*/
/*
void CreateRoad()
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
