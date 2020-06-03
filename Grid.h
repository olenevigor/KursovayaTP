#pragma once

#include <SFML/Graphics.hpp>

#include "Cell.h"

// Стандартные настройки поля
const sf::Color GUI_GRID_FILL_COLOR(8, 76, 97, 255);
const sf::Color GUI_GRID_OUTLINE_COLOR(23, 42, 58, 255);

// Класс игрового поля
class Grid
{
private:
	int size; // Размер поля (size строк на size столбцов)
	int cellSize; // Размер клетки
	int filled; // Количество заполненных клеток

	sf::Vector2f position; // Позиция поля (верхний левый угол)

	sf::RectangleShape outlineRect; // Фоновый прямоугольник
	sf::Font font; // Шрифт
	Cell** cells; // Динамический массив клеток
	Cell* activeCell; // Указатель на выделенную клетку
public:
	Grid(int Size);
	~Grid();

	void initGrid(int Size); // Функция создания поля
	void setCell(int row, int col, char val); // Функция установки значения в клетку
	sf::Vector2f getSize() const; // Получение размера в пикселях
	int getGridSize() const; // Получения размера в клетках
	void setPosition(float x, float y); // Установка позиции

	bool checkWin(int& evens, int& odds); // Проверка на завершение игры

	int input(sf::Event ev, sf::RenderWindow& window, int& row, int& col); // Обновление состояния
	void render(sf::RenderWindow& window) const; // Отрисовка
};