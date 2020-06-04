#include "NewGameScene.h"
#include "OfflinePlayScene.h"
#include "OnlinePlayScene.h"

#include <iostream>

NewGameScene::NewGameScene() { }

void NewGameScene::init()
{
	// ��������� �� ������������� �����, ����� ��� ������
	std::cout << "NewGameScene Init\n";

	// �������� ������
	font.loadFromFile("Roboto-Medium.ttf");

	// ������������� ��������� ����������

	// ����� "Grid size: "
	sizeText.setFont(font);
	sizeText.setString("Grid size: ");
	sizeText.setPosition(window.getSize().x / 2 - sizeText.getGlobalBounds().width / 2, 20);

	// ����� "PORT: "
	portText.setFont(font);
	portText.setString("PORT: ");
	portText.setPosition(window.getSize().x / 2 - portText.getGlobalBounds().width / 2, 100);

	// ��������� ���� ��� ����� ������� ����
	sizeTextField.setFont(font);
	sizeTextField.setText("6"); // �� ��������� 6
	sizeTextField.setPosition(sf::Vector2f(window.getSize().x / 2 - sizeTextField.getSize().x / 2, 60));

	// ��������� ���� ��� ����� �����
	portTextField.setFont(font);
	portTextField.setText("7777"); // �� ��������� 7777
	portTextField.setPosition(sf::Vector2f(window.getSize().x / 2 - portTextField.getSize().x / 2, 140));

	// ������ ������� ������� ����
	playButton.setFont(font);
	playButton.setText("Play");
	playButton.setPosition(window.getSize().x / 2 - playButton.getSize().x / 2, 220);

	// ������ �������� �������
	serverButton.setFont(font);
	serverButton.setText("Create server");
	serverButton.setPosition(window.getSize().x / 2 - serverButton.getSize().x / 2, 300);

	// ������ ����������� � ������� ����
	backButton.setFont(font);
	backButton.setText("Back");
	backButton.setPosition(window.getSize().x / 2 - backButton.getSize().x / 2, 490);
}

void NewGameScene::update()
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

		// ���������� ��������� ������
		playButton.input(event, window);
		serverButton.input(event, window);
		backButton.input(event, window);

		// ���������� ��������� ��������� �����
		sizeTextField.input(event);
		portTextField.input(event);

		if (playButton.getState() == state::clicked)
		{
			// ������� ������� ���� �� ���������� ����
			int size = atoi(sizeTextField.getText().toAnsiString().c_str());

			// ����������� ������� ����
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
				// ��������� ����� ������� ����
				SceneManager::getInstance().loadScene(std::make_unique<OfflinePlayScene>(size));
			}
		}
		else if (serverButton.getState() == state::clicked)
		{
			// ������� ������� ���� �� ���������� ����
			int size = atoi(sizeTextField.getText().toAnsiString().c_str());
			// ������� ����� �� ���������� ����
			int port = atoi(portTextField.getText().toAnsiString().c_str());

			// ����������� ������� ����
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
				// ��������� ����� ������ ����
				SceneManager::getInstance().loadScene(std::make_unique<OnlinePlayScene>(size, "127.0.0.1", port, true));
			}
		}
		else if (backButton.getState() == state::clicked)
		{
			// �������� �����
			SceneManager::getInstance().closeScene();
		}
	}
}

void NewGameScene::draw()
{
	window.clear(sf::Color(9, 188, 138, 255));

	// ��������� ��������� ����������
	window.draw(sizeText);
	window.draw(portText);
	sizeTextField.render(window);
	portTextField.render(window);
	playButton.render(window);
	serverButton.render(window);
	backButton.render(window);

	window.display();
}