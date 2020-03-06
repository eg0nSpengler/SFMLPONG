#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameDefs.h"
class Ball
{
public:
	Ball(float x, float y);
	void Update();
public:
	sf::RectangleShape rect;
};

