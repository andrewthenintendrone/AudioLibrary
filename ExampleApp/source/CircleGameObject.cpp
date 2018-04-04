#include "CircleGameObject.h"

CircleGameObject::CircleGameObject(const float radius, const sf::Color& color, const sf::Color& outlineColor)
{
	m_radius = radius;
	m_circle.setRadius(radius);
	m_circle.setFillColor(color);
	m_circle.setOutlineColor(outlineColor);
	m_circle.setOutlineThickness(1.0f);


	m_circle.setOrigin(m_circle.getLocalBounds().left + m_circle.getLocalBounds().width / 2, m_circle.getLocalBounds().top + m_circle.getLocalBounds().height / 2);
}

void CircleGameObject::draw(sf::RenderWindow* renderer)
{
	renderer->draw(m_circle);
}

void CircleGameObject::setPosition(const sf::Vector2f& position)
{
	m_circle.setPosition(position);
}

void CircleGameObject::setPosition(const float x, const float y)
{
	m_circle.setPosition(x, y);
}

void CircleGameObject::setScale(const sf::Vector2f& scale)
{
	m_circle.setScale(scale.x, scale.y);
}

void CircleGameObject::setScale(const float x, const float y)
{
	m_circle.setScale(x, y);
}
