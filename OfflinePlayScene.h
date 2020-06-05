#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Button.h"

// Сцена оффлайн игры
class OfflinePlayScene final : public Scene
{
public:
	OfflinePlayScene(int gridSize);
	void init() override;
	void update() override;
	void draw() override;
private:
	Grid grid; // Игровое поле
	sf::Font font; // Шрифт
	sf::Text turnText; // Текст текущего игрока
	bool player1Turn; // Текущий игрок
	Button backButton; // Кнопка возвращения в меню
};