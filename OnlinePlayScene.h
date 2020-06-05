#pragma once

#include <SFML/Network.hpp>
#include <string>

#include "Scene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Button.h"

// Сцена онлайн игры
class OnlinePlayScene : public Scene
{
public:
	OnlinePlayScene(int gridSize, std::string Address, int _PORT, bool IsServer);
	void init() override;
	void update() override;
	void draw() override;
private:
	Grid grid; // Игровое поле
	sf::Font font; // Шрифт
	sf::Text turnText; // Текст текущего игрока

	bool isServer; // Открыта ли сцена у сервера
	bool player1Turn; // Текущий игрок
	bool clientConnected; // Подключен ли клиент

	int PORT; // Порт
	std::string address; // Ип-адрес
	sf::TcpSocket socket; // Сокет для передачи пакетов
	sf::Mutex globalMutex; // Мутекс для обеспечения безопастности многопотока
	sf::Packet serverPacket; // Пакет

	sf::Thread listenerThread; // Поток для получения пакетов от другого игрока
	sf::TcpListener listener;

	Button backButton; // Кнопка возвращения в меню

	void packetListener(); // Функция для молучения пакетов от другого игрока
	void serverSend(); // Функция для отправки пакета другому игроку
};