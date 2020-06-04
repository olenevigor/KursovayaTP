#include "OfflinePlayScene.h"
#include "EndGameScene.h"

#include <iostream>

OfflinePlayScene::OfflinePlayScene(int gridSize) : grid(gridSize), player1Turn(true) { }

void OfflinePlayScene::init()
{
	// ��������� �� ������������� �����, ����� ��� ������
	std::cout << "OfflinePlayScene Init\n";

	// ��������� �������� ������
	int screenWidth = window.getSize().x;
	int screenHeight = window.getSize().y;

	// ����������� ���� � �����
	grid.setPosition(screenWidth / 2 - grid.getSize().x / 2, screenHeight / 2 - grid.getSize().y / 2);

	// �������� ������
	font.loadFromFile("Roboto-Medium.ttf");

	// ������������� ��������� ����������
	
	// ����� �������� ������
	turnText.setFont(font);
	turnText.setString("Player 1 turn");
	turnText.setPosition(screenWidth / 2 - turnText.getGlobalBounds().width / 2, 40);

	// ������ ����������� � ����
	backButton.setFont(font);
	backButton.setText("Back");
	backButton.setPosition(window.getSize().x / 2 - backButton.getSize().x / 2, 490);
}

void OfflinePlayScene::update()
{
	// ��������� ������� (�������� ����, ����, ������� ������ � �.�.)
	for (auto event = sf::Event{}; window.pollEvent(event);)
	{
		// �������� �� �������� ���������� ��� �����
		if (event.type == sf::Event::Closed)
		{
			SceneManager::getInstance().quit();
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			SceneManager::getInstance().closeScene();
		}

		// ���������� ��������� ������ ������
		backButton.input(event, window);
		if (backButton.getState() == state::clicked)
		{
			// �������� �����
			SceneManager::getInstance().closeScene();
		}

		int row, col;
		int turn = grid.input(event, window, row, col);

		// �������� ���� �� �������� ����
		if (turn != -1)
		{
			// ���������� ������ �������� ������
			if (player1Turn)
			{
				turnText.setString("Player 2 turn");
			}
			else
			{
				turnText.setString("Player 1 turn");
			}

			player1Turn = !player1Turn;

			// �������� ����� ����
			int evens, odds;
			if (grid.checkWin(evens, odds))
			{
				// ���� ���� ������ �������, ��������� ����� ����� ����
				SceneManager::getInstance().loadScene(std::make_unique<EndGameScene>(evens, odds), true);
			}
		}
	}
}

void OfflinePlayScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// ��������� ���������� � ����
	grid.render(window);
	window.draw(turnText);
	backButton.render(window);

	window.display();
}