#include "Grid.h"

Grid::Grid(int Size) : activeCell(NULL), cellSize(48), filled(0)
{
	// �������� ������
	font.loadFromFile("Roboto-Medium.ttf");

	// �������� ����
	initGrid(Size);
}

Grid::~Grid()
{
	for (int i = 0; i < size; i++)
	{
		delete[] cells[i];
	}
	delete[] cells;
}

void Grid::initGrid(int Size)
{
	constexpr int minimum_size = 1;
	if (Size < minimum_size) return;

	// �� ���� ����������� � ������ 336�336
	// �������������� ��������� ������ ����� ������
	cellSize = 336 / Size;
	size = Size;

	// ����� ����� ������� �������� ������, ���������� �����������
	// �� ������� initGrid ���������� 1 ��� �� �����
	// ������� ��� �� ���������

	// ������������ ��������� ������ ��� ������ (������)
	cells = new Cell*[size];

	for (int i = 0; i < size; i++)
	{
		// ������������ ��������� ������ ��� ������ (�������)
		cells[i] = new Cell[size];

		for (int j = 0; j < size; j++)
		{
			// ��������� ������
			cells[i][j].setFont(font);
			cells[i][j].setSize(cellSize);
			cells[i][j].setPosition(position.x + j * cellSize + j * GUI_CELL_OUTLINE_THICKNESS, 
				position.y + i * cellSize + i * GUI_CELL_OUTLINE_THICKNESS);
		}
	}

	// ��������� �������� ��������������
	outlineRect.setFillColor(GUI_GRID_FILL_COLOR);
	outlineRect.setSize(sf::Vector2f(size * (cellSize + GUI_CELL_OUTLINE_THICKNESS), 
		size * (cellSize + GUI_CELL_OUTLINE_THICKNESS)));
	outlineRect.setPosition(position.x - GUI_CELL_OUTLINE_THICKNESS, position.y - GUI_CELL_OUTLINE_THICKNESS);
	outlineRect.setOutlineThickness(GUI_CELL_OUTLINE_THICKNESS);
	outlineRect.setOutlineColor(GUI_GRID_OUTLINE_COLOR);
}

void Grid::setCell(int row, int col, char val)
{
	if (row < 0 || col < 0 || row >= size || col >= size)
	{
		return;
	}

	cells[row][col].setValue(val);
	filled++;
}

sf::Vector2f Grid::getSize() const
{
	// ���������� globalBounds ������ getSize, ����� ������ �������
	sf::FloatRect bounds = outlineRect.getGlobalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

int Grid::getGridSize() const
{
	return size;
}

void Grid::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cells[i][j].setPosition(position.x + j * cellSize + j * GUI_CELL_OUTLINE_THICKNESS, 
				position.y + i * cellSize + i * GUI_CELL_OUTLINE_THICKNESS);
		}
	}

	outlineRect.setPosition(position.x - GUI_CELL_OUTLINE_THICKNESS, position.y - GUI_CELL_OUTLINE_THICKNESS);
}

// ������� ��� �������� ����� ����
bool Grid::checkWin(int& evens, int& odds)
{
	if (filled < size * size) return false;

	evens = 0;
	odds = 0;

	int tmp;

	// ������� ������ � �������� ����� � �������
	for (int i = 0; i < size; i++)
	{
		tmp = 0;
		for (int j = 0; j < size; j++)
		{
			tmp += cells[i][j].getValue() - '0';
		}

		if (tmp % 2 == 0)
		{
			evens++;
		}
		else
		{
			odds++;
		}
	}

	// ������� ������ � �������� ����� � ��������
	for (int i = 0; i < size; i++)
	{
		tmp = 0;
		for (int j = 0; j < size; j++)
		{
			tmp += cells[j][i].getValue() - '0';
		}

		if (tmp % 2 == 0)
		{
			evens++;
		}
		else
		{
			odds++;
		}
	}

	// ������� ����� � ������� ���������
	tmp = 0;
	for (int i = 0; i < size; i++)
	{
		tmp += cells[i][i].getValue() - '0';
	}

	if (tmp % 2 == 0)
	{
		evens++;
	}
	else
	{
		odds++;
	}

	// ������� ����� � �������� ���������
	tmp = 0;
	for (int i = 0; i < size; i++)
	{
		tmp += cells[i][size - i - 1].getValue() - '0';
	}

	if (tmp % 2 == 0)
	{
		evens++;
	}
	else
	{
		odds++;
	}

	return true;
}

int Grid::input(sf::Event ev, sf::RenderWindow& window, int& row, int& col)
{
	// �������� �� �������� ����
	if (ev.type == sf::Event::MouseMoved)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = outlineRect.getGlobalBounds();
		if (bounds.contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
		{
			mousePosition.x -= position.x;
			mousePosition.y -= position.y;

			// ����������, �� ����� ������ �������� ����
			row = mousePosition.y / (cellSize + GUI_CELL_OUTLINE_THICKNESS);
			col = mousePosition.x / (cellSize + GUI_CELL_OUTLINE_THICKNESS);

			// �������� ��������� �� ��� ������
			Cell* cell = &cells[row][col];
			if (activeCell != cell)
			{
				// ���� ���� ������� ������ ������, ������� � �� ���������
				if (activeCell != NULL)
				{
					activeCell->setActive(false);
				}

				// ���� ������ ��� ������ ���������, ��� �� ����� ���� ��������
				if (cell->getValue() == 0)
				{
					activeCell = cell;
					activeCell->setActive(true);
				}
				else
				{
					activeCell = NULL;
				}
			}
		}
		else if (activeCell != NULL)
		{
			// ���� ����� ������ ���, � ������ �� ��������, ������� � �� ���������
			activeCell->setActive(false);
			activeCell = NULL;
		}
	}
	// �������� �� ������� ������ ����
	else if (ev.type == sf::Event::MouseButtonPressed)
	{
		if (activeCell != NULL)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::FloatRect bounds = outlineRect.getGlobalBounds();

			mousePosition.x -= position.x;
			mousePosition.y -= position.y;

			// �������������� ������ row � col ��� ��������� �������� �� ��������� �������
			row = mousePosition.y / (cellSize + GUI_CELL_OUTLINE_THICKNESS);
			col = mousePosition.x / (cellSize + GUI_CELL_OUTLINE_THICKNESS);

			// ������ 1 ��� 0 ������������ �� ������� ������ ����
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				activeCell->setValue('1');
				activeCell->setActive(false);
				activeCell = NULL;
				filled++;
				return 1; // ������� � ���, ��� ��������� 1
			}
			else if(ev.mouseButton.button == sf::Mouse::Right)
			{
				activeCell->setValue('0');
				activeCell->setActive(false);
				activeCell = NULL;
				filled++;
				return 0; // ������� � ���, ��� ��������� 0
			}
		}
	}

	return -1; // ���� �� ��������
}

void Grid::render(sf::RenderWindow& window) const
{
	// ��������� �������� ��������������
	window.draw(outlineRect);

	// ��������� ������ ������
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cells[i][j].render(window);
		}
	}
}