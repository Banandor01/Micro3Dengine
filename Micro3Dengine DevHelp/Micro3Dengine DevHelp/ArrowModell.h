#pragma once

#include "..\..\Micro3Dengine\Face.h";

const Vector3D<float> Cubevectors2[14] =
{
	{ 0.0f,  0.0f, +3.0f },
	{ +1.0f, 0.0f, +1.0f },
	{ -1.0f, 0.0f, +1.0f },

	{ -0.3f,  0.0f, +1.0f },
	{  0.3f,  0.0f, +1.0f },

	{ -0.3f,  0.0f, -1.0f },
	{  0.3f,  0.0f, -1.0f },

	{ 0.0f,  -1.0f, +3.0f },
	{ +1.0f, -1.0f, +1.0f },
	{ -1.0f, -1.0f, +1.0f },

	{ -0.3f,  -1.0f, +1.0f },
	{  0.3f,  -1.0f, +1.0f },

	{ -0.3f,  -1.0f, -1.0f },
	{  0.3f,  -1.0f, -1.0f },

};


// create the indices using an int array
const Face cubeFaces2[6] =
{
	{0, 2, 1},
	{3, 5, 4},
	{4, 5, 6},

	{7, 8, 9},
	{10, 11, 12},
	{11, 13, 12},
};
