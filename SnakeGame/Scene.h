#pragma once

#include <iostream>
#include "Drawable.h"

// Forward declarations to avoid circular dependencies
class Snake;
class Fruit;


class Scene : public Drawable
{
private:
	const int height = 20;
	const int width = 60;
	int score;
	
	Snake& snake;
	Fruit& fruit;

	friend class Snake;

public: 
	// Constructor initializes the scene with references to Snake and Fruit
	Scene(Snake& sn, Fruit& f);

	// Polymorphic function (from Drawable) responsible for drawing
	void draw() const override;

	int getHeight() const;
	int getWidth() const;

	void updateScore(int value);
};

