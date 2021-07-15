
#include "Ball.h"

Ball::Ball(float x, float y)
{
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(8.0f, 8.0f));
	rect.setFillColor(sf::Color::White);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);
}


void Ball::Reset(const sf::RenderWindow& window)
{
	auto windowSizeX = static_cast<float>(window.getSize().x);
	auto windowSizeY = static_cast<float>(window.getSize().y);
	rect.setPosition(windowSizeX / 2, windowSizeY/ 2);
}

