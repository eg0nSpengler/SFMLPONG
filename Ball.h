#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
public:
	Ball() = default;
	Ball(float x, float y);
	void Reset(const sf::RenderWindow& window);

public:
	sf::RectangleShape rect;

};

