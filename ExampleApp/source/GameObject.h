#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:

	GameObject(const std::string& filename);

	void update(float dt);

	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	void playSound();

	char getKeyCode() const { return m_keycode; }

	void draw(sf::RenderWindow* renderer);


	float m_hitTimer = 0.0f;
	char m_keycode = 'a';
	std::string m_soundEffect;

private:

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};