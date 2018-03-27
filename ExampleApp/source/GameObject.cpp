#include "GameObject.h"
#include "AudioManager.h"

GameObject::GameObject(const std::string& filename)
{
	m_texture.loadFromFile(filename);
	m_sprite.setTexture(m_texture);

	// center origin
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);
}

void GameObject::update(float dt)
{
	m_hitTimer = std::max(0.0f, m_hitTimer - dt);
}

void GameObject::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
}

void GameObject::setPosition(const float x, const float y)
{
	m_sprite.setPosition(sf::Vector2f(x, y));
}

void GameObject::playSound()
{
	AudioManager::getInstance().playAudio(m_soundEffect);
}

void GameObject::draw(sf::RenderWindow* renderer)
{
	m_sprite.setScale(1.0f + m_hitTimer, 1.0f + m_hitTimer);
	renderer->draw(m_sprite);
}
