#include "Snake.h"
#include "Scene.h"
#include "Fruit.h"

#include <iostream>
#include <cstdlib>

Snake::Snake(Scene &scene, Fruit &fruit)
	: scene(scene), fruit(fruit) {

	// Start snake position at the center of the scene
	x = scene.width / 2;
	y = scene.height / 2;

	//Initialy, snake has no tail
	nTail = 0;

}

void Snake::draw() const {

	// Clear screen (simple method; can cause flickering)
	system("cls");

	for (int i = 0; i < scene.height; ++i) {
		for (int j = 0; j < scene.width; j++) {

			if (i == y && j == x) {
				std::cout << "O";
			}
			else {
				bool printedTail = false;

				// Check if current position matches any tail segment
				for (int k = 0; k < nTail; ++k) {
					if (i == tailY[k] && j == tailX[k]) {
						std::cout << "o";
						printedTail = true;
						break;
					}
				}
				if (!printedTail){
					std::cout << " "; 
				}
			}
		}

		// If nothing is printed yet, print an empty space
		std::cout << std::endl;
	}
}


void Snake::update() {

	//Tail logic
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;

	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];

		tailX[i] = prevX;
		tailY[i] = prevY;

		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (currentDirection) {
	case Direction::UP:
		y--;
		break;
	case Direction::DOWN:
		y++;
		break;
	case Direction::LEFT:
		x--;
		break;
	case Direction::RIGHT:
		x++;
		break;
	default:
		break;
	}

	if (x < 0 || x > scene.width || y < 0 || y > scene.height) {
		gameOver = true; //this because l deleted acces header file snake to main.cpp
	}

	for (int i = 0; i < nTail; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			gameOver = true; //this because l deleted acces header file snake to main.cpp
		}
	}

	if (x == fruit.getFruitX() && y == fruit.getFruitY()) {
		nTail++;
	}
}

void Snake::Move() {
	if (_kbhit()) {
		char key = _getch();
		switch (key) {
		case 'w': currentDirection = Direction::UP; break;
		case 'a': currentDirection = Direction::LEFT; break;
		case 's': currentDirection = Direction::DOWN; break;
		case 'd': currentDirection = Direction::RIGHT; break;
		}
	}
}
