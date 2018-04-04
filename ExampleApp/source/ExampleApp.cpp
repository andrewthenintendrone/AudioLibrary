#include "ExampleApp.h"
#include <iostream>

ExampleApp::ExampleApp(const int width, const int height, const std::string& title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	m_font.loadFromFile("fonts/Roboto-Regular.ttf");
	m_errorText.setFont(&m_font);
	m_errorText.setPosition(width / 4, height / 4);

	if (record)
	{
		m_timingData.addRepeatingEvent(sf::Keyboard::Space, 0, 368, 300);
	}

	else
	{
		m_timingData.readEvents(m_timingFile);
	}
}

// add a new drawable object
void ExampleApp::addGameObject(GameObject* gameobject)
{
	m_gameObjects.push_back(gameobject);
}

// remove a drawable object
void ExampleApp::removeGameObject(GameObject* gameobject)
{
	for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end();)
	{
		if (*iter == gameobject)
		{
			iter = m_gameObjects.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void ExampleApp::run()
{
	// preload audio assets
	for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter ++)
	{
		AudioManager::getInstance().preloadAudio((*iter)->m_soundEffect);
	}

	// play audio
	AudioManager::getInstance().playStream("audio/lockstep.mp3");

	// reset clock
	m_clock = Clock();

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
	sf::Event event;

	// poll events
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			if (record)
			{
				m_timingData.writeEvents(m_timingFile, false);
			}
			m_window->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (record)
				{
					m_timingData.writeEvents(m_timingFile, false);
				}
				m_window->close();
			}
			else
			{
				for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++)
				{
					if ((char)event.key.code == (*iter)->m_keycode && record)
					{
						(*iter)->m_hitTimer = 0.25f;
						m_timingData.addEvent((char)event.key.code, m_clock.getTimeMilliseconds());
						(*iter)->playSound();
					}

					updateScore();
				}
			}
		}
	}

	// update gameobjects
	for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++)
	{
		(*iter)->update(m_clock.getDeltaTime());
	}

	if (!record)
	{
		if (currentEvent < m_timingData.getNumEvents())
		{
			float ratio = m_timingData.getRatioToNextEvent(currentEvent, m_clock.getTimeMilliseconds());
			m_gameObjects.front()->setScale(1.25f - ratio, 1.25f - ratio);

			if (m_clock.getTimeMilliseconds() > m_timingData.getEvent(currentEvent).TimeStamp)
			{
				for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++)
				{
					if (m_timingData.getEvent(currentEvent).KeyCode == (*iter)->m_keycode)
					{
						(*iter)->playSound();
						(*iter)->m_hitTimer = 0.25f;
					}
				}
				currentEvent++;
			}
		}
	}

	AudioManager::getInstance().update();
}

void ExampleApp::draw()
{
	m_window->clear();

	for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++)
	{
		(*iter)->draw(m_window);
	}

	m_errorText.draw(m_window);

	m_window->display();
}

// update the score
void ExampleApp::updateScore()
{
	// how far off the event are we
	int64_t playerError = m_timingData.getClosestEventOffset(m_clock.getTimeMilliseconds());

	int perfectCutoff = 30;
	int goodCutoff = 100;

	if (playerError < perfectCutoff)
	{
		m_currentSuccessState = PERFECT;
		m_errorText.setColor(sf::Color::Blue);
		m_errorText.setString("PERFECT");
	}
	else if (playerError < goodCutoff)
	{
		m_currentSuccessState = GOOD;
		m_errorText.setColor(sf::Color::Green);
		m_errorText.setString("GOOD");
	}
	else
	{
		m_currentSuccessState = BAD;
		m_errorText.setColor(sf::Color::Red);
		m_errorText.setString("BAD");
	}
}