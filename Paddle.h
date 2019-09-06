#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Paddle
{
	Paddle() = default;
	~Paddle();


private:
	sf::RectangleShape paddle;
	sf::Vector2f size;
	sf::Color col;
	float thickness;
	sf::Vector2f pos;


};

