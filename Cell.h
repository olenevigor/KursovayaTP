#pragma once

#include <SFML/Graphics.hpp>

const sf::Color GUI_CELL_OUTLINE_COLOR(23, 42, 58, 255);
const int GUI_CELL_OUTLINE_THICKNESS = 3;

// Класс отдельной клетки на поле
class Cell
{
private:
	char value; // Значение клетки
	sf::Text text; // Текст для отрисовки значения клетки
	sf::RectangleShape rect; // Прямоугольник клетки
	sf::Vector2f position; // Позиция клетки
	bool isActive; // Состояние клетки
public:
	Cell();

	void setFont(sf::Font& font); // Установка шрифта
	void setValue(char Value); // Установка значения
	char getValue() const; // Получение значения
	void setPosition(float x, float y); // Установка позиции
	void setSize(int size); // Установка размера
	int getSize() const; // Получение размера
	void setActive(bool active); // Получение состояния
	void render(sf::RenderWindow& window); // Отрисовка клетки
};