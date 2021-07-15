#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
class TextElement : public sf::Text
{
public:
	TextElement() = default;
	TextElement(const sf::Font& font, const sf::Color& color, const unsigned int charSize, sf::String string, sf::Vector2f pos);
	TextElement(const sf::Font& font, sf::String& string, sf::Vector2f pos);

private:
	sf::Font font;
	sf::String string;
	sf::Color color;
	unsigned int charSize;
	sf::Vector2f pos;
};

