#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Button.h"

// —цена главного меню
class MainMenuScene final : public Scene
{
public:
	MainMenuScene();
	void init() override;
	void update() override;
	void draw() override;
private:
	Button newGameButton; //  нопка новой игры
	Button connectButton; //  нопка подключени€
	Button exitButton; //  нопка выхода
	sf::Font font; // Ўрифт
};