#include "NewGameScene.h"
#include "OfflinePlayScene.h"
#include "OnlinePlayScene.h"

#include <iostream>

NewGameScene::NewGameScene() { }

void NewGameScene::init()
{
	// Сообщение об инициализации сцены, нужно для дебага
	std::cout << "NewGameScene Init\n";

	// Загрузка шрифта
	font.loadFromFile("Roboto-Medium.ttf");

	// Инициализация элементов интерфейса

	// Текст "Grid size: "
	sizeText.setFont(font);
	sizeText.setString("Grid size: ");
	sizeText.setPosition(window.getSize().x / 2 - sizeText.getGlobalBounds().width / 2, 20);

	// Текст "PORT: "
	portText.setFont(font);
	portText.setString("PORT: ");
	portText.setPosition(window.getSize().x / 2 - portText.getGlobalBounds().width / 2, 100);

	// Текстовое поле для ввода размера поля
	sizeTextField.setFont(font);
	sizeTextField.setText("6"); // По умолчанию 6
	sizeTextField.setPosition(sf::Vector2f(window.getSize().x / 2 - sizeTextField.getSize().x / 2, 60));

	// Текстовое поле для ввода порта
	portTextField.setFont(font);
	portTextField.setText("7777"); // По умолчанию 7777
	portTextField.setPosition(sf::Vector2f(window.getSize().x / 2 - portTextField.getSize().x / 2, 140));

	// Кнопка запуска оффлайн игры
	playButton.setFont(font);
	playButton.setText("Play");
	playButton.setPosition(window.getSize().x / 2 - playButton.getSize().x / 2, 220);

	// Кнопка создания сервера
	serverButton.setFont(font);
	serverButton.setText("Create server");
	serverButton.setPosition(window.getSize().x / 2 - serverButton.getSize().x / 2, 300);

	// Кнопка возвращения в главное меню
	backButton.setFont(font);
	backButton.setText("Back");
	backButton.setPosition(window.getSize().x / 2 - backButton.getSize().x / 2, 490);
}

void NewGameScene::update()
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
		playButton.input(event, window);
		serverButton.input(event, window);
		backButton.input(event, window);

		// Обновление состояний текстовых полей
		sizeTextField.input(event);
		portTextField.input(event);

		if (playButton.getState() == state::clicked)
		{
			// Парсинг размера поля из текстового поля
			int size = atoi(sizeTextField.getText().toAnsiString().c_str());

			// Ограничение размера поля
			if (size > 10)
			{
				sizeTextField.setText("10");
			}
			else if (size < 3)
			{
				sizeTextField.setText("3");
			}
			else
			{
				// Загрузить сцену оффлайн игры
				SceneManager::getInstance().loadScene(std::make_unique<OfflinePlayScene>(size));
			}
		}
		else if (serverButton.getState() == state::clicked)
		{
			// Парсинг размера поля из текстового поля
			int size = atoi(sizeTextField.getText().toAnsiString().c_str());
			// Парсинг порта из текстового поля
			int port = atoi(portTextField.getText().toAnsiString().c_str());

			// Ограничение размера поля
			if (size > 10)
			{
				sizeTextField.setText("10");
			}
			else if (size < 3)
			{
				sizeTextField.setText("3");
			}
			else
			{
				// Загрузить сцену онлайн игры
				SceneManager::getInstance().loadScene(std::make_unique<OnlinePlayScene>(size, "127.0.0.1", port, true));
			}
		}
		else if (backButton.getState() == state::clicked)
		{
			// Закрытие сцены
			SceneManager::getInstance().closeScene();
		}
	}
}

void NewGameScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// Отрисовка элементов интерфейса
	window.draw(sizeText);
	window.draw(portText);
	sizeTextField.render(window);
	portTextField.render(window);
	playButton.render(window);
	serverButton.render(window);
	backButton.render(window);

	window.display();
}