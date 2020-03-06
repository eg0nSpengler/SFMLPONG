#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameDefs.h"

class Paddle
{
public:
	Paddle(float x, float y);

public:
	sf::RectangleShape rect;
};

