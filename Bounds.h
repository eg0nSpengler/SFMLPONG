#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameDefs.h"
class Bounds
{
public:
	Bounds(float x, float y, float width, float height);

public:
	sf::RectangleShape rect;
};

