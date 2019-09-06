#pragma once
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Actor.h"
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
	Actor player;
	Actor topBounds;
	Actor bottomBounds;
	Actor rightBounds;
	Actor leftBounds;
	Actor ball;

};

