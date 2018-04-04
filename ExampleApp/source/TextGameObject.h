#pragma once
#include "GameObject.h"

class TextGameObject : public GameObject
{
public:

	TextGameObject();

	void update(float dt);

	virtual void draw(sf::RenderWindow* renderer);

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setPosition(const float x, const float y);

	virtual void setScale(const sf::Vector2f& scale);
	virtual void setScale(const float x, const float y);

	void setFont(sf::Font* font);
	void setColor(const sf::Color& color);
	void setString(const std::string& string);


private:

	void setOrigin();

	sf::Font* m_font;
	sf::Text m_text;
};