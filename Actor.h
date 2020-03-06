#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameDefs.h"
class Actor
{
public:
	Actor() = default;
	Actor(sf::Vector2f pos);
	static Actor* CreateActor(const sf::Vector2f& pos);
	sf::RectangleShape rect;

private:
	sf::Vector2f pos;


};

