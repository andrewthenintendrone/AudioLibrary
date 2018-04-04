#include "ExampleApp.h"

const int windowWidth = 1280;
const int windowHeight = 720;

int main(int argc, char* argv[])
{
	ExampleApp app(windowWidth, windowHeight, "Audio Library Example");

	CircleGameObject timingObject(200, sf::Color(0, 0, 0, 0));
	timingObject.m_keycode = sf::Keyboard::Space;
	timingObject.setOutlineThickness(2.0f);
	timingObject.m_soundEffect = "audio/drum.wav";
	timingObject.setPosition(windowWidth / 2, windowHeight / 2);

	CircleGameObject hitObject(50, sf::Color(232, 102, 160, 255));
	hitObject.m_keycode = sf::Keyboard::Space;
	hitObject.setOutlineThickness(8.0f);
	hitObject.m_soundEffect = "audio/drum.wav";
	hitObject.setPosition(windowWidth / 2, windowHeight / 2);

	app.addGameObject(&timingObject);
	app.addGameObject(&hitObject);

	app.run();

	return 0;
}