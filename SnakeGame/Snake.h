#pragma once

#include <conio.h>

#include "Drawable.h"
#include "GameObjectBehavior.h"
#include "Direction.h"

//forward declarations
class Scene;
class Fruit;

// Class representing the Snake object in the game
class Snake : public Drawable, public GameObjectBehavior
{
private:
	int tailX[100] = { 0 };
	int tailY[100] = { 0 };
	int nTail;
	int x;
	int y;
	bool gameOver = false;

	Direction currentDirection = Direction::STOP;

	friend class Scene;
	friend class Fruit;

	Scene &scene;
	Fruit &fruit;

public:

	// Constructor to initialize snake position and game references
	Snake(Scene& scene, Fruit& fruit);

	//polimorphism functions
	void draw() const override;		// Renders the snake on the console
	void update() override;			// Updates snake logic each frame
	
	// Function to handle player input
	void Move();

};

