#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
class Actor
{
public:
	Actor();
	Actor(sf::Vector2f size, sf::Color col, float thick, sf::Vector2f pos);
	sf::RectangleShape rect;
private:
	sf::Vector2f size;
	sf::Color col;
	float thick;
	sf::Vector2f pos;


};

