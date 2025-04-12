#include <iostream>
#include <windows.h>

#include "Scene.h"
#include "Snake.h"
#include "Fruit.h"

bool gameOver = false;

int main() {

    // for mamory allocation l used malloc
    // malloc — это функция из языка C, означает memory allocation — "выделение памяти"
    // Она выделяет блок памяти в оперативке нужного размера.
    // sizeof(Snake) — это размер одного объекта Snake в байтах.
    // Например, если один Snake занимает 120 байт, то malloc(sizeof(Snake)) выделит 120 байт в памяти.
    // Важно: malloc ничего не конструирует, он просто "даёт пустое место".
    //(тип_в_который_приводим) значение = (Snake*)malloc(...) // превращаем void* в Snake*

    Snake* snake = (Snake*)malloc(sizeof(Snake));
    Fruit* fruit = (Fruit*)malloc(sizeof(Fruit));
    Scene* scene = (Scene*)malloc(sizeof(Scene));  

    //using placement new
    //А вот placement new — это спецверсия new, которая:
    // ✅ НЕ выделяет память,
    //    а просто размещает объект в уже выделенной памяти.
    //Синтаксис:
        //new (указатель_на_память) Тип(аргументы_конструктора);
    //Пример:
        //void* ptr = malloc(sizeof(Scene));
        //new(ptr) Scene(...); // вызываем конструктор Scene по адресу ptr
    //3. Что делает эта строка?
    //new(scene) Scene(*snake, *fruit);
    //Разбиваем по частям:
    //Часть кода
    //new(scene)
    //Что значит
    //Размести объект в памяти по адресу scene
    //Scene(...)
    //Вызови конструктор Scene с нужными аргументами
    //4. Как это работает пошагово
    //Scene* scene = (Scene*)malloc(sizeof(Scene)); // выделили "сырую" память
    //new(scene) Scene(*snake, *fruit);             // разместили в ней объект Scene
    //🔁 Это как
    //Купили участок земли (malloc)
    //Построили дом (placement new — вызвали конструктор)

    new(scene) Scene(*snake, *fruit);
    new(snake) Snake(*scene, *fruit);
    new(fruit) Fruit(*scene, *snake);

    //Game loop
    while (!gameOver) {
        system("cls");              
        scene->draw();             //Draw borders and score
        fruit->draw();             //Draw fruit inside scene
        snake->draw();             //Draw snake (after fruit for layering)

        snake->Move();             //Handle input
        snake->update();           //Move snake and update tail
        fruit->update();           //Handle collision with snake (and respawn if needed)

        Sleep(100);                //Delay for game speed
    }

    //Cleanup
    snake->~Snake();
    fruit->~Fruit();
    scene->~Scene();

    free(snake);
    free(fruit);
    free(scene);

    std::cout << "Game Over!\n";
    return 0;
}


//malloc — ты купил участок земли
//placement new — построил дом на этом участке
//~Object() — вынес мебель, убрался перед переездом
//free — снес фундамент и освободил участок