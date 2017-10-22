
#include "Box2D/Box2D.h"

#include <stdio.h>


int main(int argc, char** argv)
{
	//gravity vector;
	b2Vec2 myGravity(10.0f, -20.0f );
	//adding gravity to my world;
	b2World myWorld(myGravity);

	//creating a body

	// ground body definition
	b2BodyDef myGroundBodyDef;
	// setting initial position for body
	myGroundBodyDef.position.Set(10.f, -15.0f);
	// passed definition to the world
	b2Body* myGroundBody = myWorld.CreateBody(&myGroundBodyDef);
	//creating a ground polygon
	b2PolygonShape myGroundBox;
	//setting width (2x30) and height (2x20)
	myGroundBox.SetAsBox(30.0f, 20.0f);
	//creating fixture with a shortcut 'cause we do not need any specific properties (density, mass, ect.)  to this body
	myGroundBody->CreateFixture(&myGroundBox, 0.0f);

	return 0;
}
