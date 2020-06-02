#pragma once

#include <stack>

#include "Scene.h"

class Scene;

// ��� ��������� ���� ����������� ������� Singleton �������
class SceneManager
{
private:
	// ��������� ������������ ��� ��������
	SceneManager();
	SceneManager(const SceneManager&);
	SceneManager& operator=(SceneManager&);

	std::stack<std::unique_ptr<Scene>> scenes;

	bool resume;
	bool isRunning;
	bool isClosing;

	std::unique_ptr<Scene> next;
public:
	// ����������� ������� ��� ��������
	static SceneManager& getInstance() {
		static SceneManager instance;
		return instance;
	}

	void run(std::unique_ptr<Scene> scene); // ��������� ��������� �����

	void loadScene(std::unique_ptr<Scene> scene, bool replace = false); // ��������� ����� �����
	void closeScene(); // ������� ������� �����

	void nextState(); // ���������� ��������� ���� (�������/������� �����)
	void update(); // ���������� ������� �����
	void draw(); // ��������� ������� �����

	bool running() const;
	void quit();
};