#pragma once
#include <memory>
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Actor.h"
class Engine
{
public:
	Engine(int windowWidth, int windowHeight);
	~Engine();

	void Handle_Events();
	bool Handle_Collisions(Actor actA, Actor actB);
	bool IsAtPoint(Actor actA, Actor actB);
	void BallUpdate();
	void AIUpdate();
	void Update();
	void Render();
	void Run();

private:

	enum GAMESTATE
	{
		STATE_RESET,
		STATE_PLAY
	};
	enum BALL_DIR
	{
		CENTER,
		NORTH,
		NORTHEAST,
		EAST,
		SOUTHEAST,
		SOUTH,
		SOUTHWEST,
		WEST,
		NORTHWEST
	};
	GAMESTATE gm;
	BALL_DIR dir;
	int windowWidth;
	int windowHeight;
	float dx;
	float dy;
	float balldx;
	float balldy;
	float playerVel;
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time dTime;
	sf::Time dTimeSinceStart;
	Actor player;
	Actor aiPaddle;
	Actor topBounds;
	Actor bottomBounds;
	Actor rightBounds;
	Actor leftBounds;
	Actor net;
	Actor ball;

};

