#include "ExampleApp.h"

ExampleApp::ExampleApp(const int width, const int height, const std::string& title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

// add a new drawable object
void ExampleApp::addDrawable(sf::Drawable* drawable)
{
	m_drawables.push_back(drawable);
}

// remove a drawable object
void ExampleApp::removeDrawable(sf::Drawable* drawable)
{
	for (auto iter = m_drawables.begin(); iter != m_drawables.end();)
	{
		if (*iter == drawable)
		{
			iter = m_drawables.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void ExampleApp::run()
{
	// play audio
	AudioManager::getInstance().playStream("audio/music.mp3");

	while (m_window->isOpen())
	{
		update();
		draw();
	}
}

// main loop
void ExampleApp::update()
{
	sf::Event event;

	// poll events
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			m_window->close();
		}
	}
}

void ExampleApp::draw()
{
	m_window->clear();

	for (auto iter = m_drawables.begin(); iter != m_drawables.end(); iter++)
	{
		m_window->draw(**iter);
	}

	m_window->display();
}

