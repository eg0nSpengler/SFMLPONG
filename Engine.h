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
	void Handle_Collisions();
	void BallUpdate()
	{
		
		if (gm == STATE_PLAY)
		{
			switch (dir)
			{
			case CENTER:
				{
					ball.rect.setPosition(windowWidth / 2, windowHeight / 2);
					break;
				}
			case NORTH:
				{
					balldy--;
					ball.rect.setPosition(balldx, balldy);
					if (ball.rect.getGlobalBounds().intersects(topBounds.rect.getGlobalBounds()))
					{
						balldy++;
						dir = SOUTH;
					}
					break;
				}
			case SOUTH:
				{
					balldy++;
					ball.rect.setPosition(balldx, balldy);
					if (ball.rect.getGlobalBounds().intersects(bottomBounds.rect.getGlobalBounds()))
					{
						balldy--;
						dir = NORTH;
					}
					break;
				}
			default:
				{
					break;
				}
			}
		}
	};
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
	Actor topBounds;
	Actor bottomBounds;
	Actor rightBounds;
	Actor leftBounds;
	Actor net;
	Actor ball;

};

