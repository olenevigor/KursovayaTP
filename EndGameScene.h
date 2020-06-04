#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Button.h"

// ����� ���������� ���� � ��������� �����
class EndGameScene final : public Scene
{
public:
	// � ����������� ��������� ���������� ������ ���� � ��������
	EndGameScene(int Evens, int Odds);
	void init() override;
	void update() override;
	void draw() override;
private:
	sf::Font font; // �����
	sf::Text winText; // ����� � ����������
	sf::Text evenNumbersText; // ����� � ���������� ������ ����
	sf::Text oddsNumbersText; // ����� � ���������� �������� ����
	Button backButton; // ������ ���������� �����

	int evens; // ���������� ������ ����
	int odds; // ���������� �������� ����
};