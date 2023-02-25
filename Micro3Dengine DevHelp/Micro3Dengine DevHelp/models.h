#ifdef ONPC
#define PROGMEM
#endif

#include "..\..\Micro3Dengine\Face.h";

extern const Vector3D<float> Cubevectors[8];
extern const Face cubeFaces[12];

extern const Vector3D<float> bridgeVectors[119];
extern const Face bridgeFaces[254];


/*
* it was used in texturing test project
const uint8_t UV[16][2] = PROGMEM{
	{ 0  ,0 } ,
	{ 79 ,0 } ,    // V1
	{ 79 ,79} ,
	{ 0, 79 } ,    // V3

	{ 0 , 0 } ,
	{ 79, 0 } ,
	{ 79,79 } ,
	{ 0, 79 },

	{ 0 , 79 } ,  // V8
	{ 79, 79 } ,
	{ 79, 0 } ,
	{ 0, 0 },

	{ 0 , 19 } ,  // V12
	{ 19, 19 } ,
	{ 19, 0 } ,
	{ 0, 0 }
};

*/



