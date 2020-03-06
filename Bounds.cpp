
#include "Bounds.h"

Bounds::Bounds(float x, float y, float width, float height)
{
	rect.setPosition(x, y);
	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color::White);
}
