
#include "Ball.h"

Ball::Ball(float x, float y)
{
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(8.0f, 8.0f));
	rect.setFillColor(sf::Color::White);
}

void Ball::Update()
{
	
}
