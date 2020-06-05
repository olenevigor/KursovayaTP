#include <string>

#include <SFML/Graphics.hpp>

#include "TextField.h"

TextField::TextField() {
	active = false;
	box.setFillColor(GUI_TEXT_FIELD_FILL_COLOR);
	box.setOutlineColor(sf::Color::Transparent);
	box.setOutlineThickness(GUI_TEXT_FIELD_OUTLINE_THICKNESS);

	renderPlaceholder = false;
	placeholder = "";

	txt.setFillColor(sf::Color::White);

	size = GUI_TEXT_MAX;
	length = 0;
}

void TextField::setPosition(sf::Vector2f vec) {
	box.setPosition(vec);
	txt.setPosition(vec + sf::Vector2f(5, 5));
}

void TextField::input(sf::Event ev) {
	// Проверка на нажатие по текстовому полю
	if (ev.type == sf::Event::MouseButtonReleased) {
		sf::Vector2f pos(ev.mouseButton.x, ev.mouseButton.y);
		if (box.getGlobalBounds().contains(pos)) {
			setActive(true);
		}
		else {
			setActive(false);
		}
	}

	// Проверка на ввод текста при активном текстовом поле
	if (ev.type == sf::Event::TextEntered && active) {
		sf::String str = txt.getString();

		if (ev.text.unicode == GUI_TEXT_BACKSPACE) {
			if (str.getSize() > 0) {
				length--;
				str = str.substring(0, str.getSize() - 1);
			}
		}
		else if (ev.text.unicode == GUI_TEXT_ESCAPE) {
			setActive(false);
		}
		else {
			sf::String sfstr = "";
			sfstr += ev.text.unicode;
			str += sfstr.toAnsiString();
		}

		if (str.getSize() == size) return;

		txt.setString(str);
		length++;
	}
}

void TextField::setFont(sf::Font& f) {
	txt.setFont(f);
	txt.setCharacterSize(24);

	box.setSize(sf::Vector2f((txt.getCharacterSize() * (size / 2 + 1)) + 10, txt.getCharacterSize() + 10));
}

const sf::String& TextField::getText() {
	return txt.getString();
}

void TextField::render(sf::RenderWindow& window) {
	window.draw(box);
	window.draw(txt);
}

void TextField::setActive(bool arg) {
	active = arg;
	if (active) {
		box.setOutlineColor(sf::Color(23, 42, 58, 255));
	}
	else {
		box.setOutlineColor(sf::Color::Transparent);
	}

	if (renderPlaceholder && arg) {
		renderPlaceholder = false;
		txt.setString("");
		txt.setFillColor(sf::Color::Black);
	}
}

void TextField::setPlaceholder(std::string str) {
	placeholder = str;
	renderPlaceholder = true;
	txt.setFillColor(GUI_TEXT_GRAY);
	txt.setString(placeholder);
	setActive(false);
}

void TextField::setLength(int arg) {
	size = arg;

	box.setSize(sf::Vector2f((txt.getCharacterSize() * (size / 2 + 1)) + 10, txt.getCharacterSize() + 10));
}

int TextField::getTextLength() {
	return length;
}

bool TextField::isActive() {
	return active;
}

void TextField::open() {
	setActive(true);
}

void TextField::setText(std::string str)
{
	txt.setString(str);
	length = str.length();
}

sf::Vector2f TextField::getSize() const
{
	return box.getSize();
}