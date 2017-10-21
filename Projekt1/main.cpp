
#include "Box2D/Box2D.h"

#include <stdio.h>


int main(int argc, char** argv)
{
	//gravity vector;
	b2Vec2 myGravity(10.0f, -20.0 );
	//adding gravity to my world;
	b2World myWorld(myGravity);
	// ground body definition
	b2BodyDef myGroundBodyDef;
	// setting initial position for body
	myGroundBodyDef.position.Set(10.f, -15.0f);

	return 0;
}
