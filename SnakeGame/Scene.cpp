#include "Scene.h"
#include "Snake.h"
#include "Fruit.h"

#include <cstdlib>

// Constructor: Initialize scene with references, and initial score
Scene::Scene(Snake &sn, Fruit &f) 
	: snake(sn), fruit(f), score(0) {
 }

void Scene::draw() const {

	system("cls");

	// drawing edje
	for (int i = 0; i < width; ++i) {
		std::cout << "#";
	}
	std::cout << std::endl;

	// drawing heigth
	for (int i = 0; i < height; ++i) {

		for (int j = 0; j < width; j++) {
			if (j == 0) {
				std::cout << "#";
			}
			else if (j == width - 1) {
				std::cout << "#";
			}

			else {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	// drawing edje
	for (int i = 0; i < width; ++i) {
		std::cout << "#";
	}

	std::cout << std::endl;
	std::cout << "Score: " << score << std::endl;

}

int Scene::getHeight() const {
	return height;
}

int Scene::getWidth() const {
	return width;
}

void Scene::updateScore(int value) {
	score += value;
}
