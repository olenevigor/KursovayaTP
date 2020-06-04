#pragma once

#include <SFML/Network.hpp>
#include <string>

#include "Scene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Button.h"

// ����� ������ ����
class OnlinePlayScene : public Scene
{
public:
	OnlinePlayScene(int gridSize, std::string Address, int _PORT, bool IsServer);
	void init() override;
	void update() override;
	void draw() override;
private:
	Grid grid; // ������� ����
	sf::Font font; // �����
	sf::Text turnText; // ����� �������� ������

	bool isServer; // ������� �� ����� � �������
	bool player1Turn; // ������� �����
	bool clientConnected; // ��������� �� ������

	int PORT; // ����
	std::string address; // ��-�����
	sf::TcpSocket socket; // ����� ��� �������� �������
	sf::Mutex globalMutex; // ������ ��� ����������� ������������� �����������
	sf::Packet serverPacket; // �����

	sf::Thread listenerThread; // ����� ��� ��������� ������� �� ������� ������
	sf::TcpListener listener;

	Button backButton; // ������ ����������� � ����

	void packetListener(); // ������� ��� ��������� ������� �� ������� ������
	void serverSend(); // ������� ��� �������� ������ ������� ������
};