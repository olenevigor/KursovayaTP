#pragma once

#include <SFML/Graphics.hpp>

#include "Application.h"

class Scene
{
public:
	Scene();
	virtual ~Scene() = default;

	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
protected:
	sf::RenderWindow& window; // окно для отрисовки
};