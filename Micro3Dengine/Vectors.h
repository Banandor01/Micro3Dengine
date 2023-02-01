#pragma once

/// <summary>
/// Vector2D class represent a 2D vector
/// </summary>
/// <typeparam name="numT">type of the number</typeparam>
template<class numT>
class Vector2D
{
public:
	// Constructors
	Vector2D () : X(0), Y(0)	{}

	Vector2D (numT x, numT y) : X(x), Y(y) {}

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

	// Set the length of the vector to one
	void Normalize();
	
	// Length of the vector
	numT Length();
	
	// Squared length of the vector (for optimalization)
	numT SquaredLength();

	// Dot product of the two vectors
	static numT DotProduct(const Vector2D<numT>& left, const Vector2D<numT>& right);

public:
	// They shold be private but for performance reson we don't want to use accessor methods
	numT X;
	numT Y;
};

/// <summary>
/// Vector3D class represents a 3D vector
/// </summary>
/// <typeparam name="numT"></typeparam>
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

	// Set the length of the vector to one
	void Normalize();

	// Length of the vector
	numT Length();

	// Squared length of the vector (for optimalization)
	numT SquaredLength();

	// Cross product of the two vectors
	Vector3D CrossProduct(const Vector3D<numT>& right);

	// DotProduct
	numT DotProduct(const Vector3D<numT>& right);

public:
	// It would be better if the above members were private, but for performance reson we use public
	numT X;
	numT Y;
	numT Z;
};

