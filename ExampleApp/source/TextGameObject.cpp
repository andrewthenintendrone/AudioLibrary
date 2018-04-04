#include "TextGameObject.h"

TextGameObject::TextGameObject()
{
	
}

void TextGameObject::draw(sf::RenderWindow* renderer)
{
	setOrigin();
	renderer->draw(m_text);
}

void TextGameObject::setPosition(const sf::Vector2f& position)
{
	m_text.setPosition(position);
}

void TextGameObject::setPosition(const float x, const float y)
{
	m_text.setPosition(x, y);
}

void TextGameObject::setScale(const sf::Vector2f& scale)
{
	m_text.setScale(scale);
}

void TextGameObject::setScale(const float x, const float y)
{
	m_text.setScale(x, y);
}

void TextGameObject::setFont(sf::Font* font)
{
	m_font = font;
	m_text.setFont(*m_font);
}

void TextGameObject::setColor(const sf::Color& color)
{
	m_text.setFillColor(color);
}

void TextGameObject::setString(const std::string& string)
{
	m_text.setString(string);
}

void TextGameObject::setOrigin()
{
	sf::FloatRect localBounds = m_text.getLocalBounds();
	m_text.setOrigin(localBounds.left + localBounds.width / 2, localBounds.top + localBounds.height / 2);
}
