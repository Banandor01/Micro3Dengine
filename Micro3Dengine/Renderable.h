
#include "EngineConfig.h"

template<class T>
class Vector3D;
template<class T>
class Camera;
template<class T>
class Face3D;
class Face;

#include "Vectors.h"
#include "Matrix.h"
#include "Color.h"

// Base class of all 3D object 
template<class numT>
class Renderable
{
public:
	Renderable();

	void SetRotation(Vector3D<numT> rvect);
	void SetRotation(numT x, numT y, numT z);

	void SetPosition(numT x, numT y, numT z);
	void SetPosition(Vector3D<numT> positionVector);
	
	void SetScale(numT x, numT y, numT z);
	void SetScale(Vector3D<numT> & scaleVector);
	
	void SetColor(Color color) { this->color = color; }
	
	Color& GetColor() { return color; }
	Vector3D<numT>& Position() { return position; }
	Mat33<numT>& Rotation() { return rotationMat; }

	virtual void UpdateModellToWorldMatrix();	// Calculate the modell to world matrix according to the Object's position, scale and rotation

	// virtual methods
	// Apply Rotation, Sacling and translation inorder to move model into world space with set orreintation
	virtual void ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts, unsigned int& num,
							   Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling = ture) = 0;
protected:
	Vector3D<numT> position;
	Vector3D<numT> rotation;
	Vector3D<numT> scale;

	Mat33<numT>    rotationMat;
	Mat44<numT>	   m2w;			// Modell to world matrix
	Color color;
};