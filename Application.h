#pragma once

#include "SceneManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

class SceneManager;

// �������� ����� ����������
class Application
{
public:
	void run(); // ������ ����������

	static sf::RenderWindow window; // ��������� ���������� ��� �������� ����, � ������� �������������� ����
};