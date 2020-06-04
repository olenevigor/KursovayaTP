#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "OnlinePlayScene.h"
#include "Button.h"
#include "TextField.h"

// Сцена подключения к серверу с вводом ip и порта
class ConnectScene : public Scene
{
public:
	ConnectScene();
	void init() override;
	void update() override;
	void draw() override;
private:
	TextField addressField; // Текстовое поле для ввода ип-адреса
	TextField portField; // Текстовое поле для ввода порта
	Button connectButton; // Кнопка для подключения к серверу
	Button backButton; // Кнопка возвращения в меню
	sf::Font font; // Шрифт
};