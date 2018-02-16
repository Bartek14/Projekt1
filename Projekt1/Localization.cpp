#include "Localization.hpp"
#include "Box2D/Box2D.h"

float32 LocalizeCentreX(float32 x, float32 width)
{
	return dynamicRectCoordinates.x + dynamicRectCoordinates.width / 2;
}
