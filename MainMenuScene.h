#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Button.h"

// сцена главного меню
class MainMenuScene final : public Scene
{
public:
	MainMenuScene();
	void init() override;
	void update() override;
	void draw() override;
private:
	Button newGameButton; //  кнопка новой игры
	Button connectButton; //  кнопка подключения
	Button exitButton; //  кнопка выхода
	sf::Font font; // шрифт
};