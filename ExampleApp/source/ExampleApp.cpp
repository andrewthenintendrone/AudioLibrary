#include "ExampleApp.h"

ExampleApp::ExampleApp(const int width, const int height, const std::string& title)
{
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	if (!record)
	{
		//m_timingData.readEvents(m_timingFile);
		m_timingData.averageEvents(m_timingFile1, m_timingFile2);
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
	AudioManager::getInstance().playStream("audio/music2.mp3");

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
				m_timingData.writeEvents(m_timingFile2, false);
			}
			m_window->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (record)
				{
					m_timingData.writeEvents(m_timingFile2, false);
				}
				m_window->close();
			}
			else
			{
				for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++)
				{
					if ((char)event.key.code == (*iter)->getKeyCode() &&record)
					{
						(*iter)->m_hitTimer = 0.25f;
						m_timingData.addEvent((char)event.key.code, m_clock.getTimeMilliseconds());
						(*iter)->playSound();
					}
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
			if (m_clock.getTimeMilliseconds() >= m_timingData.getEvent(currentEvent).TimeStamp)
			{
				for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); iter++)
				{
					if (m_timingData.getEvent(currentEvent).KeyCode == (*iter)->getKeyCode())
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

	m_window->display();
}
