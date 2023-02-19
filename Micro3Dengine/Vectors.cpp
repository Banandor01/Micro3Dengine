#include "EngineConfig.h"

#include "Vectors.h"
#include <math.h>

template class Vector3D<NUMBERTYPE>;

template<class numT>
Vector2D<numT> Vector2D<numT>::operator+(const Vector2D<numT>& right) const
{
	return Vector2D(X + right.X, Y + right.Y);
}

template<class numT>
Vector2D<numT> Vector2D<numT>::operator- (const Vector2D<numT>& right) const 
{
	return Vector2D(X - right.X, Y - right.Y);
}

template<class numT>
Vector2D<numT> Vector2D<numT>::operator*(const Vector2D<numT>& right) const
{
	return Vector2D(X * right.x, Y * right.Y);
}

template<class numT>
Vector2D<numT> Vector2D<numT>::operator/(const Vector2D& right) const
{
	return Vector2D(X / right.x, Y / right.Y);
}

template<class numT>
Vector2D<numT> Vector2D<numT>::operator*(numT right) const
{
	return Vector2D(X * right, Y * right);
}

template<class numT>
Vector2D<numT> Vector2D<numT>::operator/(numT right) const
{
	return Vector2D(X / right, Y / right);
}

template<class numT>
Vector2D<numT>& Vector2D<numT>::operator+=(const Vector2D<numT>& right)
{
	X += right.X;
	Y += right.Y;
	return *this;
}

template<class numT>
Vector2D<numT>& Vector2D<numT>::operator-=(const Vector2D<numT>& right)
{
	X -= right.X;
	Y -= right.Y;
	return *this;
}

template<class numT>
Vector2D<numT>& Vector2D<numT>::operator*=(const Vector2D<numT>& right)
{
	X *= right.X;
	Y *= right.Y;
	return *this;
}

template<class numT>
Vector2D<numT>& Vector2D<numT>::operator/=(const Vector2D<numT>& right)
{
	X /= right.X;
	Y /= right.Y;
	return *this;
}

template<class numT>
inline void Vector2D<numT>::Normalize() {
	if (X != 0 || Y != 0) {
		numT lenght = sqrt(pow(X, 2) + pow(Y, 2));
		X /= lenght;
		Y /= lenght;
	}
	else {
		// if X and Y are zero we are good to do nothing
	}
}

template<class numT>
numT Vector2D<numT>::Length()
{
	return sqrt(pow(X, 2) + pow(Y, 2));
}

template<class numT>
numT Vector2D<numT>::SquaredLength()
{
	return pow(X, 2) + pow(Y, 2);
}
template<class numT>
numT Vector2D<numT>::DotProduct(const Vector2D<numT>& left, const Vector2D<numT>& right) {
	return left.X * right.X + left.Y * right.Y;
}


/// <summary>
/// Vectro3D implementation
/// </summary>
/// <typeparam name="numT"></typeparam>
/// <param name="right"></param>
/// <returns></returns>
template<class numT>
Vector3D<numT> Vector3D<numT>::operator+(const Vector3D& right) const
{
	return Vector3D(X + right.X, Y + right.Y, Z + right.Z);
}

template<class numT>
Vector3D<numT> Vector3D<numT>::operator-(const Vector3D& right) const
{
	return Vector3D(X - right.X, Y - right.Y, Z - right.Z);
}

template<class numT>
Vector3D<numT> Vector3D<numT>::operator*(const Vector3D& right) const
{
	return Vector3D(X * right.X, Y * right.Y, Z * right.Z);
}

template<class numT>
Vector3D<numT> Vector3D<numT>::operator/(const Vector3D& right) const
{
	return Vector3D(X / right.X, Y / right.Y, Z / right.Z);
}

template<class numT>
Vector3D<numT> Vector3D<numT>::operator*(numT right) const
{
	return Vector3D(X * right, Y * right, Z * right);
}

template<class numT>
Vector3D<numT> Vector3D<numT>::operator/(numT right) const
{
	return Vector3D(X / right, Y / right, Z / right);
}

template<class numT>
Vector3D<numT>& Vector3D<numT>::operator+=(const Vector3D<numT>& right)
{
	X += right.X;
	Y += right.Y;
	Z += right.Z;
	return *this;
}

template<class numT>
Vector3D<numT>& Vector3D<numT>::operator-=(const Vector3D<numT>& right)
{
	X -= right.X;
	Y -= right.Y;
	Z -= right.Z;
	return *this;
}

template<class numT>
Vector3D<numT>& Vector3D<numT>::operator/=(const Vector3D<numT>& right)
{
	X /= right.X;
	Y /= right.Y;
	Z /= right.Z;
	return *this;
}

template<class numT>
Vector3D<numT>& Vector3D<numT>::operator*=(const Vector3D<numT>& right)
{
	X *= right.X;
	Y *= right.Y;
	Z *= right.Z;
	return *this;
}


template<class numT>
 Vector3D<numT> Vector3D<numT>::Normalize() {
	numT lenght = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z,2));
	if (lenght != 0) {
		X /= lenght;		
		Y /= lenght;
		Z /= lenght;
	}
	else {
		Y = Z = 0; // What should we do zero length vector
		X = 1;
	}
	return *this;
}

template<class numT>
numT Vector3D<numT>::Length()
{
	return sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));
}

template<class numT>
numT Vector3D<numT>::SquaredLength()
{
	return pow(X, 2) + pow(Y, 2) * pow(Z, 2);
}
template<class numT>
Vector3D<numT> Vector3D<numT>::CrossProduct(const Vector3D<numT>& right) 
{
	Vector3D dot;
	dot.X = Y * right.Z - Z * right.Y;
	dot.Y = Z * right.X - X * right.Z;
	dot.Z = X * right.Y - Y * right.X;
	return dot;
}

template<class numT>
numT Vector3D<numT>::DotProduct(const Vector3D<numT>& right) {

	return X * right.X + Y * right.Y + Z * right.Z;
}
