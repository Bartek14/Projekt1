
#include "Box2D/Box2D.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>

#include "Localization.hpp"


int main(int argc, char** argv)
{

	/////////////Graphic
	dynamicRectCoordinates =
	{
		19,
		0,
		10,
		10,
	};

	groundRectCoordinates =
	{
		50,
		100,
		50,
		60,
	};

	sf::RenderWindow window(sf::VideoMode(400, 400), "SFML works!");
	sf::RectangleShape dynamicRect(sf::Vector2f((float)dynamicRectCoordinates.width, (float)dynamicRectCoordinates.height));
	dynamicRect.setFillColor(sf::Color::Green);
	dynamicRect.setPosition(dynamicRectCoordinates.x - dynamicRectCoordinates.width/2, dynamicRectCoordinates.y- dynamicRectCoordinates.height/2);

	sf::RectangleShape groundRect(sf::Vector2f(groundRectCoordinates.width, groundRectCoordinates.height));
	groundRect.setFillColor(sf::Color::Red);
	groundRect.setPosition(groundRectCoordinates.x - groundRectCoordinates.width / 2, groundRectCoordinates.y - groundRectCoordinates.height / 2);

	
	b2Vec2 rightForce(2.0f, 0.0f);
	b2Vec2 leftForce(-2.0f, 0.0f);
	b2Vec2 upForce(0.0f, -2.0f);
	b2Vec2 downForce(0.0f, 2.0f);
	b2Vec2 stopForce(0.0f, 0.0f);

	centreX = dynamicRectCoordinates.width/2;
	centreY = dynamicRectCoordinates.height/2;
	b2Vec2 centre(centreX, centreY );
	float32 angle1 = 0.0f;

	//gravity vector;
	b2Vec2 myGravity(0.0f, 0.5f);
	//adding gravity to my world;
	b2World myWorld(myGravity);
	
	//creating a static body (they are static by default)

	// ground body definition
	b2BodyDef myGroundBodyDef;
	// setting initial position for body
	myGroundBodyDef.position.Set(groundRectCoordinates.x, groundRectCoordinates.y);
	// passed definition to the world
	b2Body* myGroundBody = myWorld.CreateBody(&myGroundBodyDef);
	//creating a ground polygon
	b2PolygonShape myGroundBox;
	//setting width and height 
	myGroundBox.SetAsBox(groundRectCoordinates.width/2, groundRectCoordinates.height/2);
	//creating fixture with a shortcut 'cause we do not need any specific properties (density, mass, ect.)  to this body
	myGroundBody->CreateFixture(&myGroundBox, 0.0f);

	//creating dynamic body definition
	b2BodyDef dynamicBodyDef;
	
	dynamicBodyDef.type = b2_dynamicBody;
	dynamicBodyDef.position.Set(dynamicRectCoordinates.x, dynamicRectCoordinates.y);
	b2Body* myDynamicBody =myWorld.CreateBody(&dynamicBodyDef);

	//creating a dynamic body in vertices

	b2Vec2 vertices[3];
	vertices[0].Set(0.0f, 0.0f);
	vertices[1].Set(0.0f, 1.0f);
	vertices[2].Set(0.5f, 1.5f);
	

	int32 count = 3;

	//creating the box shape
	b2PolygonShape DynamicBody;
	DynamicBody.Set(vertices, count);
	DynamicBody.SetAsBox((dynamicRectCoordinates.width) / 2, (dynamicRectCoordinates.height) / 2, centre, angle1);

	//same as above
	//b2BodyDef myDynamicBodyDef;
	//myDynamicBodyDef.type = b2_dynamicBody;
	//myDynamicBodyDef.position.Set(dynamicRectCoordinates.x, dynamicRectCoordinates.y);
	//b2Body* myDynamicBody = myWorld.CreateBody(&myDynamicBodyDef);


	

	//creating fixture definition using the box
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &DynamicBody;
	myFixtureDef.density = 1.0f;
	myFixtureDef.friction = 0.3f;

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

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				myDynamicBody->SetLinearVelocity(rightForce);
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				myDynamicBody->SetLinearVelocity(leftForce);
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				for(int i=0; i<4; ++i)
				myDynamicBody->SetLinearVelocity(upForce);
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				myDynamicBody->SetLinearVelocity(downForce);

			


			//Graphics

			dynamicRect.setPosition(myPosition.x, myPosition.y);
			dynamicRect.setRotation(myAngle*(180.0f/3.14f));
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
float32 LocalizeCentreX(float32 width)
{
	return width / 2;
}

float32 LocalizeCentreY(float32 height)
{
	return height / 2;
}
