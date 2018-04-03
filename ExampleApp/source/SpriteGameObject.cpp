#include "SpriteGameObject.h"

SpriteGameObject::SpriteGameObject(const std::string& filename)
{
	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);

	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

void SpriteGameObject::draw(sf::RenderWindow* renderer)
{
	renderer->draw(m_sprite);
}

void SpriteGameObject::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}

void SpriteGameObject::setPosition(const float x, const float y)
{
	m_sprite.setPosition(x, y);
}

void SpriteGameObject::setScale(const sf::Vector2f& scale)
{
	m_sprite.setScale(scale);
}

void SpriteGameObject::setScale(const float x, const float y)
{
	m_sprite.setScale(x, y);
}