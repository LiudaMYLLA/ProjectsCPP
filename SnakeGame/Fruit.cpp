
#include "Fruit.h"
#include "Scene.h"
#include "Snake.h"

#include <cstdlib>
#include <iostream>

Fruit::Fruit(Scene &scene, Snake &snake) : scene(scene), snake(snake){
	do {
		fruitX = std::rand() % scene.getWidth();
		fruitY = std::rand() % scene.getHeight();

	} while (snake.x == fruitX && snake.y == fruitY);
}

void Fruit::draw() const{
	system("cls");
	for (int i = 0; i < scene.getHeight(); ++i) {
		for (int j = 0; j < scene.getWidth(); ++j) {

			if (i == fruitY && j == fruitX) {
				std::cout << "F"; 
			}
			else {
				std::cout << " "; 
			}
		}
		std::cout << std::endl; 
	 }
}

void Fruit::update(){
	if (snake.x == fruitX && snake.y == fruitY) {
		do {
			fruitX = rand() % scene.getWidth();
			fruitY = rand() % scene.getHeight();

		} while (snake.x == fruitX && snake.y == fruitY);
	}
}

int Fruit::getFruitX() const{
	return fruitX;
}

int Fruit::getFruitY() const{
	return fruitY;
}