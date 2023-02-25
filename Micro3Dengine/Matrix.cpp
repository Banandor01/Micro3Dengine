
#include "EngineConfig.h"
#include "Matrix.h"

template class Mat33<NUMBERTYPE>;
template class Mat44<NUMBERTYPE>;

template<class numT>
 Mat33<numT>::Mat33() {
	m00 = 1;  m10 = 0; m20 = 0;
	m01 = 0;  m11 = 1; m21 = 0;
	m02 = 0;  m12 = 0; m22 = 1;
}

template<class numT>
void Mat33<numT>::CreateRotationMatrix(numT x, numT y, numT z) {

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

template<class numT>
Vector3D<numT> Mat33<numT>::ToEulerAngles()
{
	numT sy = sqrt(m00 * m00 + m01 * m01);
	bool singular = sy < 1e-6; // If

	numT x, y, z;
	if (!singular)
	{
		x = atan2(m12, m22);
		y = atan2(-m02, sy);
		z = atan2(m01, m00);
	}
	else
	{
		x = atan2(-m21, m11);
		y = atan2(-m02, sy);
		z = 0;
	}

	x = x / 3.14159 * 180;
	y = y / 3.14159 * 180;
	z = z / 3.14159 * 180;

	return Vector3D<numT>(x, y, z);
}

template<class numT>
Mat33<numT> Mat33<numT>::operator* (const Mat33 & right)
{
	Mat33<numT> nM;

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


template<class numT>
void Mat44<numT>::SetRotation(numT x, numT y, numT z) {

	numT x2 = x * M_PI / 180;
	numT y2 = y * M_PI / 180;
	numT z2 = z * M_PI / 180;

	numT cosz = cos(z2);    numT sinz = sin(z2);
	numT siny = sin(y2);    numT cosy = cos(y2);
	numT sinx = sin(x2);    numT cosx = cos(x2);

	el[0] = cosy * cosz;  el[1] = cosz * sinx * siny - cosx * sinz;     el[2] = cosx * cosz * siny + sinx * sinz; el[3] = 0;
	el[4] = cosy * sinz;  el[5] = cosx * cosz + sinx * siny * sinz;     el[6] = cosx * siny * sinz - cosz * sinx; el[7] = 0;
	el[8] = -siny;        el[9] = cosy * sinx;                          el[10] = cosx * cosy;					  el[11] = 0;
	el[12] = 0;			  el[13] = 0;									el[14] = 0;								  el[15] = 0;
}
