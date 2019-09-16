#include "Engine.h"

Engine::Engine(int windowWidth, int windowHeight) :
	window(sf::VideoMode(windowWidth, windowHeight), "Pong"),
	player(sf::Vector2f(20.0f, 60.f), sf::Color::White, 2.0f, sf::Vector2f(30.0f, windowHeight / 2)),
	aiPaddle(sf::Vector2f(20.f, 60.0f), sf::Color::White, 2.0f, sf::Vector2f(250.0f, windowHeight / 2)),
	topBounds(sf::Vector2f(windowWidth, 0.0f), sf::Color::Green, 2.0f, sf::Vector2f(0.0f, 0.0f)),
	bottomBounds(sf::Vector2f(windowWidth, 0.0f), sf::Color::Green, 2.0f, sf::Vector2f(0.0f, windowWidth)),
	rightBounds(sf::Vector2f(0.0f, windowHeight), sf::Color::Green, 2.0f, sf::Vector2f(windowWidth, 0.0f)),
	leftBounds(sf::Vector2f(0.0f, windowHeight), sf::Color::Green, 2.0f, sf::Vector2f(0.0f, 0.0f)),
	net(sf::Vector2f(0.0, windowHeight), sf::Color::White, 1.0f, sf::Vector2f(windowWidth / 2, 0.0f)),
	ball(sf::Vector2f(5.0f, 5.0f), sf::Color::White, 2.0f, sf::Vector2f(windowWidth / 2, windowHeight / 2))
{
	std::cout << "Engine object constructed!" << std::endl;
	dx = player.rect.getPosition().x;
	dy = player.rect.getPosition().y;
	balldx = ball.rect.getPosition().x;	//ball.rect.getPosition().x;
	balldy = ball.rect.getPosition().y;//ball.rect.getPosition().y;
	gm = STATE_PLAY;
	dir = EAST;
	dTime = sf::seconds(1.0f / 60.0f);
	dTimeSinceStart = sf::Time::Zero;
	playerVel = 10.0f;
}

Engine::~Engine()
{
	std::cout << "Engine object deleted!" << std::endl;
}

void Engine::Handle_Events()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		window.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{	
		dy--;
		player.rect.setPosition(dx, dy);
		std::cout << dy << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		dy++;
		player.rect.setPosition(dx, dy);
		std::cout << dy << std::endl;
	}
}


bool Engine::Handle_Collisions(Actor actA, Actor actB)
{                 
	if (actA.rect.getGlobalBounds().intersects(actB.rect.getGlobalBounds()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Engine::IsAtPoint(Actor actA, Actor actB)
{
	auto rectBottom = actB.rect.getGlobalBounds().height;
	auto rectMid = rectBottom - 20;
	auto rectTop = rectMid - 20;
	if (actA.rect.getGlobalBounds().contains(0.0f, rectBottom))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Engine::BallUpdate()
{
	if (gm == STATE_PLAY)
	{
		switch (dir)
		{
		case CENTER:
		{
			ball.rect.setFillColor(sf::Color::Black);
			ball.rect.setOutlineColor(sf::Color::Black);
			balldx--;
			ball.rect.setPosition(balldx, balldy);
			if (ball.rect.getPosition().x == net.rect.getPosition().x)
			{
				ball.rect.setFillColor(sf::Color::White);
				ball.rect.setOutlineColor(sf::Color::White);
				dir = BALL_DIR(rand() % 3);
			}
			break;
		}
		case NORTH:
		{
			balldy--;
			ball.rect.setPosition(balldx, balldy);
			if (Handle_Collisions(ball, topBounds) == true)
			{
				dir = SOUTH;
			}
			break;
		}

		case NORTHWEST:
		{
			balldx--;
			balldy--;
			ball.rect.setPosition(balldx, balldy);
			if (Handle_Collisions(ball, topBounds) == true)
			{
				dir = BALL_DIR(SOUTHWEST || SOUTHEAST);
			}
			break;
		}

		case NORTHEAST:
		{
			balldx++;
			balldy--;
			ball.rect.setPosition(balldx, balldy);
			if (Handle_Collisions(ball, topBounds) == true)
			{
				dir = SOUTHWEST;
			}
			break;
		}
		case SOUTH:
		{
			balldy++;
			ball.rect.setPosition(balldx, balldy);
			if (Handle_Collisions(ball, bottomBounds) == true)
			{
				dir = NORTH;
			}
			break;
		}

		case SOUTHWEST:
		{
			balldx--;
			balldy++;
			ball.rect.setPosition(balldx, balldy);
			if (Handle_Collisions(ball, bottomBounds) == true)
			{
				dir = NORTHEAST;
			}
			break;
		}

		case SOUTHEAST:
		{
			balldx++;
			balldy++;
			ball.rect.setPosition(balldx, balldy);
			if(Handle_Collisions(ball, bottomBounds) == true)
			{
				dir = NORTHWEST;
			}
			break;
		}
		case EAST:
		{
			balldx++;
			ball.rect.setPosition(balldx, balldy);
			if (Handle_Collisions(ball, rightBounds) || Handle_Collisions(ball, aiPaddle) == true)
			{
				dir = WEST;
			}
			break;
		}

		case WEST:
		{
			balldx--;
			ball.rect.setPosition(balldx, balldy);
			if (Handle_Collisions(ball, leftBounds) || Handle_Collisions(ball, player) == true)
			{
				if (IsAtPoint(ball, player) == true)
				{
					dir = SOUTHEAST;
				}
			}
			break;
		}
		default:
		{
			break;
		}
		}	
	}
}

void Engine::AIUpdate()
{

}

void Engine::Update()
{
	BallUpdate();
}

void Engine::Render()
{
	window.clear(sf::Color::Black);
	window.draw(player.rect);
	window.draw(aiPaddle.rect);
	window.draw(topBounds.rect);
	window.draw(bottomBounds.rect);
	window.draw(rightBounds.rect);
	window.draw(leftBounds.rect);
	window.draw(net.rect);
	window.draw(ball.rect);
	window.display(); 
	
}

void Engine::Run()
{
	while (window.isOpen())
	{
		while (dTimeSinceStart > dTime)
		{	
		dTimeSinceStart -= dTime;
		Handle_Events();
		Update();
		}
		Render();
		dTimeSinceStart += clock.restart();
	}
}
