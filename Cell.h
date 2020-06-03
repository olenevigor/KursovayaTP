#pragma once

#include <SFML/Graphics.hpp>

const sf::Color GUI_CELL_OUTLINE_COLOR(23, 42, 58, 255);
const int GUI_CELL_OUTLINE_THICKNESS = 3;

// ����� ��������� ������ �� ����
class Cell
{
private:
	char value; // �������� ������
	sf::Text text; // ����� ��� ��������� �������� ������
	sf::RectangleShape rect; // ������������� ������
	sf::Vector2f position; // ������� ������
	bool isActive; // ��������� ������
public:
	Cell();

	void setFont(sf::Font& font); // ��������� ������
	void setValue(char Value); // ��������� ��������
	char getValue() const; // ��������� ��������
	void setPosition(float x, float y); // ��������� �������
	void setSize(int size); // ��������� �������
	int getSize() const; // ��������� �������
	void setActive(bool active); // ��������� ���������
	void render(sf::RenderWindow& window); // ��������� ������
};