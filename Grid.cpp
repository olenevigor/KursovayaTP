#include "Grid.h"

Grid::Grid(int Size) : activeCell(NULL), cellSize(48), filled(0)
{
	// Загрузка шрифта
	font.loadFromFile("Roboto-Medium.ttf");

	// Создание поля
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

	// Всё поле вписывается в размер 336х336
	// Соответственно вычисляем размер одной клетки
	cellSize = 336 / Size;
	size = Size;

	// Здесь можно вызвать очищение памяти, выделенной динамически
	// Но функция initGrid вызывается 1 раз за сцену
	// Поэтому это не требуется

	// Динамическое выделение памяти под клетки (строки)
	cells = new Cell*[size];

	for (int i = 0; i < size; i++)
	{
		// Динамическое выделение памяти под клетки (столбцы)
		cells[i] = new Cell[size];

		for (int j = 0; j < size; j++)
		{
			// Настройка клетки
			cells[i][j].setFont(font);
			cells[i][j].setSize(cellSize);
			cells[i][j].setPosition(position.x + j * cellSize + j * GUI_CELL_OUTLINE_THICKNESS, 
				position.y + i * cellSize + i * GUI_CELL_OUTLINE_THICKNESS);
		}
	}

	// Настройка фонового прямоугольника
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
	// Используем globalBounds вместо getSize, чтобы учесть аутлайн
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

// Функция для проверки конца игры
bool Grid::checkWin(int& evens, int& odds)
{
	if (filled < size * size) return false;

	evens = 0;
	odds = 0;

	int tmp;

	// Считаем четные и нечетные суммы в строках
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

	// Считаем четные и нечетные суммы в столбцах
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

	// Считаем сумму в главной диагонале
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

	// Считаем сумму в побочной диагонале
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
	// Проверка на движение мыши
	if (ev.type == sf::Event::MouseMoved)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::FloatRect bounds = outlineRect.getGlobalBounds();
		if (bounds.contains(sf::Vector2f(mousePosition.x, mousePosition.y)))
		{
			mousePosition.x -= position.x;
			mousePosition.y -= position.y;

			// Определяем, на какую клетку наведена мышь
			row = mousePosition.y / (cellSize + GUI_CELL_OUTLINE_THICKNESS);
			col = mousePosition.x / (cellSize + GUI_CELL_OUTLINE_THICKNESS);

			// Получаем указатель на эту клетку
			Cell* cell = &cells[row][col];
			if (activeCell != cell)
			{
				// Если была активна другая клетка, снимаем с неё выделение
				if (activeCell != NULL)
				{
					activeCell->setActive(false);
				}

				// Если клетка уже занята значением, она не можем быть выделена
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
			// Если новой клетки нет, а старая не выделена, снимаем с неё выделение
			activeCell->setActive(false);
			activeCell = NULL;
		}
	}
	// Проверка на нажатие кнопки мыши
	else if (ev.type == sf::Event::MouseButtonPressed)
	{
		if (activeCell != NULL)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::FloatRect bounds = outlineRect.getGlobalBounds();

			mousePosition.x -= position.x;
			mousePosition.y -= position.y;

			// Инициализируем ссылки row и col для получения значений за пределами функции
			row = mousePosition.y / (cellSize + GUI_CELL_OUTLINE_THICKNESS);
			col = mousePosition.x / (cellSize + GUI_CELL_OUTLINE_THICKNESS);

			// Ставим 1 или 0 взависимости от нажатой кнопки мыши
			if (ev.mouseButton.button == sf::Mouse::Left)
			{
				activeCell->setValue('1');
				activeCell->setActive(false);
				activeCell = NULL;
				filled++;
				return 1; // Говорим о том, что поставили 1
			}
			else if(ev.mouseButton.button == sf::Mouse::Right)
			{
				activeCell->setValue('0');
				activeCell->setActive(false);
				activeCell = NULL;
				filled++;
				return 0; // Говорим о том, что поставили 0
			}
		}
	}

	return -1; // Поле не менялось
}

void Grid::render(sf::RenderWindow& window) const
{
	// Отрисовка фонового прямоугольника
	window.draw(outlineRect);

	// Отрисовка каждой клетки
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cells[i][j].render(window);
		}
	}
}