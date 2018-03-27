#pragma once
#include <SFML\Graphics.hpp>
#include <AudioManager.h>
#include <TimingData.h>
#include <Clock.h>
#include <string>
#include <list>
#include "GameObject.h"

class ExampleApp
{

public:

	ExampleApp(const int width = 800, const int height = 600, const std::string& title = "");

	void run();

	void addGameObject(GameObject* gameobject);
	void removeGameObject(GameObject* gameobject);

private:

	void update();
	void draw();

	sf::RenderWindow* m_window;

	std::list<GameObject*> m_gameObjects;

	TimingData m_timingData;
	Clock m_clock;

	int currentEvent = 0;
	bool record = false;
};