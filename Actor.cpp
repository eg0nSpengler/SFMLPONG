#include "Actor.h"
Actor::Actor()
{

}
Actor::Actor(sf::Vector2f size, sf::Color col, float thick, sf::Vector2f pos) : size(size), col(col), thick(thick), pos(pos)
{
	rect.setSize(size);
	rect.setOutlineColor(col);
	rect.setOutlineThickness(thick);
	rect.setPosition(pos);
}

