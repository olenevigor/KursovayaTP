#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Button.h"

// ����� ������� ����
class OfflinePlayScene final : public Scene
{
public:
	OfflinePlayScene(int gridSize);
	void init() override;
	void update() override;
	void draw() override;
private:
	Grid grid; // ������� ����
	sf::Font font; // �����
	sf::Text turnText; // ����� �������� ������
	bool player1Turn; // ������� �����
	Button backButton; // ������ ����������� � ����
};