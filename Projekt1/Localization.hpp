#include "Box2D/Box2D.h"


#ifndef Localization_hpp
#define Localization_hpp

struct coOrdinates
{
	float32 x;
	float32 y;
	float32 width;
	float32 height;

};
coOrdinates dynamicRectCoordinates, groundRectCoordinates;

float32 localizeCentreX(float32);
float32 localizeCentreY(float32);

float32 centreX, centreY;
#endif
