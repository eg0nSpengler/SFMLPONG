#pragma once
#include <memory>
#include <iostream>
#include <cmath>
#include <string.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameDefs.h"
#include "Paddle.h"
#include "Ball.h"
#include "Bounds.h"
#include "TextElement.h"

enum BOUNDS
{
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

class Engine
{
public:
	Engine();
	~Engine();
	void Handle_Input(const sf::Time& deltaTime);
	void AIUpdate();
	void Update(const sf::Time& deltaTime);
	void ResetBall();
	void ResetGame();
	void Render();
	void Run();
	bool Handle_Collisons(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB);

private:
	const int windowWidth = WINDOW_WIDTH;
	const int windowHeight = WINDOW_HEIGHT;
	int pScore = 0;
	int p2Score = 0;
	float rightPaddleSpeed = 0.0f;
	float ballAngle = 0.0f;

private:
	sf::RenderWindow window;
	sf::Font font;
	sf::Clock clock;
	sf::Time dTime;
	sf::Time dTimeSinceStart;

private:
	std::vector<std::shared_ptr<sf::RectangleShape>> rectShapes;
	std::shared_ptr<std::vector<TextElement>> textElems;
	std::shared_ptr<Paddle> player1;
	std::shared_ptr<Paddle> player2;
	std::shared_ptr<Ball> ball;
	std::shared_ptr<Bounds> topBounds;
	std::shared_ptr<Bounds> bottomBounds;
	std::shared_ptr<Bounds> leftBounds;
	std::shared_ptr<Bounds> rightBounds;
	TextElement* playerScore;
	TextElement* aiScore;
	TextElement* toolTip1;
	TextElement* toolTip2;
};

