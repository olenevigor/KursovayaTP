#include "Application.h"
#include "MainMenuScene.h"

void Application::run()
{
	// Создание окна
	window.create({ 800, 600 }, "Even-Odd", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);

	// Инициализация начальной сцены
	SceneManager::getInstance().run(std::make_unique<MainMenuScene>());

	// Главный цикл игры
	while (SceneManager::getInstance().running())
	{
		SceneManager::getInstance().nextState();
		SceneManager::getInstance().update();
		SceneManager::getInstance().draw();
	}
}

sf::RenderWindow Application::window;