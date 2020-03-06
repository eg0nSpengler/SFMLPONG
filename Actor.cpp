

#include "Actor.h"

Actor::Actor(sf::Vector2f pos) : pos(pos)
{
	rect.setSize(sf::Vector2f(PADDLE_SIZE_X, PADDLE_SIZE_Y));
	rect.setFillColor(sf::Color::White);
	rect.setPosition(pos);
	
}

Actor* Actor::CreateActor(const sf::Vector2f& pos)
{
	return new Actor(pos);
}
