#pragma once

#include "Vectors.h"
#include <math.h>

#define M_PI 3.14159


/// <summary>
/// Matrix3D
/// </summary>
/// <typeparam name="numT"></typeparam>
template<class numT>
class Matrix3x3 {
public:
	Matrix3x3() {
		m00 = 1;  m10 = 0; m20 = 0;
		m01 = 0;  m11 = 1; m21 = 0;
		m02 = 0;  m12 = 0; m22 = 1;
	}

	// Create a rotation matrix
	void CreateRotationMatrix(numT x, numT y, numT z) {

		numT x2 = x * M_PI / 180;
		numT y2 = y * M_PI / 180;
		numT z2 = z * M_PI / 180;

		numT cosz = cos(z2);    numT sinz = sin(z2);
		numT siny = sin(y2);    numT cosy = cos(y2);
		numT sinx = sin(x2);    numT cosx = cos(x2);

		m00 = cosy * cosz;  m10 = cosz * sinx * siny - cosx * sinz;     m20 = cosx * cosz * siny + sinx * sinz;
		m01 = cosy * sinz;  m11 = cosx * cosz + sinx * siny * sinz;     m21 = cosx * siny * sinz - cosz * sinx;
		m02 = -siny;        m12 = cosy * sinx;                          m22 = cosx * cosy;
	}

	friend Vector3D<numT> operator*(const Vector3D<numT>& vec, const Matrix3x3& m) 
	{
		numT x = m.m00 * vec.X + m.m10 * vec.Y + m.m20 * vec.Z;
		numT y = m.m01 * vec.X + m.m11 * vec.Y + m.m21 * vec.Z;
		numT z = m.m02 * vec.X + m.m12 * vec.Y + m.m22 * vec.Z;
		return Vector3D<numT> (x, y, z);
	}

	Matrix3x3<numT> operator* (const Matrix3x3& right)
	{
		Matrix3x3<numT> nM;

		nM.m00 = m00 * right.m00 + m10 * right.m01 + m20 * right.m02;	
		nM.m10 = m00 * right.m10 + m10 * right.m11 + m20 * right.m12;
		nM.m20 = m00 * right.m20 + m10 * right.m21 + m20 * right.m22;

		nM.m01 = m01 * right.m00 + m11 * right.m01 + m21 * right.m02;
		nM.m11 = m01 * right.m10 + m11 * right.m11 + m21 * right.m12;
		nM.m21 = m01 * right.m20 + m11 * right.m21 + m21 * right.m22;

		nM.m02 = m02 * right.m00 + m12 * right.m01 + m22 * right.m02;
		nM.m12 = m02 * right.m10 + m12 * right.m11 + m22 * right.m12;
		nM.m22 = m02 * right.m20 + m12 * right.m21 + m22 * right.m22;

		return nM;
	}

private:
	numT m00, m10, m20;
	numT m01, m11, m21;
	numT m02, m12, m22;
};

// 4x4 matrix only needs for projection in this project, that is why it is not a general 4x4Matrix
template<class numT>
class ProjectionMatrix {
public:
	void CreatePerspective(numT fov, numT width, numT height, numT near, numT far) {

		this->height = height;
		this->width = width;
		numT aspect = height / width;
		numT D2R = M_PI / 180.0;
		numT xScale = aspect / tan(D2R * fov / 2);
		numT yScale = 1.0 / tan(D2R * fov / 2);

		numT farmnear = far - near;

		m00 = xScale;       m10 = 0;            m20 = 0;                        m30 = 0,
		m01 = 0;            m11 = yScale;       m21 = 0;                        m31 = 0,
		m02 = 0;            m12 = 0;            m22 = far / farmnear;           m32 = (-far * near) / farmnear;
		m03 = 0;            m13 = 0;            m23 = 1;                        m33 = 0;
	}

	// Project vector to a clipping space and after that apply the z division
	void ProjectVector(Vector3D<numT>& vect) {

		// The projection calculation can be optimized, because a lots of element of the matrix is 0 or 1
		// But in below form is more understable
		const numT vectW = 1;
		numT x = vect.X * m00 + vect.Y * m10 + vect.Z * m20 + vectW * m30;
		numT y = vect.X * m01 + vect.Y * m11 + vect.Z * m21 + vectW * m31;
		numT z = vect.X * m02 + vect.Y * m12 + vect.Z * m22 + vectW * m32;
		numT w = vect.X * m03 + vect.Y * m13 + vect.Z * m23 + vectW * m33;

		if (w != 0) {
			vect.X = x / w;
			vect.Y = y / w;
			vect.Z = z / w;
		}

		//Normalized device coordinate to ViewPort Coordinate
		vect.X = vect.X * width / 2 + width / 2;
		vect.Y = vect.Y * height / 2 + height / 2;
	}

	// It is a simplified version of projection for embedded, no z normalization is applied here 
	void ProjectVectorNoZnormalization(Vector3D<numT>& vect)
	{
		const numT vectW = 1;
		numT x = vect.X * m00;
		numT y = vect.Y * m11;

		if (vect.Z != 0) {
			vect.X = x / vect.Z;
			vect.Y = y / vect.Z;
		}

		//Normalizde device coordinate to ViewPort Coordinate
		vect.X = vect.X * width / 2 + width / 2;
		vect.Y = vect.Y * height / 2 + height / 2;
	}

	void ProjectVectorsNoZnormalization(Vector3D<numT>* vect, unsigned num)
	{
		for (unsigned i = 0; i < num; i++) {
			const numT vectW = 1;
			numT x = vect[i].X * m00;
			numT y = vect[i].Y * m11;

			if (vect[i].Z != 0) {
				vect[i].X = x / vect[i].Z;
				vect[i].Y = y / vect[i].Z;
			}

			//Normalizde device coordinate to ViewPort Coordinate
			vect[i].X = vect[i].X * width / 2 + width / 2;
			vect[i].Y = vect[i].Y * height / 2 + height / 2;
		}
	}

private:
	numT m00, m10, m20, m30;
	numT m01, m11, m21, m31;
	numT m02, m12, m22, m32;
	numT m03, m13, m23, m33;

	numT height, width;
};



