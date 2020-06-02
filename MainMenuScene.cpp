#include "MainMenuScene.h"
#include "OfflinePlayScene.h"
#include "OnlinePlayScene.h"
#include "ConnectScene.h"
#include "NewGameScene.h"
#include "Application.h"

#include <iostream>

MainMenuScene::MainMenuScene() { }

void MainMenuScene::init()
{
	// ��������� �� ������������� �����, ����� ��� ������
	std::cout << "MainMenuScene Init\n";

	// �������� ������
	font.loadFromFile("Roboto-Medium.ttf");

	// ����� ������ �� ����
	int halfWidth = window.getSize().x / 2;

	// ������������� ��������� ����������

	// ������ ����� ����
	newGameButton.setFont(font);
	newGameButton.setText("New Game");
	newGameButton.setPosition(halfWidth - newGameButton.getSize().x / 2, 140);

	// ������ �����������
	connectButton.setFont(font);
	connectButton.setText("Connect");
	connectButton.setPosition(halfWidth - connectButton.getSize().x / 2, 220);

	// ������ ������ �� ����
	exitButton.setFont(font);
	exitButton.setText("Exit");
	exitButton.setPosition(halfWidth - exitButton.getSize().x / 2, 300);
}

void MainMenuScene::update()
{
	// ��������� ������� (�������� ����, ����, ������� ������ � �.�.)
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		// �������� �� �������� ����������
		if (event.type == sf::Event::Closed)
		{
			SceneManager::getInstance().quit();
		}

		// ���������� ��������� ������
		exitButton.input(event, window);
		newGameButton.input(event, window);
		connectButton.input(event, window);

		if (newGameButton.getState() == state::clicked)
		{
			
			(std::make_unique<NewGameScene>());
		}
		else if (connectButton.getState() == state::clicked)
		{
			(std::make_unique<ConnectScene>());
		}
		else if (exitButton.getState() == state::clicked)
		{
			// ����� �� ����
			SceneManager::getInstance().quit();
		}
	}
}

void MainMenuScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// ��������� ��������� ����������
	newGameButton.render(window);
	connectButton.render(window);
	exitButton.render(window);

	window.display();
}