#pragma once

#include <stack>

#include "Scene.h"

class Scene;

// Для менеджера сцен использован паттерн Singleton Мэйерса
class SceneManager
{
private:
	// Приватные конструкторы для паттерна
	SceneManager();
	SceneManager(const SceneManager&);
	SceneManager& operator=(SceneManager&);

	std::stack<std::unique_ptr<Scene>> scenes;

	bool resume;
	bool isRunning;
	bool isClosing;

	std::unique_ptr<Scene> next;
public:
	// Статическая функция для паттерна
	static SceneManager& getInstance() {
		static SceneManager instance;
		return instance;
	}

	void run(std::unique_ptr<Scene> scene); // Загрузить начальную сцену

	void loadScene(std::unique_ptr<Scene> scene, bool replace = false); // Загрузить новую сцену
	void closeScene(); // Закрыть текущую сцену

	void nextState(); // Обновление состояние сцен (закрыть/открыть сцену)
	void update(); // Обновление текущей сцены
	void draw(); // Отрисовка текущей сцены

	bool running() const;
	void quit();
};