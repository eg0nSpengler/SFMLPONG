#include "Engine.h"

Engine::Engine(int windowWidth, int windowHeight) : window(sf::VideoMode(windowWidth, windowHeight), "Pong"), topBounds(), bottomBounds(), rightBounds(), leftBounds(), ball()
{
	std::cout << "Engine object constructed!" << std::endl;

	/*rectOne.setSize(sf::Vector2f(20.0f, 90.0f));
	rectOne.setOutlineColor(sf::Color::White);
	rectOne.setOutlineThickness(2.0f);
	rectOne.setPosition(sf::Vector2f(30.0f, windowHeight / 2));*/
	topBounds.setSize(sf::Vector2f(windowWidth, 0.0f));
	topBounds.setOutlineColor(sf::Color::Green);
	topBounds.setOutlineThickness(2.0f);
	topBounds.setPosition(sf::Vector2f(0.0f, 0.0f));
	bottomBounds.setSize(sf::Vector2f(windowWidth, 0.0f));
	bottomBounds.setOutlineColor(sf::Color::Green);
	bottomBounds.setOutlineThickness(2.0f);
	bottomBounds.setPosition(sf::Vector2f(0.0f, 480));
	rightBounds.setSize(sf::Vector2f(0.0f, windowHeight));
	rightBounds.setOutlineColor(sf::Color::Green);
	rightBounds.setOutlineThickness(2.0f);
	rightBounds.setPosition(sf::Vector2f(windowWidth, 0.0f));
	leftBounds.setSize(sf::Vector2f(0.0f, windowHeight));
	leftBounds.setOutlineColor(sf::Color::Green);
	leftBounds.setOutlineThickness(2.0f);
	leftBounds.setPosition(sf::Vector2f(0.0f, 0.0f));
	ball.setSize(sf::Vector2f(5.0f, 5.0f));
	ball.setOutlineColor(sf::Color::White);
	ball.setOutlineThickness(2.0f);
	ball.setPosition(sf::Vector2f(windowWidth / 2, windowHeight / 2));
	dx = rectOne.getPosition().x;
	dy = rectOne.getPosition().y;
	balldx = ball.getPosition().x;
	balldy = ball.getPosition().y;
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
		if (rectOne.getGlobalBounds().top)
		{
		dy--;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (rectOne.getGlobalBounds().intersects(bottomBounds.getGlobalBounds()))
		{
			dy--;
		}
		dy++;
	}
}

void Engine::Update()
{
	rectOne.setPosition(dx, dy);
}

void Engine::Render()
{
	window.clear(sf::Color::Black);
	window.draw(rectOne);
	window.draw(topBounds);
	window.draw(bottomBounds);
	window.draw(rightBounds);
	window.draw(leftBounds);
	window.draw(ball);
	window.display(); 
	
}

void Engine::Run()
{
	while (window.isOpen())
	{
	Handle_Events();
	Update();
	Render();
	}
}
