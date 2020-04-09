#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameDefs.h"
class Paddle
{
public:
	Paddle() = default;
	Paddle(float x, float y);

public:
	sf::RectangleShape rect;

private:
	const float paddleVelocity = PADDLE_SPEED;
};

