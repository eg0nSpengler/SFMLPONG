
#include "Paddle.h"


Paddle::Paddle(float x, float y)
{
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(PADDLE_SIZE_X, PADDLE_SIZE_Y));
	rect.setFillColor(sf::Color::White);
}
