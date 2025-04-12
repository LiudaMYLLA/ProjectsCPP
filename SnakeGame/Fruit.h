
#pragma once

#include "Drawable.h"
#include "GameObjectBehavior.h"

//forward declarations
class Scene;
class Snake;


class Fruit : public Drawable, public GameObjectBehavior
{
private:
	int fruitX, fruitY;
	Scene& scene;
	Snake& snake;
	
public:

	Fruit(Scene& scene, Snake& snake);

	//polimorphism functions
	void draw() const override;
	void update() override;

	
	int getFruitX() const;
	int getFruitY() const;

};

