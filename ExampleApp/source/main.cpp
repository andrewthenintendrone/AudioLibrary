#include "ExampleApp.h"

const int windowWidth = 1280;
const int windowHeight = 720;

int main(int argc, char* argv[])
{
	ExampleApp app(windowWidth, windowHeight, "Audio Library Example");

	CircleGameObject object(200, sf::Color(232, 102, 160, 255));
	object.m_keycode = sf::Keyboard::Space;
	object.m_soundEffect = "audio/drum.wav";
	object.setPosition(windowWidth / 2, windowHeight / 2);

	app.addGameObject(&object);

	app.run();

	return 0;
}