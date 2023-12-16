// CGT215Lab07_Winter_Geo.cpp
// Geo Winter

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(200, 300));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Create the ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	// Create the left wall
	PhysicsRectangle l_wall;
	l_wall.setSize(Vector2f(20, 600));
	l_wall.setCenter(Vector2f(10, 300));
	l_wall.setStatic(true);
	world.AddPhysicsBody(l_wall);

	// Create the right wall
	PhysicsRectangle r_wall;
	r_wall.setSize(Vector2f(20, 600));
	r_wall.setCenter(Vector2f(790, 300));
	r_wall.setStatic(true);
	world.AddPhysicsBody(r_wall);

	// Create the center square
	PhysicsRectangle c_square;
	c_square.setSize(Vector2f(80, 80));
	c_square.setCenter(Vector2f(400, 300));
	c_square.setStatic(true);
	world.AddPhysicsBody(c_square);

	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};
	l_wall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};
	r_wall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
	};

	//square collision
	int bang_count(0);
	c_square.onCollision = [&bang_count](PhysicsBodyCollisionResult result) {
		cout << "bang " << bang_count + 1 << endl;
		bang_count++;
	};

	Clock clock;
	Time lastTime(clock.getElapsedTime());

	while (bang_count < 3) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
			ball.applyImpulse(Vector2f(0.0001, 0));
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(l_wall);
		window.draw(r_wall);
		window.draw(c_square);
		window.display();
	}

	exit(0);
}