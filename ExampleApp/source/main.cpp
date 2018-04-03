#include "ExampleApp.h"

const int windowWidth = 1280;
const int windowHeight = 720;

int main(int argc, char* argv[])
{
	ExampleApp app(windowWidth, windowHeight, "Audio Library Example");

	GameObject drum("textures/drum.png");
	drum.m_keycode = sf::Keyboard::RShift;
	drum.m_soundEffect = "audio/drum.wav";

	GameObject cymbal("textures/cymbal.png");
	cymbal.m_keycode = sf::Keyboard::LShift;
	cymbal.m_soundEffect = "audio/cymbal.wav";

	GameObject saxophone("textures/saxophone.png");
	saxophone.m_keycode = sf::Keyboard::Space;
	saxophone.m_soundEffect = "audio/saxophone.wav";

	GameObject violin("textures/violin.png");
	violin.m_keycode = sf::Keyboard::B;
	violin.m_soundEffect = "audio/violin.wav";

	drum.setPosition(windowWidth * 0.25f, windowHeight * 0.25f);
	cymbal.setPosition(windowWidth * 0.75f, windowHeight * 0.25f);
	saxophone.setPosition(windowWidth * 0.25f, windowHeight * 0.75f);
	violin.setPosition(windowWidth * 0.75f, windowHeight * 0.75f);

	app.addGameObject(&drum);
	app.addGameObject(&cymbal);
	app.addGameObject(&saxophone);
	app.addGameObject(&violin);

	app.run();

	return 0;
}