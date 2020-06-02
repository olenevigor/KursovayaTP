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
	// Сообщение об инициализации сцены, нужно для дебага
	std::cout << "MainMenuScene Init\n";

	// Загрузка шрифта
	font.loadFromFile("Roboto-Medium.ttf");

	// Центр экрана по иксу
	int halfWidth = window.getSize().x / 2;

	// Инициализация элементов интерфейса

	// Кнопка новой игры
	newGameButton.setFont(font);
	newGameButton.setText("New Game");
	newGameButton.setPosition(halfWidth - newGameButton.getSize().x / 2, 140);

	// Кнопка подключения
	connectButton.setFont(font);
	connectButton.setText("Connect");
	connectButton.setPosition(halfWidth - connectButton.getSize().x / 2, 220);

	// Кнопка выхода из игры
	exitButton.setFont(font);
	exitButton.setText("Exit");
	exitButton.setPosition(halfWidth - exitButton.getSize().x / 2, 300);
}

void MainMenuScene::update()
{
	// Обработка событий (движение мыши, клик, нажатие клавиш и т.д.)
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		// Проверка на закрытие приложения
		if (event.type == sf::Event::Closed)
		{
			SceneManager::getInstance().quit();
		}

		// Обновление состояний кнопок
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
			// Выход из игры
			SceneManager::getInstance().quit();
		}
	}
}

void MainMenuScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// Отрисовка элементов интерфейса
	newGameButton.render(window);
	connectButton.render(window);
	exitButton.render(window);

	window.display();
}