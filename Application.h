#pragma once

#include "SceneManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

class SceneManager;

// Основной класс приложения
class Application
{
public:
	void run(); // Запуск приложения

	static sf::RenderWindow window; // Статичная переменная для хранения окна, в которое отрисовывается игра
};