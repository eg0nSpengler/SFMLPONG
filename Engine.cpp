

#include "Engine.h"

Engine::Engine() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong", sf::Style::Close)
{
	std::cout << "Engine object constructed!" << "\n";
	dTime = sf::seconds(1.0f / FRAME_RATE);
	dTimeSinceStart = sf::Time::Zero;
	windowWidthFP = static_cast<float>(WINDOW_WIDTH);
	windowHeightFP = static_cast<float>(WINDOW_HEIGHT);
	auto windowPosX = windowWidthFP / 2;
	auto windowPosY = windowHeightFP / 2;
	font.loadFromFile("Content/bit5x3.ttf");


	IsGameRunning = true;
	leftScore = 0;
	rightScore = 0;
	maxScore = SCORE_MAX;
	ballAngle = (std::rand() % 360) * 2 * (PI / 360);

	leftScoreString = std::to_string(leftScore);
	rightScoreString = std::to_string(rightScore);

	player1 = std::make_shared<Paddle>(80.0f, windowPosY);
	player2 = std::make_shared<Paddle>(560.0f, windowPosY);
	ball = std::make_shared<Ball>(windowPosX, windowPosY);

	topBound = std::make_shared<Bound>(0.0f, 0.0f, windowWidthFP, 4.0f);
	bottomBound = std::make_shared<Bound>(0.0f, windowHeightFP, windowWidthFP, 4.0f);
	leftBound = std::make_shared<Bound>(0.0f, 0.0f, 1.0f, windowHeightFP);
	rightBound = std::make_shared<Bound>(windowWidthFP, 0.0f, 1.0f, windowHeightFP);

	textElems.emplace_back(std::make_shared<TextElement>(font, leftScoreString, sf::Vector2f(windowPosX - 30.0f, 0.0f)));
	textElems.emplace_back(std::make_shared<TextElement>(font, rightScoreString, sf::Vector2f(windowPosX + 10.0f, 0.0f)));
	textElems.emplace_back(std::make_shared<TextElement>(font, sf::Color::Magenta, TEXT_MIN_SIZE, "Press SPACEBAR to reset the game", sf::Vector2f(0.0f, -2.0f)));
	textElems.emplace_back(std::make_shared<TextElement>(font, sf::Color::Cyan, TEXT_MIN_SIZE, "Press Esc/Escape to quit", sf::Vector2f(0.0f, 12.0f)));
	textElems.emplace_back(std::make_shared<TextElement>(font, sf::Color::Green, TEXT_MAX_SIZE, " ", sf::Vector2f(windowPosX, windowPosY)));

}

Engine::~Engine()
{
	std::cout << "Engine object deleted!" << "\n";
}

