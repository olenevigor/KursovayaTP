#include "SceneManager.h"
#include "Scene.h"

#include <iostream>

SceneManager::SceneManager()
	: resume{ false }
	, isRunning{ false }
	, isClosing{ false }
{
	std::cout << "SceneManager Init\n";
}

void SceneManager::run(std::unique_ptr<Scene> scene)
{
	isRunning = true;
	loadScene(std::move(scene));
}

void SceneManager::loadScene(std::unique_ptr<Scene> scene, bool replace)
{
	if (replace)
		isClosing = true;
	next = std::move(scene);
}

void SceneManager::closeScene()
{
	isClosing = true;
}

void SceneManager::nextState()
{
	if (isClosing)
	{
		scenes.pop();
		isClosing = false;
	}

	if (next)
	{
		scenes.push(std::move(next));
		scenes.top()->init();
	}
}

void SceneManager::update()
{
	// Обновление текущей сцены
	scenes.top()->update();
}

void SceneManager::draw()
{
	// Отрисовка текущей сцены
	scenes.top()->draw();
}

bool SceneManager::running() const
{
	return isRunning;
}

void SceneManager::quit()
{
	isRunning = false;
}