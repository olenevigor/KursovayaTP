#include "Cell.h"

Cell::Cell()
{
	isActive = false;
	value = 0;
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(GUI_CELL_OUTLINE_COLOR);
	rect.setOutlineThickness(GUI_CELL_OUTLINE_THICKNESS);
}

void Cell::setFont(sf::Font& font)
{
	text.setFont(font);
}

void Cell::setValue(char Value)
{
	value = Value;
	text.setString(value);

	// Текст выравнивается по центру клетки
	text.setPosition(position.x + rect.getSize().x / 2 - text.getLocalBounds().width / 2,
		position.y - rect.getSize().y / 2 + text.getLocalBounds().height / 2);
}

char Cell::getValue() const
{
	return value;
}

void Cell::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	rect.setPosition(x, y);

	// Текст выравнивается по центру клетки
	text.setPosition(x + rect.getSize().x / 2 - text.getLocalBounds().width / 2,
		y - rect.getSize().y / 2 + text.getLocalBounds().height / 2);
}

void Cell::setSize(int size)
{
	size -= GUI_CELL_OUTLINE_THICKNESS;
	rect.setSize(sf::Vector2f(size, size));
	text.setCharacterSize(size);
}

int Cell::getSize() const
{
	return rect.getGlobalBounds().width;
}

void Cell::setActive(bool active)
{
	if (!isActive && active)
	{
		rect.setFillColor(sf::Color(117, 221, 221, 255));
	}
	else if (isActive && !active)
	{
		rect.setFillColor(sf::Color::Transparent);
	}

	isActive = active;
}

void Cell::render(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(text);
}