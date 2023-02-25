#pragma once

#include "../../../Micro3Dengine/Micro3Dengine/EngineConfig.h"
#include "../../../Micro3Dengine/Micro3Dengine/object3d.h"
#include "../Micro3Dengine DevHelp/models.h"

#include <stdlib.h>

template<class numT> 
class Bullet : public Object3D<numT>
{
public:
	Bullet() : Object3D<numT>(&Cubevectors[0], _countof(Cubevectors), cubeFaces, _countof(cubeFaces)),
		visible(false)
	{}

	void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
					   Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling) override;
	
	void Visible(bool visible1) { 
		visible = visible1; 
	}
	void SetSpeed(Vector3D<numT> speed) { this->speed = speed; }
private:
	Vector3D<numT> speed;
	bool visible;
};

