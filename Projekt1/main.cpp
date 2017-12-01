
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>


int main(int argc, char** argv)
{
	struct coOrdinates
	{
		float32 x = 0;
		float32 y = 0;
		float32 width = 0;
		float32 height = 0;

	};
	/////////////Graphics

	coOrdinates dynamicRectCoordinates =
	{
		0,
		0,
		100,
		100,
	};
	coOrdinates groundRectCoordinates =
	{
		0,
		300,
		100,
		100,
	};
	float32 dynamicRectPositionX = 0;
	float32 dynamicRectPositionY = 0;
	float32 groundRectPositionX = 0;
	float32 groundRectPositionY = 300;
	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
	sf::RectangleShape dynamicRect(sf::Vector2f(dynamicRectCoordinates.width, dynamicRectCoordinates.height));
	dynamicRect.setFillColor(sf::Color::Green);
	dynamicRect.setPosition(dynamicRectCoordinates.x, dynamicRectCoordinates.y);

	sf::RectangleShape groundRect(sf::Vector2f(groundRectCoordinates.width, groundRectCoordinates.height));
	groundRect.setFillColor(sf::Color::Red);
	groundRect.setPosition(groundRectCoordinates.x, groundRectCoordinates.y);
	//int iterator(0);
	//int temp;
	
	//b2Vec2 myForce(1.0f, 0.0f);


	//gravity vector;
	b2Vec2 myGravity(0.0f, 0.5f);
	//adding gravity to my world;
	b2World myWorld(myGravity);

	//changing angle
	//b2Vec2 myAngle(50.0f, 50.0f);

	//creating a static body (they are static by default)

	// ground body definition
	b2BodyDef myGroundBodyDef;
	// setting initial position for body
	myGroundBodyDef.position.Set(groundRectCoordinates.x, groundRectCoordinates.y);
	// passed definition to the world
	b2Body* myGroundBody = myWorld.CreateBody(&myGroundBodyDef);
	//creating a ground polygon
	b2PolygonShape myGroundBox;
	//setting width (2x50) and height (2x50)
	myGroundBox.SetAsBox(groundRectCoordinates.width/2, groundRectCoordinates.height/2);
	//creating fixture with a shortcut 'cause we do not need any specific properties (density, mass, ect.)  to this body
	myGroundBody->CreateFixture(&myGroundBox, 0.0f);

	//creating a dynamic body

	//same as above
	b2BodyDef myDynamicBodyDef;
	myDynamicBodyDef.type = b2_dynamicBody;
	myDynamicBodyDef.position.Set(dynamicRectPositionX, dynamicRectPositionY);
	b2Body* myDynamicBody = myWorld.CreateBody(&myDynamicBodyDef);

	//creating the box shape
	b2PolygonShape myDynamicBox;
	myDynamicBox.SetAsBox(dynamicRectCoordinates.width/2, dynamicRectCoordinates.height/2);
	//creating fixture definition using the box
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &myDynamicBox;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 90.0f;

	//creating fixture
	myDynamicBody->CreateFixture(&myFixtureDef);

	//creating a simulation

	//creating timestep
	float32 timeStep = 1.0f / 60.0f;

	//solving constraints iterations
	int32 myVelocityIterations = 6;
	int32 myPositonIterations = 2;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//game loop
		//for (int32 i = 0; i < 59; ++i)
		while (sf::Keyboard::isKeyPressed)
		{
		
			myWorld.Step(timeStep, myVelocityIterations, myPositonIterations);
			b2Vec2 myPosition = myDynamicBody->GetPosition();
			float32 myAngle = myDynamicBody->GetAngle();
			printf("%4.2f %4.2f %4.2f\n", myPosition.x, myPosition.y, myAngle);


			//Graphics

			dynamicRect.setPosition(myPosition.x, myPosition.y);
			//iterator++;
			//displaying
			window.clear();
			window.draw(dynamicRect);
			window.draw(groundRect);
			window.display();
		}

		window.clear();
		window.draw(dynamicRect);
		window.draw(groundRect);
		window.display();
	}
	printf("----------------------------------------------------\n");
	//shapes

	//circle
//	b2BodyDef circleBodyDef;
//	circleBodyDef.position.Set(0.0f, -9.0f);
//	circleBodyDef.type = b2_dynamicBody;
//	b2Body* dynamicCircle = myWorld.CreateBody(&circleBodyDef);
//	
//	b2CircleShape myCircle;
//	myCircle.m_p.Set(10.0f, 3.0f);
//	myCircle.m_radius = 1.0f;
//
//
//	b2FixtureDef circleFixtureDef;
//	circleFixtureDef.shape = &myCircle;
//	circleFixtureDef.density = 3.0f;
//	circleFixtureDef.friction = 0.6f;
//
//	dynamicCircle->CreateFixture(&circleFixtureDef);
//
//	for (int k = 0; k < 59; k++)
//	{
//		myWorld.Step(timeStep, myVelocityIterations, myPositonIterations);
//		b2Vec2 circlePosition = dynamicCircle->GetPosition();
//		float32 circleAngle = dynamicCircle->GetAngle();
//		printf("%4.2f %4.2f %4.2f\n", circlePosition.x, circlePosition.y, circleAngle);
//	}

	
	getchar();

	return 0;
}
