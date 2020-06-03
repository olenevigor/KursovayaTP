#pragma once

#include <SFML/Graphics.hpp>

#include "Cell.h"

// ����������� ��������� ����
const sf::Color GUI_GRID_FILL_COLOR(8, 76, 97, 255);
const sf::Color GUI_GRID_OUTLINE_COLOR(23, 42, 58, 255);

// ����� �������� ����
class Grid
{
private:
	int size; // ������ ���� (size ����� �� size ��������)
	int cellSize; // ������ ������
	int filled; // ���������� ����������� ������

	sf::Vector2f position; // ������� ���� (������� ����� ����)

	sf::RectangleShape outlineRect; // ������� �������������
	sf::Font font; // �����
	Cell** cells; // ������������ ������ ������
	Cell* activeCell; // ��������� �� ���������� ������
public:
	Grid(int Size);
	~Grid();

	void initGrid(int Size); // ������� �������� ����
	void setCell(int row, int col, char val); // ������� ��������� �������� � ������
	sf::Vector2f getSize() const; // ��������� ������� � ��������
	int getGridSize() const; // ��������� ������� � �������
	void setPosition(float x, float y); // ��������� �������

	bool checkWin(int& evens, int& odds); // �������� �� ���������� ����

	int input(sf::Event ev, sf::RenderWindow& window, int& row, int& col); // ���������� ���������
	void render(sf::RenderWindow& window) const; // ���������
};