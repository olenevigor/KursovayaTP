#include "Application.h"
#include "MainMenuScene.h"

void Application::run()
{
	// создание окна
	window.create({ 800, 600 }, "Even-Odd", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);

	// инициализаци¤ начальной сцены
	SceneManager::getInstance().run(std::make_unique<MainMenuScene>());

	// главный цикл игры
	while (SceneManager::getInstance().running())
	{
		SceneManager::getInstance().nextState();
		SceneManager::getInstance().update();
		SceneManager::getInstance().draw();
	}
}

sf::RenderWindow Application::window;