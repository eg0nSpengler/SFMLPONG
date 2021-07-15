
#include "TextElement.h"

TextElement::TextElement(const sf::Font& font, const sf::Color& color, const unsigned int charSize, sf::String string, sf::Vector2f pos) : font(font), color(color), charSize(charSize), string(string), pos(pos)
{
	setFont(font);
	setFillColor(color);
	setCharacterSize(charSize);
	setString(string);
	setPosition(pos);
}

TextElement::TextElement(const sf::Font& font, sf::String& string, sf::Vector2f pos) : font(font), string(string), pos(pos)
{
	setFont(font);
	setString(string);
	setPosition(pos);
}
