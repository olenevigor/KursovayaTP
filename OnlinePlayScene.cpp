#include "OnlinePlayScene.h"
#include "EndGameScene.h"

#include <iostream>

OnlinePlayScene::OnlinePlayScene(int gridSize, std::string Address, int _PORT, bool IsServer)
	: grid(gridSize), listenerThread(&OnlinePlayScene::packetListener, this), isServer(IsServer), 
	address(Address), PORT(_PORT), clientConnected(!IsServer), player1Turn(IsServer)
{
}

void OnlinePlayScene::init()
{
	// Сообщение об инициализации сцены, нужно для дебага
	std::cout << "OnlinePlayScene Init\n";

	// Если не получается подключиться к серверу, закрываем сцену
	if (!isServer && socket.connect(address, PORT, sf::Time(sf::seconds(2))) != sf::Socket::Done)
	{
		SceneManager::getInstance().closeScene();
		return;
	}

	// Если сцена запущена для клиента, получаем у сервера размер поля
	if (!isServer)
	{
		// receive grid size
		int gridSize;
		socket.receive(serverPacket);
		serverPacket >> gridSize;
		serverPacket.clear();

		grid.initGrid(gridSize);
	}

	// Поток для получения пакетов от другого игрока
	listenerThread.launch();

	// Получение размеров экрана
	int screenWidth = window.getSize().x;
	int screenHeight = window.getSize().y;

	// Перемещение поля в центр
	grid.setPosition(screenWidth / 2 - grid.getSize().x / 2, screenHeight / 2 - grid.getSize().y / 2);

	// Загрузка шрифтов
	font.loadFromFile("Roboto-Medium.ttf");

	// Инициализация элементов интерфейса

	// Текст текущего игрока
	turnText.setFont(font);
	turnText.setString("Waiting second player...");
	turnText.setPosition(screenWidth / 2 - turnText.getGlobalBounds().width / 2, 40);

	// Кнопка возвращения в меню
	backButton.setFont(font);
	backButton.setText("Back");
	backButton.setPosition(window.getSize().x / 2 - backButton.getSize().x / 2, 490);
}

void OnlinePlayScene::update()
{
	// Обработка событий (движение мыши, клик, нажатие клавиш и т.д.)
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		// Проверки на закрытие приложения или сцены
		if (event.type == sf::Event::Closed)
		{
			// Закрытие потока получения пакетов от другого игрока
			listenerThread.terminate();
			// Закрытие приложения
			SceneManager::getInstance().quit();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			// Закрытие потока получения пакетов от другого игрока
			listenerThread.terminate();
			listener.close();
			// Закрытие сцены
			SceneManager::getInstance().closeScene();
		}

		// Обновления состояния кнопки выхода
		backButton.input(event, window);
		if (backButton.getState() == state::clicked)
		{
			// Закрытие потока получения пакетов от другого игрока
			listenerThread.terminate();
			listener.close();
			// Закрытие сцены
			SceneManager::getInstance().closeScene();
		}

		// Если текущий ход и клиент подключен
		if (player1Turn && clientConnected)
		{
			// Получаем состояние поля
			int row, col;
			int turn = grid.input(event, window, row, col);

			// Если поле было изменено
			if (turn != -1)
			{
				// Пока делаем ход блокируем получение пакетов
				globalMutex.lock();

				// Отправляем текущий ход другому игроку
				serverPacket << row << col << turn;
				serverSend();

				player1Turn = false;

				// Обновление текста
				turnText.setString("Waiting other player...");
				turnText.setPosition(window.getSize().x / 2 - turnText.getGlobalBounds().width / 2, turnText.getPosition().y);

				// Проверка завершения игры
				int evens, odds;
				if (grid.checkWin(evens, odds))
				{
					listenerThread.terminate();
					listener.close();

					// Загружаем сцену завершения игры
					SceneManager::getInstance().loadScene(std::make_unique<EndGameScene>(evens, odds), true);
				}

				// Разблокировка получения пакетов
				globalMutex.unlock();
			}
		}
	}
}

void OnlinePlayScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// Отрисовка интерфейса и поля
	grid.render(window);
	window.draw(turnText);
	backButton.render(window);

	window.display();
}

void OnlinePlayScene::packetListener()
{
	if (isServer)
	{
		// Ожидаем подключения клиента
		std::cout << "Listening for clients." << std::endl;
		listener.listen(PORT);
		listener.accept(socket);
		std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
		clientConnected = true;

		turnText.setString("Your turn");
		turnText.setPosition(window.getSize().x / 2 - turnText.getGlobalBounds().width / 2, turnText.getPosition().y);

		// Отправляем клиенту размер поля
		serverPacket << grid.getGridSize();
		serverSend();
	}

	while (window.isOpen())
	{
		// Получаем пакет от другого игрока
		socket.receive(serverPacket);

		while (!serverPacket.endOfPacket())
		{
			// Блокируем ход пока получаем ход другого игрока
			globalMutex.lock();

			// Распаковываем пакет в переменные
			int row, col, val;
			serverPacket >> row >> col >> val;

			// Обновляем поле (вписываем ход другого игрока)
			grid.setCell(row, col, '0' + val);
			player1Turn = true;

			// Обновляем текст
			turnText.setString("Your turn");
			turnText.setPosition(window.getSize().x / 2 - turnText.getGlobalBounds().width / 2, turnText.getPosition().y);

			// Проверка на завершение игры
			int evens, odds;
			if (grid.checkWin(evens, odds))
			{
				// Загрузка сцены завершения игры
				SceneManager::getInstance().loadScene(std::make_unique<EndGameScene>(evens, odds), true);
				listener.close();
				listenerThread.terminate();
			}

			// Разблокировка хода
			globalMutex.unlock();
		}

		// Очищаем пакет
		serverPacket.clear();
	}
}

void OnlinePlayScene::serverSend()
{
	// Отправка пакета другому игроку
	if (serverPacket.getDataSize() > 0)
	{
		globalMutex.lock();
		socket.send(serverPacket);
		serverPacket.clear();
		globalMutex.unlock();
	}
}