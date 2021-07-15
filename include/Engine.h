#pragma once
#include <memory>
#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameDefs.h"
#include "Paddle.h"
#include "Ball.h"
#include "TextElement.h"

class Engine
{

	enum class SCOREBOUND
	{
		LEFT,
		RIGHT
	};

	struct Bound
	{
		Bound(float x, float y, float width, float height)
		{
			rect.setPosition(x, y);
			rect.setSize(sf::Vector2f(width, height));
			rect.setFillColor(sf::Color::Transparent);
		}
		sf::RectangleShape rect;
	};

public:
	Engine();
	~Engine();
	void HandleInput(const sf::Time& deltaTime);
	void Update(const sf::Time& deltaTime);
	void GameReset();
	void GameEnd();
	void Render();
	void Run();
	void HandleCollisons();
	void CheckScore();
	void UpdateScore(Engine::SCOREBOUND bound);
	bool CheckCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB);

private:
	unsigned int leftScore;
	unsigned int rightScore;
	unsigned int maxScore;
	bool IsGameRunning;
	float windowWidthFP; /*Window Width casted to float*/
	float windowHeightFP; /*Window Height casted to float*/
	float ballAngle;

private:
	sf::RenderWindow window;
	sf::Font font;
	sf::Clock clock;
	sf::Time dTime;
	sf::Time dTimeSinceStart;
	sf::String leftScoreString;
	sf::String rightScoreString;

private:
	std::shared_ptr<Paddle> player1;
	std::shared_ptr<Paddle> player2;
	std::shared_ptr<Ball> ball;
	std::shared_ptr<Bound> topBound;
	std::shared_ptr<Bound> bottomBound;
	std::shared_ptr<Bound> leftBound;
	std::shared_ptr<Bound> rightBound;

	std::vector<std::shared_ptr<TextElement>> textElems;
};

