#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "Button.h"
#include "TextField.h"

// ����� �������� ���������/�������������� ����
class NewGameScene final : public Scene
{
public:
	NewGameScene();
	void init() override;
	void update() override;
	void draw() override;
private:
	sf::Font font; // �����
	sf::Text sizeText; // ����� ������� ����
	sf::Text portText; // ����� �����
	TextField sizeTextField; // ��������� ���� ��� ����� ������� ����
	TextField portTextField; // ��������� ���� ��� ����� �����
	Button playButton; // ������ ������ ������� ����
	Button serverButton; // ������ ������� ������
	Button backButton; // ������ ����������� � ����
};