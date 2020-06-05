#include "ConnectScene.h"

#include <iostream>

ConnectScene::ConnectScene() { }

void ConnectScene::init()
{
	std::cout << "ConnectScene Init\n";

	font.loadFromFile("Roboto-Medium.ttf");

	int halfWidth = window.getSize().x / 2;

	// Поле ввода ip-адреса
	addressField.setFont(font);
	addressField.setPosition(sf::Vector2f(halfWidth - addressField.getSize().x / 2, 90));
	addressField.setText("127.0.0.1");

	// Поле ввода порта
	portField.setFont(font);
	portField.setPosition(sf::Vector2f(halfWidth - addressField.getSize().x / 2, 140));
	portField.setText("7777");


	// Кнопка подключения
	connectButton.setFont(font);
	connectButton.setText("Connect");
	connectButton.setPosition(halfWidth - connectButton.getSize().x / 2, 190);

	// Кнопка возврата в главное меню
	backButton.setFont(font);
	backButton.setText("Back");
	backButton.setPosition(halfWidth - backButton.getSize().x / 2, 270);
}

void ConnectScene::update()
{
	// Обработка событий (движение мыши, клик, нажатие клавиш и т.д.)
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		// Проверки на закрытие приложения или сцены
		if (event.type == sf::Event::Closed)
		{
			SceneManager::getInstance().quit();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			SceneManager::getInstance().closeScene();
		}
		
		// Обновление состояний кнопок
		connectButton.input(event, window);
		backButton.input(event, window);

		// Обновление состояний текстовых полей
		addressField.input(event);
		portField.input(event);

		if (connectButton.getState() == state::clicked)
		{
			int port = atoi(portField.getText().toAnsiString().c_str());

			// Загрузка сцены онлайн игры
			SceneManager::getInstance().loadScene(
				std::make_unique<OnlinePlayScene>(0, addressField.getText(), port, false));
		}
		else if (backButton.getState() == state::clicked)
		{
			// Закрытие сцены
			SceneManager::getInstance().closeScene();
		}
	}
}

void ConnectScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// Отрисовка элементов интерфейса
	addressField.render(window);
	portField.render(window);
	connectButton.render(window);
	backButton.render(window);

	window.display();
}