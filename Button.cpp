#include "Button.h"

#include <iostream>

Button::Button()
{
	// Стандартные настройки кнопки
	// Применяются в конструкторе, чтобы все кнопки были в одном стиле

	box.setSize(GUI_BUTTON_SIZE);
	box.setFillColor(GUI_BUTTON_FILL_COLOR);
	box.setOutlineThickness(GUI_BUTTON_OUTLINE_THICKNESS);
	box.setOutlineColor(sf::Color::Transparent);

	text.setFillColor(sf::Color::White);

	buttonState = state::normal;
}

void Button::setPosition(float x, float y)
{
	box.setPosition(x, y);

	// Текст выравнивается по центру прямоугольника
	text.setPosition(x + box.getSize().x / 2 - text.getLocalBounds().width / 2,
		y + box.getSize().y / 2 - text.getLocalBounds().height / 2);
}

void Button::setText(const std::string& str)
{
	text.setString(str);
}

void Button::render(sf::RenderWindow& window)
{
	window.draw(box);
	window.draw(text);
}

void Button::setFont(const sf::Font& font)
{
	text.setFont(font);
}

sf::Vector2f Button::getSize() const
{
	return box.getSize();
}

sf::Uint32 Button::getState() const
{
	return buttonState;
}

void Button::input(sf::Event ev, sf::RenderWindow& window)
{
	if (ev.type == sf::Event::MouseMoved)
	{
		// Проверка находится ли мышь над кнопкой
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		if (box.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
			buttonState = state::hovered;
			setActive(true);
		}
		else {
			buttonState = state::normal;
			setActive(false);
		}
	}
	else if (buttonState == state::hovered && ev.type == sf::Event::MouseButtonReleased)
	{
		// Проверка на нажатие по кнопке
		buttonState = state::clicked;
	}
}

void Button::setActive(bool arg)
{
	if (arg) {
		box.setOutlineColor(GUI_BUTTON_OUTLINE_COLOR);
	}
	else {
		box.setOutlineColor(sf::Color::Transparent);
	}
}