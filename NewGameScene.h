#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Button.h"
#include "TextField.h"

// Сцена создания одиночной/мультиплеерной игры
class NewGameScene final : public Scene
{
public:
	NewGameScene();
	void init() override;
	void update() override;
	void draw() override;
private:
	sf::Font font; // Шрифт
	sf::Text sizeText; // Текст размера поля
	sf::Text portText; // Текст порта
	TextField sizeTextField; // Текстовое поле для ввода размера поля
	TextField portTextField; // Текстовое поле для ввода порта
	Button playButton; // Кнопка начать оффлайн игру
	Button serverButton; // Кнопка создать сервер
	Button backButton; // Кнопка возвращения в меню
};