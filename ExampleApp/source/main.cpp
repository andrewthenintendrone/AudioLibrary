#include "ExampleApp.h"

const int windowWidth = 1280;
const int windowHeight = 720;

int main(int argc, char* argv[])
{
	ExampleApp app(windowWidth, windowHeight, "Audio Library Example");

	GameObject drum("textures/drum.png");
	drum.m_keycode = (sf::Keyboard::RShift);
	drum.m_soundEffect = ("audio/drum.wav");

	GameObject cymbal("textures/cymbal.png");
	cymbal.m_keycode = (sf::Keyboard::LShift);
	cymbal.m_soundEffect = ("audio/cymbal.wav");

	GameObject saxophone("textures/saxophone.png");
	saxophone.m_keycode = (sf::Keyboard::Space);
	saxophone.m_soundEffect = ("audio/saxophone.wav");

	drum.setPosition(sf::Vector2f(windowWidth * 0.75f, windowHeight / 2.0f));
	cymbal.setPosition(sf::Vector2f(windowWidth * 0.25f, windowHeight / 2.0f));
	saxophone.setPosition(sf::Vector2f(windowWidth * 0.5f, windowHeight / 2.0f));

	app.addGameObject(&drum);
	app.addGameObject(&cymbal);
	app.addGameObject(&saxophone);

	app.run();

	return 0;
}