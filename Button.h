#pragma once

#include <string>

#include <SFML/Graphics.hpp>

// Стандартные настройки кнопки
const sf::Vector2f GUI_BUTTON_SIZE(210, 70);
const sf::Color GUI_BUTTON_FILL_COLOR(8, 76, 97, 255);
const sf::Color GUI_BUTTON_OUTLINE_COLOR(23, 42, 58, 255);
const int GUI_BUTTON_OUTLINE_THICKNESS = 3;

// Состояния кнопки
namespace state
{
	enum
	{
		normal = 0,
		hovered = 1,
		clicked = 2
	};
}

// Класс кнопки для интерфейса
class Button
{
public:
	Button();
	void setPosition(float x, float y); // Установка позиции
	void setText(const std::string& str); // Установка размера
	void setFont(const sf::Font& font); // Установка шрифта
	sf::Vector2f getSize() const; // Получения размера
	sf::Uint32 getState() const; // Получение состояния
	void input(sf::Event ev, sf::RenderWindow& window); // Обновление состояния кнопки
	void render(sf::RenderWindow& window); // Отрисовка
private:
	sf::Text text; // Текст на кнопке
	sf::RectangleShape box; // Прямоугольник (для отображения кнопки)
	sf::Uint32 buttonState; // Состояние
	void setActive(bool arg); // Выделить/снять выделение кнопки
};