void Engine::HandleInput(const sf::Time& deltaTime)
{
	sf::Event event;
	
	while (window.pollEvent(event))
	{
		switch (event.key.code)
		{
			case sf::Keyboard::Escape:
			window.close();
			break;

			case sf::Keyboard::Space:
			GameReset();
			break;
		
			default:
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player1->rect.move(0.0f, -1.0f * PADDLE_SPEED * dTime.asSeconds());
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player1->rect.move(0.0f, 1.0f * PADDLE_SPEED * dTime.asSeconds());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player2->rect.move(0.0f, -1.0f * PADDLE_SPEED * dTime.asSeconds());
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player2->rect.move(0.0f, 1.0f * PADDLE_SPEED * dTime.asSeconds());
	}
}

void Engine::Update(const sf::Time& deltaTime)
{
	auto windowPosX = windowWidthFP / 2;
	auto windowPosY = windowHeightFP / 2;
	auto ballPosX = ball->rect.getPosition().x;
	auto ballPosY = ball->rect.getPosition().y;
	auto newBallAngle = PI - ballAngle + (std::rand() % 20) * PI / 180;

	/*This checks to see if the ball has gone out of bounds*/
	/*This check is also done since SFML doesn't have any built in collision detection/resolution outside of checking for intersections*/
	if (ballPosX && ballPosY >= WINDOW_WIDTH)
	{
		ball->rect.setPosition(windowPosX, windowPosY);
	}
	else if (ballPosX && ballPosY <= 0.0f)
	{
		ball->rect.setPosition(windowPosX, windowPosY);
	}


	ball->rect.move(std::cos(ballAngle) * BALL_SPEED * dTime.asSeconds(), std::sin(ballAngle) * BALL_SPEED * dTime.asSeconds());

	if (CheckCollision(ball->rect, player1->rect) == true)
	{
		ball->rect.move(10.0f, 0.0f);
		ballAngle = newBallAngle;
	}

	if (CheckCollision(ball->rect, player2->rect) == true)
	{
		ball->rect.move(-10.0f, 0.0f);
		ballAngle = newBallAngle;
	}

	if (CheckCollision(ball->rect, topBound->rect) == true)
	{
		ballAngle = -ballAngle;
	}

	if (CheckCollision(ball->rect, bottomBound->rect) == true)
	{
		ballAngle = ++ballAngle;
	}

	if (CheckCollision(ball->rect, leftBound->rect) == true)
	{
		ball->rect.setPosition(windowPosX, windowPosY);
		ballAngle = newBallAngle;
		UpdateScore(SCOREBOUND::LEFT);
	}

	if (CheckCollision(ball->rect, rightBound->rect) == true)
	{
		ball->rect.setPosition(windowPosX, windowPosY);
		ballAngle = newBallAngle;
		UpdateScore(SCOREBOUND::RIGHT);
	}
}

void Engine::GameReset()
{
	auto leftScorePtr = textElems.at(0);
	auto rightScorePtr = textElems.at(1);
	auto winMessagePtr = textElems.at(4);
	
	IsGameRunning = true;
	leftScore = 0;
	rightScore = 0;
	winMessagePtr->setString(" ");

	leftScorePtr->setString(std::to_string(leftScore));
	rightScorePtr->setString(std::to_string(rightScore));
	
	ball->Reset(window);
	ballAngle = PI - ballAngle + (std::rand() % 20) * PI / 180;

}

void Engine::GameEnd()
{ 
	auto winMessagePtr = textElems.at(4);

	auto player1PosX = player1->rect.getPosition().x - player2->rect.getSize().x;
	auto player1PosY = player2->rect.getPosition().y - player2->rect.getSize().y;
	auto player2PosX = player2->rect.getPosition().x - player2->rect.getSize().x;
	auto player2PosY = player2->rect.getPosition().y - player2->rect.getSize().y;

	winMessagePtr->setString("You win!");
	winMessagePtr->setLetterSpacing(1.0f);

	if (leftScore == maxScore)
	{
		winMessagePtr->setPosition(player1PosX , player1PosY);
	}
	else if (rightScore == maxScore)
	{
		winMessagePtr->setPosition(player2PosX, player2PosY);
	}
	
	IsGameRunning = false;

}

void Engine::Render()
{
	window.clear(sf::Color::Black);
	sf::VertexArray net(sf::LineStrip, 2);
	net[0].position = sf::Vector2f(windowWidthFP / 2, 0.0f);
	net[1].position = sf::Vector2f(windowWidthFP/ 2, windowHeightFP);
	net[0].color = sf::Color::White;
	net[1].color = sf::Color::White;

	window.draw(player1->rect);
	window.draw(player2->rect);
	window.draw(ball->rect);

	window.draw(topBound->rect);
	window.draw(bottomBound->rect);
	window.draw(leftBound->rect);
	window.draw(rightBound->rect);

	for (auto const &text : textElems)
	{
		window.draw(*text);
	}

	window.draw(net);
	window.display();
}

void Engine::Run()
{	
	while (window.isOpen())
	{
		while (dTimeSinceStart > dTime)
		{
			HandleCollisons();
			dTimeSinceStart -= dTime;
			HandleInput(dTime);
			Update(dTime);
		}
		dTimeSinceStart += clock.restart();
		Render();
	}
}

void Engine::HandleCollisons()
{
	/*The amount to displace the paddle by once it collides with a bound*/
	auto disp = 10.0f;

	if (CheckCollision(player1->rect, topBound->rect) == true)
	{
		player1->rect.move(0.0f, disp);
	}

	if (CheckCollision(player1->rect, bottomBound->rect) == true)
	{
		player1->rect.move(0.0f, -disp);
	}

	if (CheckCollision(player2->rect, topBound->rect) == true)
	{
		player2->rect.move(0.0f, disp);
	}

	if (CheckCollision(player2->rect, bottomBound->rect) == true)
	{
		player2->rect.move(0.0f, -disp);
	}
}


bool Engine::CheckCollision(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB)
{
	if (rectA.getGlobalBounds().intersects(rectB.getGlobalBounds()) == true)
	{
		return true;
	}
	else
	{
		return false;
	}
} 
void Engine::CheckScore()
{
	if (IsGameRunning)
	{
	 if (leftScore == maxScore)
	 {
		std::cout << "Score reached!" << '\n';
		GameEnd();
	 }
	 else if (rightScore == maxScore)
	 {
		std::cout << "Score reached!" << '\n';
		GameEnd();
	} 
	}
}

void Engine::UpdateScore(Engine::SCOREBOUND bound)
{
	if (!IsGameRunning)
	{
		return;
	}

	auto leftScorePtr = textElems.at(0);
	auto rightScorePtr = textElems.at(1);
	switch (bound)
	{
		{
		case SCOREBOUND::LEFT:
		rightScore++;
		rightScorePtr->setString(std::to_string(rightScore));
		break;

		case SCOREBOUND::RIGHT:
		leftScore++;
		leftScorePtr->setString(std::to_string(leftScore));
		break;

		default:
		break;
		}
	}
	CheckScore();
}
