#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:

	void update(float dt);

	virtual void setPosition(const sf::Vector2f& position) = 0;
	virtual void setPosition(const float x, const float y) = 0;

	virtual void setScale(const sf::Vector2f& scale) = 0;
	virtual void setScale(const float x, const float y) = 0;

	void playSound();

	virtual void draw(sf::RenderWindow* renderer) = 0;

	float m_hitTimer = 0.0f;
	char m_keycode = 'a';
	std::string m_soundEffect;
};