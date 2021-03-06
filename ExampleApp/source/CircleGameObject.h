#pragma once
#include "GameObject.h"

class CircleGameObject : public GameObject
{
public:

	CircleGameObject(const float radius = 10.0f, const sf::Color& color = sf::Color::White, const sf::Color& outlineColor = sf::Color::White);

	virtual void draw(sf::RenderWindow* renderer);

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setPosition(const float x, const float y);

	virtual void setScale(const sf::Vector2f& scale);
	virtual void setScale(const float x, const float y);

	void setColor(const sf::Color& color);
	void setOutlineColor(const sf::Color& color);
	void setOutlineThickness(const float thickness);

private:

	sf::CircleShape m_circle;

	float m_radius;
};
