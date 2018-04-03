#pragma once
#include "GameObject.h"

class SpriteGameObject : public GameObject
{
public:

	SpriteGameObject(const std::string& filename);

	virtual void draw(sf::RenderWindow* renderer);

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setPosition(const float x, const float y);

	virtual void setScale(const sf::Vector2f& scale);
	virtual void setScale(const float x, const float y);

private:

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};
