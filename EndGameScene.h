#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Button.h"

// Сцена завершения игры с подсчётом очков
class EndGameScene final : public Scene
{
public:
	// В конструктор передаётся количество чётных сумм и нечётных
	EndGameScene(int Evens, int Odds);
	void init() override;
	void update() override;
	void draw() override;
private:
	sf::Font font; // Шрифт
	sf::Text winText; // Текст о победителе
	sf::Text evenNumbersText; // Текст о количестве четных сумм
	sf::Text oddsNumbersText; // Текст о количестве нечетных сумм
	Button backButton; // Кнопка возращения назад

	int evens; // Количество четных сумм
	int odds; // Количество нечетных сумм
};