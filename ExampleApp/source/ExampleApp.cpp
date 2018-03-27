#include "ExampleApp.h"

ExampleApp::ExampleApp(const int width, const int height, const std::string& title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	if (!record)
	{
		m_timingData.readEvents("C:/Users/s170837/Desktop/timing.bin");
	}
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
	AudioManager::getInstance().playStream("audio/music4.mp3");

	while (m_window->isOpen())
	{
		update();
		draw();
	}
}

// main loop
void ExampleApp::update()
{
	m_clock.update();
	hitTimer = std::max(0.0f, hitTimer - m_clock.getDeltaTime());
	sf::Event event;

	// poll events
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			if (record)
			{
				m_timingData.writeEvents("C:/Users/s170837/Desktop/timing.bin");
			}
			m_window->close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			if (record)
			{
				m_timingData.writeEvents("C:/Users/s170837/Desktop/timing.bin");
			}
			m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (record)
			{
				hitTimer = 0.5f;
				m_timingData.addEvent((char)event.key.code, m_clock.getTimeMilliseconds());
				AudioManager::getInstance().playAudio("audio/drum.wav");
			}
		}
	}

	if (!record)
	{
		if (currentEvent < m_timingData.getNumEvents())
		{
			if (m_clock.getTimeMilliseconds() >= m_timingData.getEvent(currentEvent).TimeStamp)
			{
				AudioManager::getInstance().playAudio("audio/drum.wav");
				currentEvent++;
				hitTimer = 0.5f;
			}
		}
	}

	AudioManager::getInstance().update();
}

void ExampleApp::draw()
{
	m_window->clear();

	float scale = 1.0f + hitTimer;

	for (auto iter = m_drawables.begin(); iter != m_drawables.end(); iter++)
	{
		reinterpret_cast<sf::CircleShape*>(*iter)->setScale(scale, scale);
		m_window->draw(**iter);
	}

	m_window->display();
}
