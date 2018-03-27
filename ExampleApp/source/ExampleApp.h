#pragma once
#include <SFML\Graphics.hpp>
#include <AudioManager.h>
#include <TimingData.h>
#include <Clock.h>
#include <string>
#include <list>

class ExampleApp
{

public:

	ExampleApp(const int width = 800, const int height = 600, const std::string& title = "");

	void run();

	void addDrawable(sf::Drawable* drawable);
	void removeDrawable(sf::Drawable* drawable);

private:

	void update();
	void draw();

	sf::RenderWindow* m_window;

	std::list<sf::Drawable*> m_drawables;

	TimingData m_timingData;
	Clock m_clock;

	int currentEvent = 0;
	bool record = false;

	float hitTimer = 0;
};