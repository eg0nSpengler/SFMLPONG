#pragma once
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Paddle.h"
class Engine
{
public:
	Engine(int windowWidth, int windowHeight);
	~Engine();

	void Handle_Events();
	void Update();
	void Render();
	void Run();

private:
	enum ball_dir
	{
		WEST,
		EAST
	};
	int windowWidth;
	int windowHeight;
	float dx;
	float dy;
	float balldx;
	float balldy;
	sf::RenderWindow window;
	Paddle player;
	sf::RectangleShape topBounds;
	sf::RectangleShape bottomBounds;
	sf::RectangleShape rightBounds;
	sf::RectangleShape leftBounds;
	sf::RectangleShape ball;

};

