

#include "Engine.h"

Engine::Engine() : window(sf::VideoMode(windowWidth, windowHeight), "Pong", sf::Style::Close)
{
	std::cout << "Engine object constructed!" << "\n";
	dTime = sf::seconds(1.0f / FRAME_RATE);
	dTimeSinceStart = sf::Time::Zero;
	ballAngle = (std::rand() % 360) * 2 * PI / 360;
	//rectShapes = std::make_unique<std::vector<sf::RectangleShape*>>();
	textElems = std::make_unique<std::vector<TextElement>>();
	float windowWidthFP = static_cast<int>(std::round(windowWidth));
	float windowHeightFP = static_cast<int>(std::round(windowHeight));
	font.loadFromFile("G:/VSRepos/SFMLPONG/Content/bit5x3.ttf");

	for (int i = 1; i <= NUM_TEXT_ELEMS; i++)
	{
		textElems->push_back(*TextElement::CreateElement());
	}

	player1 = std::make_shared<Paddle>(80.0f, windowHeightFP / 2);

	player2 = std::make_shared<Paddle>(560.0f, windowHeightFP / 2);
	ball = std::make_shared<Ball>(windowWidthFP / 2, windowHeightFP / 2);
	topBounds = std::make_shared<Bounds>(0.0f, 0.0f, windowWidth, 0.0f);
	bottomBounds = std::make_shared<Bounds>(0.0f, windowHeight, windowWidth, 0.0f);
	leftBounds = std::make_shared<Bounds>(0.0f, 0.0f, 0.0f, windowHeight);
	rightBounds = std::make_shared<Bounds>(windowWidth, 0.0f, 0.0f, windowHeight);

	rectShapes.emplace_back(player1->rect);
	rectShapes.emplace_back(&player2->rect);
	rectShapes.emplace_back(&ball->rect);
	rectShapes.emplace_back(&topBounds->rect);
	rectShapes.emplace_back(&bottomBounds->rect);
	rectShapes.emplace_back(&leftBounds->rect);
	rectShapes.emplace_back(&rightBounds->rect);


	playerScore = &textElems->at(0);
	playerScore->setFont(font);
	playerScore->setString(std::to_string(pScore));
	playerScore->setPosition(window.getSize().x / 2 - 30.0f, 0.0f);

	aiScore = &textElems->at(1);
	aiScore->setFont(font);
	aiScore->setString(std::to_string(p2Score));
	aiScore->setPosition(window.getSize().x / 2 + 10.0f, 0.0f);

	toolTip1 = &textElems->at(2);
	toolTip2 = &textElems->at(3);
	
	toolTip1->setFont(font);
	toolTip1->setFillColor(sf::Color::Green);
	toolTip1->setCharacterSize(TEXT_MIN_SIZE);
	toolTip1->setString("Press SPACEBAR to reset the game");
	toolTip1->setPosition(sf::Vector2f(0.0f, -2.0f));

	toolTip2->setFont(font);
	toolTip2->setFillColor(sf::Color::Cyan);
	toolTip2->setCharacterSize(TEXT_MIN_SIZE);
	toolTip2->setString("Press Esc/Escape to quit");
	toolTip2->setPosition(sf::Vector2f(0.0f, 12.0f));

	player1->rect.setOrigin(player1->rect.getSize().x / 2, player1->rect.getSize().y / 2);
	player2->rect.setOrigin(player2->rect.getSize().x / 2, player2->rect.getSize().y / 2);
	ball->rect.setOrigin(ball->rect.getSize().x / 2, ball->rect.getSize().y / 2);
}

Engine::~Engine()
{
	std::cout << "Engine object deleted!" << "\n";
}

void Engine::Handle_Input(const sf::Time& deltaTime)
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
			ResetGame();
			break;

			default:
			break;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (Handle_Collisons(player1->rect, topBounds->rect) == false)
		{
			player1->rect.move(0.0f, -1.0f * PADDLE_SPEED * deltaTime.asSeconds());
		}
		player1->rect.move(0.0f, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (Handle_Collisons(player1->rect, bottomBounds->rect) == false)
		{
			player1->rect.move(0.0f, 1.0f * PADDLE_SPEED * deltaTime.asSeconds());
		}
		player1->rect.move(0.0f, 0.00f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (Handle_Collisons(player2->rect, topBounds->rect) == false)
		{
			player2->rect.move(0.0f, -1.0f * PADDLE_SPEED * deltaTime.asSeconds());
		}
		player2->rect.move(0.0f, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (Handle_Collisons(player2->rect, bottomBounds->rect) == false)
		{
			player2->rect.move(0.0f, 1.0f * PADDLE_SPEED * deltaTime.asSeconds());
		}
		player2->rect.move(0.0f, 0.0f);
	}
}

bool Engine::Handle_Collisons(const sf::RectangleShape& rectA, const sf::RectangleShape& rectB)
{
	if (rectA.getGlobalBounds().intersects(rectB.getGlobalBounds()))
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

	player2->rect.move(0.0f, rightPaddleSpeed);

	if (ball->rect.getPosition().y > player2->rect.getPosition().y)
	{
		rightPaddleSpeed = PADDLE_SPEED;
	}
	else if (ball->rect.getPosition().y < player2->rect.getPosition().y)
	{
		rightPaddleSpeed = -PADDLE_SPEED;
	}
	else
	{
		rightPaddleSpeed = 0.0f;
	}
}

void Engine::Update(const sf::Time& deltaTime)
{
	ball->rect.move(std::cos(ballAngle) * BALL_SPEED * deltaTime.asSeconds(), std::sin(ballAngle) * BALL_SPEED * deltaTime.asSeconds());

	if (Handle_Collisons(ball->rect, player1->rect) == true)
	{
		ballAngle = PI - ballAngle + (std::rand() % 20) * PI / 180;
	}

	if (Handle_Collisons(ball->rect, player2->rect) == true)
	{
		ballAngle = PI - ballAngle + (std::rand() % 20) * PI / 180;
	}

	if (Handle_Collisons(ball->rect, topBounds->rect) == true)
	{
		ballAngle = -ballAngle;
	}

	if (Handle_Collisons(ball->rect, bottomBounds->rect) == true)
	{
		ballAngle = ++ballAngle;
	}

	if (Handle_Collisons(ball->rect, leftBounds->rect) == true)
	{
		ResetBall();
		p2Score++;
		aiScore->setString(std::to_string(p2Score));
	}

	if (Handle_Collisons(ball->rect, rightBounds->rect) == true)
	{
		ResetBall();
		pScore++;
		playerScore->setString(std::to_string(pScore));
	}

}

void Engine::ResetBall()
{
	ball->rect.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	ballAngle = PI - ballAngle + (std::rand() % 20) * PI / 180;
}

void Engine::ResetGame()
{
	pScore = 0;
	p2Score = 0;
	playerScore->setString(std::to_string(pScore));
	aiScore->setString(std::to_string(p2Score));
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

	for (const auto tx : *textElems)
	{
		window.draw(tx);
	}

	for (const auto rect : rectShapes)
	{
		window.draw(*rect);
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
			dTimeSinceStart -= dTime;
			Handle_Input(dTime);
			Update(dTime);
		}
		Render();
		dTimeSinceStart += clock.restart();
	}

}