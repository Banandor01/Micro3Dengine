
#include "Airplane.h"
#include "../../Micro3Dengine/EngineConfig.h"

template class Airplane<NUMBERTYPE>;

template<class numT>
void Airplane<numT>::Roll(numT step) {
	Mat33<numT> rot;
	rot.CreateRotationMatrix(0, 0, step);
	this->rotationMat = this->rotationMat * rot;
	if (vectorToShow.Z > -30 && vectorToShow.Z < 30) {	vectorToShow.Z += step *2; }
}

template<class numT>
void Airplane<numT>::Yaw(numT step) {
	Mat33<numT> rot;
	rot.CreateRotationMatrix(0, step, 0);
	this->rotationMat = this->rotationMat * rot;
	if (vectorToShow.Y > -30 && vectorToShow.Y < 30) { vectorToShow.Y += step * 2; }
}

template<class numT>
void Airplane<numT>::Pitch(numT step) {
	Mat33<numT> rot;
	rot.CreateRotationMatrix(step, 0, 0);
	this->rotationMat = this->rotationMat * rot;
	if (vectorToShow.X > -30 && vectorToShow.X < 30) { vectorToShow.X += step * 2; }
}

template<class numT>
void Airplane<numT>::GoForward(numT step) {
	this->position += Vector3D<numT>(0, 0, step) * this->rotationMat;
}

template<class numT>
void Airplane<numT>::Update()
{
	numT  diff = 0 - vectorToShow.Z;
	vectorToShow.Z += diff / 20;
	diff = 0 - vectorToShow.X;
	vectorToShow.X += diff / 20;
	diff = 0 - vectorToShow.Y;
	vectorToShow.Y += diff / 20;
	
	GoForward(speed);

}

unsigned v = 0;
template<class numT>
void Airplane<numT>::Fire() {
	Bullet<numT> &bullet = bullets[v++%10];
	bullet.SetPosition(this->position + Vector3D<numT>(0,-30,0));

	Vector3D<numT> speed(0, 0, 1.0f + this->speed);
	speed = speed  * this->rotationMat;
	bullet.SetSpeed(speed);
	
	bullet.Rotation() = this->rotationMat;

	Vector3D<numT> vectS(0.8f, 0.8f, 4.0f);
	bullet.SetScale(vectS);
	
	bullet.Visible(true);
}