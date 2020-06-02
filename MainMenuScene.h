#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Button.h"

// ����� �������� ����
class MainMenuScene final : public Scene
{
public:
	MainMenuScene();
	void init() override;
	void update() override;
	void draw() override;
private:
	Button newGameButton; // ������ ����� ����
	Button connectButton; // ������ �����������
	Button exitButton; // ������ ������
	sf::Font font; // �����
};