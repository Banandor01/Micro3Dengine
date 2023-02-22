#pragma once

/// <summary>
/// Vector3D class represents a 3D vector
/// </summary>
template<class numT>
class Vector3D
{
public:
	// Constructors
	Vector3D() : X(0), Y(0), Z(0) {}
	Vector3D(numT x, numT y, numT z) : X(x), Y(y), Z(z) {}

	// Operators
	Vector3D operator+(const Vector3D& right) const;
	Vector3D operator-(const Vector3D& right) const;

	Vector3D operator*(const Vector3D& right) const;
	Vector3D operator/(const Vector3D& right) const;

	Vector3D operator*(numT right) const;
	Vector3D operator/(numT right) const;

	Vector3D& operator+=(const Vector3D& right);
	Vector3D& operator-=(const Vector3D& right);
	Vector3D& operator*=(const Vector3D& right);
	Vector3D& operator/=(const Vector3D& right);
	
	Vector3D<numT> Normalize();	// Set the length of the vector to one
	numT Length();				// Length of the vector
	numT SquaredLength();		// Squared length of the vector (for optimalization)
	Vector3D CrossProduct(const Vector3D<numT>& right);	// Cross product of the two vectors
	numT DotProduct(const Vector3D<numT>& right);	// DotProduct

public:
	// It would be better if the above members were private, but for performance reson we use public
	numT X;
	numT Y;
	numT Z;
};


/// <summary>
/// Vector2D class represent a 2D vector
/// </summary>
template<class numT>
class Vector2D
{
public:
	// Constructors
	Vector2D() : X(0), Y(0) {}

	Vector2D(numT x, numT y) : X(x), Y(y) {}

	// Operators
	Vector2D operator+(const Vector2D& right) const;
	Vector2D operator-(const Vector2D& right) const;

	Vector2D operator*(const Vector2D& right) const;
	Vector2D operator/(const Vector2D& right) const;

	Vector2D operator*(numT right) const;
	Vector2D operator/(numT right) const;

	Vector2D& operator+=(const Vector2D& right);
	Vector2D& operator-=(const Vector2D& right);
	Vector2D& operator*=(const Vector2D& right);
	Vector2D& operator/=(const Vector2D& right);

	void Normalize();		// Set the length of the vector to one
	numT Length();			// Length of the vector
	numT SquaredLength();	// Squared length of the vector (for optimalization)
	static numT DotProduct(const Vector2D<numT>& left, const Vector2D<numT>& right);	// Dot product of the two vectors

public:
	// They shold be private but for performance reson we don't want to use accessor methods
	numT X;
	numT Y;
};