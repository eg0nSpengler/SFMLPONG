#pragma once
#include <memory>
#include <iostream>
#include <cmath>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Actor.h"
class Engine
{
public:
	Engine(int windowWidth, int windowHeight);
	~Engine();
	void Handle_Input(sf::Time deltaTime);
	bool Handle_Collisons(Actor actA, Actor actB);
	void AIUpdate();
	void Update(sf::Time deltaTime);
	void ResetBall();
	void ResetGame();
	void Render();
	void Run();
private:
	const int windowWidth = 0;
	const int windowHeight = 0;
	int pScore = 0;
	int p2Score = 0;
	const float paddleSpeed = 600.0f;
	const float ballSpeed = 300.0f;
	const float pi = 3.14159f;
	float rightPaddleSpeed = 0.0f;
	float ballRadius = 10.0f;
	float ballAngle = 0.0f;
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time dTime;
	sf::Time dTimeSinceStart;
	sf::Font font;
	sf::Text playerScore;
	sf::Text aiScore;
	sf::Text toolTip;
	Actor player;
	Actor aiPaddle;
	Actor topBounds;
	Actor bottomBounds;
	Actor rightBounds;
	Actor leftBounds;
	Actor net;
	Actor ball;
	
};

