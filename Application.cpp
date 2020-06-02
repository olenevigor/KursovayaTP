#include "Application.h"
#include "MainMenuScene.h"

void Application::run()
{
	// �������� ����
	window.create({ 800, 600 }, "Even-Odd", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(30);

	// ������������� ��������� �����
	SceneManager::getInstance().run(std::make_unique<MainMenuScene>());

	// ������� ���� ����
	while (SceneManager::getInstance().running())
	{
		SceneManager::getInstance().nextState();
		SceneManager::getInstance().update();
		SceneManager::getInstance().draw();
	}
}

sf::RenderWindow Application::window;