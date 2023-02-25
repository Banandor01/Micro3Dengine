#pragma once

#include "../../Micro3Dengine/object3d.h"
#include "../../Micro3Dengine/interfaces/MovableBase.h"
#include "../../Micro3Dengine/Scene.h"

#include "Bullet.h"

template<class numT>
class Airplane : public MovableBase<numT> {
public:
	
	Airplane(Scene<numT>& scene1) 
		: scene(scene1),
		  bulletsNumber(10),
		  speed(0)
	{
		for (unsigned i = 0; i < 10; i++) {
			scene.AddObject(&bullets[i]);
		}
	}

	void Roll(numT step) override;
	void Yaw(numT step) override;
	void Pitch(numT step) override;
	void GoForward(numT step) override;
	void Update() override;

	void SpeedUp() { if (speed < 2.2f) speed += 0.02; }
	void SpeedDown() { if (speed > 0.2f) speed -= 0.02;	}

	void Fire();

	Vector3D<numT>& VectorToShow() { return vectorToShow; }
private:
	Vector3D<numT> vectorToShow;
	Scene<numT>& scene;

	Bullet<numT> bullets[10];
	unsigned bulletsNumber;
	float speed;
};