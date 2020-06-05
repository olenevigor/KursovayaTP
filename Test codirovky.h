#pragma once

#include <string>

#include <SFML/Graphics.hpp>

// Стандартные настройки текстового поля
const int GUI_TEXT_MAX = 16;
const int GUI_TEXT_BACKSPACE = 8;
const int GUI_TEXT_ESCAPE = 27;
const sf::Color GUI_TEXT_GRAY = sf::Color(105, 105, 105);
const sf::Color GUI_TEXT_FIELD_FILL_COLOR(8, 76, 97, 255);
const int GUI_TEXT_FIELD_OUTLINE_THICKNESS = 3;

// Класс текстового поля для интерфейса
class TextField {
public:
	TextField();

	void setPosition(sf::Vector2f vec);
	void input(sf::Event ev);
	void setFont(sf::Font& f);
	const sf::String& getText();
	void setPlaceholder(std::string str);
	void render(sf::RenderWindow& window);
	void setLength(int arg);
	int getTextLength();
	bool isActive();
	void open();
	void setText(std::string str);
	sf::Vector2f getSize() const;
private:
	sf::Text txt;
	sf::RectangleShape box;
	int size;
	int length;
	bool renderPlaceholder;
	void setActive(bool arg);
	bool active;
	sf::Vector2f pos;
	std::string placeholder;
};