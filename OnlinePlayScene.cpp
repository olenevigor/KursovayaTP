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
	// ��������� �� ������������� �����, ����� ��� ������
	std::cout << "OnlinePlayScene Init\n";

	// ���� �� ���������� ������������ � �������, ��������� �����
	if (!isServer && socket.connect(address, PORT, sf::Time(sf::seconds(2))) != sf::Socket::Done)
	{
		SceneManager::getInstance().closeScene();
		return;
	}

	// ���� ����� �������� ��� �������, �������� � ������� ������ ����
	if (!isServer)
	{
		// receive grid size
		int gridSize;
		socket.receive(serverPacket);
		serverPacket >> gridSize;
		serverPacket.clear();

		grid.initGrid(gridSize);
	}

	// ����� ��� ��������� ������� �� ������� ������
	listenerThread.launch();

	// ��������� �������� ������
	int screenWidth = window.getSize().x;
	int screenHeight = window.getSize().y;

	// ����������� ���� � �����
	grid.setPosition(screenWidth / 2 - grid.getSize().x / 2, screenHeight / 2 - grid.getSize().y / 2);

	// �������� �������
	font.loadFromFile("Roboto-Medium.ttf");

	// ������������� ��������� ����������

	// ����� �������� ������
	turnText.setFont(font);
	turnText.setString("Waiting second player...");
	turnText.setPosition(screenWidth / 2 - turnText.getGlobalBounds().width / 2, 40);

	// ������ ����������� � ����
	backButton.setFont(font);
	backButton.setText("Back");
	backButton.setPosition(window.getSize().x / 2 - backButton.getSize().x / 2, 490);
}

void OnlinePlayScene::update()
{
	// ��������� ������� (�������� ����, ����, ������� ������ � �.�.)
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		// �������� �� �������� ���������� ��� �����
		if (event.type == sf::Event::Closed)
		{
			// �������� ������ ��������� ������� �� ������� ������
			listenerThread.terminate();
			// �������� ����������
			SceneManager::getInstance().quit();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			// �������� ������ ��������� ������� �� ������� ������
			listenerThread.terminate();
			listener.close();
			// �������� �����
			SceneManager::getInstance().closeScene();
		}

		// ���������� ��������� ������ ������
		backButton.input(event, window);
		if (backButton.getState() == state::clicked)
		{
			// �������� ������ ��������� ������� �� ������� ������
			listenerThread.terminate();
			listener.close();
			// �������� �����
			SceneManager::getInstance().closeScene();
		}

		// ���� ������� ��� � ������ ���������
		if (player1Turn && clientConnected)
		{
			// �������� ��������� ����
			int row, col;
			int turn = grid.input(event, window, row, col);

			// ���� ���� ���� ��������
			if (turn != -1)
			{
				// ���� ������ ��� ��������� ��������� �������
				globalMutex.lock();

				// ���������� ������� ��� ������� ������
				serverPacket << row << col << turn;
				serverSend();

				player1Turn = false;

				// ���������� ������
				turnText.setString("Waiting other player...");
				turnText.setPosition(window.getSize().x / 2 - turnText.getGlobalBounds().width / 2, turnText.getPosition().y);

				// �������� ���������� ����
				int evens, odds;
				if (grid.checkWin(evens, odds))
				{
					listenerThread.terminate();
					listener.close();

					// ��������� ����� ���������� ����
					SceneManager::getInstance().loadScene(std::make_unique<EndGameScene>(evens, odds), true);
				}

				// ������������� ��������� �������
				globalMutex.unlock();
			}
		}
	}
}

void OnlinePlayScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// ��������� ���������� � ����
	grid.render(window);
	window.draw(turnText);
	backButton.render(window);

	window.display();
}

void OnlinePlayScene::packetListener()
{
	if (isServer)
	{
		// ������� ����������� �������
		std::cout << "Listening for clients." << std::endl;
		listener.listen(PORT);
		listener.accept(socket);
		std::cout << "New client connected: " << socket.getRemoteAddress() << std::endl;
		clientConnected = true;

		turnText.setString("Your turn");
		turnText.setPosition(window.getSize().x / 2 - turnText.getGlobalBounds().width / 2, turnText.getPosition().y);

		// ���������� ������� ������ ����
		serverPacket << grid.getGridSize();
		serverSend();
	}

	while (window.isOpen())
	{
		// �������� ����� �� ������� ������
		socket.receive(serverPacket);

		while (!serverPacket.endOfPacket())
		{
			// ��������� ��� ���� �������� ��� ������� ������
			globalMutex.lock();

			// ������������� ����� � ����������
			int row, col, val;
			serverPacket >> row >> col >> val;

			// ��������� ���� (��������� ��� ������� ������)
			grid.setCell(row, col, '0' + val);
			player1Turn = true;

			// ��������� �����
			turnText.setString("Your turn");
			turnText.setPosition(window.getSize().x / 2 - turnText.getGlobalBounds().width / 2, turnText.getPosition().y);

			// �������� �� ���������� ����
			int evens, odds;
			if (grid.checkWin(evens, odds))
			{
				// �������� ����� ���������� ����
				SceneManager::getInstance().loadScene(std::make_unique<EndGameScene>(evens, odds), true);
				listener.close();
				listenerThread.terminate();
			}

			// ������������� ����
			globalMutex.unlock();
		}

		// ������� �����
		serverPacket.clear();
	}
}

void OnlinePlayScene::serverSend()
{
	// �������� ������ ������� ������
	if (serverPacket.getDataSize() > 0)
	{
		globalMutex.lock();
		socket.send(serverPacket);
		serverPacket.clear();
		globalMutex.unlock();
	}
}