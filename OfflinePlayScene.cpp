#include "OfflinePlayScene.h"
#include "EndGameScene.h"

#include <iostream>

OfflinePlayScene::OfflinePlayScene(int gridSize) : grid(gridSize), player1Turn(true) { }

void OfflinePlayScene::init()
{
	// Сообщение об инициализации сцены, нужно для дебага
	std::cout << "OfflinePlayScene Init\n";

	// Получение размеров экрана
	int screenWidth = window.getSize().x;
	int screenHeight = window.getSize().y;

	// Перемещение поля в центр
	grid.setPosition(screenWidth / 2 - grid.getSize().x / 2, screenHeight / 2 - grid.getSize().y / 2);

	// Загрузка шрифта
	font.loadFromFile("Roboto-Medium.ttf");

	// Инициализация элементов интерфейса
	
	// Текст текущего игрока
	turnText.setFont(font);
	turnText.setString("Player 1 turn");
	turnText.setPosition(screenWidth / 2 - turnText.getGlobalBounds().width / 2, 40);

	// Кнопка возвращения в меню
	backButton.setFont(font);
	backButton.setText("Back");
	backButton.setPosition(window.getSize().x / 2 - backButton.getSize().x / 2, 490);
}

void OfflinePlayScene::update()
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

		// Обновления состояния кнопки выхода
		backButton.input(event, window);
		if (backButton.getState() == state::clicked)
		{
			// Закрытие сцены
			SceneManager::getInstance().closeScene();
		}

		int row, col;
		int turn = grid.input(event, window, row, col);

		// Проверка было ли изменено поле
		if (turn != -1)
		{
			// Обновление текста текущего игрока
			if (player1Turn)
			{
				turnText.setString("Player 2 turn");
			}
			else
			{
				turnText.setString("Player 1 turn");
			}

			player1Turn = !player1Turn;

			// Проверка конца игры
			int evens, odds;
			if (grid.checkWin(evens, odds))
			{
				// Если поле занято целиком, загружаем сцену конца игры
				SceneManager::getInstance().loadScene(std::make_unique<EndGameScene>(evens, odds), true);
			}
		}
	}
}

void OfflinePlayScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// Отрисовка интерфейса и поля
	grid.render(window);
	window.draw(turnText);
	backButton.render(window);

	window.display();
}