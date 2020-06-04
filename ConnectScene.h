#pragma once

#include "Scene.h"
#include "SceneManager.h"
#include "OnlinePlayScene.h"
#include "Button.h"
#include "TextField.h"

// ����� ����������� � ������� � ������ ip � �����
class ConnectScene : public Scene
{
public:
	ConnectScene();
	void init() override;
	void update() override;
	void draw() override;
private:
	TextField addressField; // ��������� ���� ��� ����� ��-������
	TextField portField; // ��������� ���� ��� ����� �����
	Button connectButton; // ������ ��� ����������� � �������
	Button backButton; // ������ ����������� � ����
	sf::Font font; // �����
};