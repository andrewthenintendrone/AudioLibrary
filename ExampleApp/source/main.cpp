#include "ExampleApp.h"

const int windowWidth = 1280;
const int windowHeight = 720;

int main(int argc, char* argv[])
{
	ExampleApp exampleApp(windowWidth, windowHeight, "OSS!");

	sf::CircleShape* ball = new sf::CircleShape(200);
	ball->setFillColor(sf::Color(233, 132, 178));
	ball->setOrigin(200, 200);
	ball->setPosition(windowWidth / 2, windowHeight / 2);
	ball->setOutlineColor(sf::Color::White);
	ball->setOutlineThickness(10);
	exampleApp.addDrawable(ball);

	sf::Font font;
	font.loadFromFile("fonts/Roboto-Regular.ttf");

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(100);
	text.setString("OSS!");
	//center text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	text.setPosition(windowWidth / 2, windowHeight / 2);
	exampleApp.addDrawable(&text);

	exampleApp.run();

	return 0;
}