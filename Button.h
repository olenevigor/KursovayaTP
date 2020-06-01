#pragma once

#include <string>

#include <SFML/Graphics.hpp>

// ����������� ��������� ������
const sf::Vector2f GUI_BUTTON_SIZE(210, 70);
const sf::Color GUI_BUTTON_FILL_COLOR(8, 76, 97, 255);
const sf::Color GUI_BUTTON_OUTLINE_COLOR(23, 42, 58, 255);
const int GUI_BUTTON_OUTLINE_THICKNESS = 3;

// ��������� ������
namespace state
{
	enum
	{
		normal = 0,
		hovered = 1,
		clicked = 2
	};
}

// ����� ������ ��� ����������
class Button
{
public:
	Button();
	void setPosition(float x, float y); // ��������� �������
	void setText(const std::string& str); // ��������� �������
	void setFont(const sf::Font& font); // ��������� ������
	sf::Vector2f getSize() const; // ��������� �������
	sf::Uint32 getState() const; // ��������� ���������
	void input(sf::Event ev, sf::RenderWindow& window); // ���������� ��������� ������
	void render(sf::RenderWindow& window); // ���������
private:
	sf::Text text; // ����� �� ������
	sf::RectangleShape box; // ������������� (��� ����������� ������)
	sf::Uint32 buttonState; // ���������
	void setActive(bool arg); // ��������/����� ��������� ������
};