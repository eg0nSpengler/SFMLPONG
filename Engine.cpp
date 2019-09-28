#include "Engine.h"

Engine::Engine(int windowWidth, int windowHeight) :
	window(sf::VideoMode(windowWidth, windowHeight), "Pong"),
	player(sf::Vector2f(20.0f, 60.f), sf::Color::White, 2.0f, sf::Vector2f(80.0f, windowHeight / 2)),
	aiPaddle(sf::Vector2f(20.f, 60.0f), sf::Color::White, 2.0f, sf::Vector2f(560.0f, windowHeight / 2)),
	topBounds(sf::Vector2f(windowWidth, 0.0f), sf::Color::Transparent, 2.0f, sf::Vector2f(0.0f, 0.0f)),
	bottomBounds(sf::Vector2f(windowWidth, 0.0f), sf::Color::Transparent, 2.0f, sf::Vector2f(0.0f, windowHeight)),
	rightBounds(sf::Vector2f(0.0f, windowHeight), sf::Color::Transparent, 2.0f, sf::Vector2f(windowWidth, 0.0f)),
	leftBounds(sf::Vector2f(0.0f, windowHeight), sf::Color::Transparent, 2.0f, sf::Vector2f(0.0f, 0.0f)),
	net(sf::Vector2f(1.0, 10.0f), sf::Color::White, 1.0f, sf::Vector2f(windowWidth / 2, 0.0f)),
	ball(sf::Vector2f(5.0f, 5.0f), sf::Color::White, 2.0f, sf::Vector2f(windowWidth / 2, windowHeight / 2))
{
	std::cout << "Engine object constructed!" << std::endl;
	dTime = sf::seconds(1.0f / 60.0f);
	dTimeSinceStart = sf::Time::Zero;
	ballAngle = (std::rand() % 360) * 2 * pi / 360;
	player.rect.setOrigin(player.rect.getSize().x / 2, player.rect.getSize().y / 2);
	aiPaddle.rect.setOrigin(aiPaddle.rect.getSize().x / 2, aiPaddle.rect.getSize().y / 2);
	ball.rect.setOrigin(ball.rect.getSize().x / 2, ball.rect.getSize().y / 2);
	font.loadFromFile("G:/VSRepos/SFMLPONG/Content/bit5x3.ttf");
	playerScore.setFont(font);
	aiScore.setFont(font);
	toolTip.setFont(font);
	playerScore.setString(std::to_string(pScore));
	playerScore.setCharacterSize(50);
	playerScore.setFillColor(sf::Color::White);
	playerScore.setPosition(window.getSize().x / 2 - 30.0f, 0.0f);
	aiScore.setString(std::to_string(p2Score));
	aiScore.setCharacterSize(50);
	aiScore.setFillColor(sf::Color::White);
	aiScore.setPosition(window.getSize().x / 2 + 10.0f, 0.0f);
	toolTip.setString("Press SPACEBAR to reset the game");
	toolTip.setCharacterSize(15);
	toolTip.setFillColor(sf::Color::Green);
	toolTip.setPosition(0.0f, -2.0f);
}

Engine::~Engine()
{
	std::cout << "Engine object deleted!" << std::endl;
}

void Engine::Handle_Input(sf::Time deltaTime)
{
	sf::Event event;
	while (window.pollEvent(event))
	{

		if (event.key.code == sf::Keyboard::Escape)
		{
			window.close();
		}

		if (event.key.code == sf::Keyboard::Space)
		{
			ResetGame();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (Handle_Collisons(player, topBounds) == false)
		{
			player.rect.move(0.0f, -1.0f * paddleSpeed * deltaTime.asSeconds());
		}
		player.rect.move(0.0f, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (Handle_Collisons(player, bottomBounds) == false)
		{
			player.rect.move(0.0f, 1.0f * paddleSpeed * deltaTime.asSeconds());
		}
		player.rect.move(0.0f, 0.00f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (Handle_Collisons(aiPaddle, topBounds) == false)
		{
			aiPaddle.rect.move(0.0f, -1.0f * paddleSpeed * deltaTime.asSeconds());
		}
		aiPaddle.rect.move(0.0f, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (Handle_Collisons(aiPaddle, bottomBounds) == false)
		{
			aiPaddle.rect.move(0.0f, 1.0f * paddleSpeed * deltaTime.asSeconds());
		}
		aiPaddle.rect.move(0.0f, 0.0f);
	}
}

bool Engine::Handle_Collisons(Actor actA, Actor actB)
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

void Engine::AIUpdate()
{

	aiPaddle.rect.move(0.0f, rightPaddleSpeed);

	if (ball.rect.getPosition().y > aiPaddle.rect.getPosition().y)
	{
		rightPaddleSpeed = paddleSpeed;
	}
	else if(ball.rect.getPosition().y < aiPaddle.rect.getPosition().y)
	{
		rightPaddleSpeed = -paddleSpeed;
	}
	else
	{
		rightPaddleSpeed = 0.0f;
	}
}

void Engine::Update(sf::Time deltaTime)
{
	ball.rect.move(std::cos(ballAngle) * ballSpeed * deltaTime.asSeconds(), std::sin(ballAngle) * ballSpeed * deltaTime.asSeconds());
	if (Handle_Collisons(ball, player) == true)
	{
		ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
	}

	if (Handle_Collisons(ball, aiPaddle) == true)
	{
		ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
	}

	if (Handle_Collisons(ball, topBounds) == true)
	{
		ballAngle = -ballAngle;
	}

	if (Handle_Collisons(ball, bottomBounds) == true)
	{
		ballAngle = ++ballAngle;
	}

	if (Handle_Collisons(ball, leftBounds) == true)
	{
		ResetBall();
		p2Score++;
		aiScore.setString(std::to_string(p2Score));
	}

	if(Handle_Collisons(ball, rightBounds) == true)
	{
		ResetBall();
		pScore++;
		playerScore.setString(std::to_string(pScore));
	}
	
}

void Engine::ResetBall()
{
	ball.rect.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
}

void Engine::ResetGame()
{
	pScore = 0;
	p2Score = 0;
	playerScore.setString(std::to_string(pScore));
	aiScore.setString(std::to_string(p2Score));
	ResetBall();
}

void Engine::Render()
{
	sf::VertexArray net(sf::LineStrip, 2);
	net[0].position = sf::Vector2f(window.getSize().x / 2, 0.0f);
	net[1].position = sf::Vector2f(window.getSize().x / 2, window.getSize().y);
	net[0].color = sf::Color::White;
	net[1].color = sf::Color::White;
	window.clear(sf::Color::Black);
	window.draw(playerScore);
	window.draw(aiScore);
	window.draw(toolTip);
	window.draw(player.rect);
	window.draw(aiPaddle.rect);
	window.draw(topBounds.rect);
	window.draw(bottomBounds.rect);
	window.draw(rightBounds.rect);
	window.draw(leftBounds.rect);
	window.draw(net);
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
			Handle_Input(dTime);
			Update(dTime);
		}
		Render();
		dTimeSinceStart += clock.restart();
	}

}

