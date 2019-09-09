#include "Engine.h"

Engine::Engine(int windowWidth, int windowHeight) :
	window(sf::VideoMode(windowWidth, windowHeight), "Pong"),
	player(sf::Vector2f(20.0f, 60.f), sf::Color::White, 2.0f, sf::Vector2f(30.f, windowHeight / 2)),
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
	dir = NORTH;
	dTime = sf::seconds(1.0f / 60.0f);
	dTimeSinceStart = sf::Time::Zero;
	playerVel = 15.0f;
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
			player.rect.move(0.0f, --playerVel * dTime.asSeconds());
			std::cout << dy << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.rect.move(0.0f, playerVel * dTime.asSeconds());
		std::cout << dy << std::endl;
	}
}


void Engine::Handle_Collisions()
{
	if (player.rect.getGlobalBounds().intersects(topBounds.rect.getGlobalBounds()))
	{
		dy++;
	}

	if (player.rect.getGlobalBounds().intersects(bottomBounds.rect.getGlobalBounds()))
	{
		dy--;
	}                                                
}

void Engine::Update()
{
	BallUpdate();
}

void Engine::Render()
{
	window.clear(sf::Color::Black);
	window.draw(player.rect);
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
