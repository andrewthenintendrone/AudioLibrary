#pragma once
#include <SFML\Graphics.hpp>
#include <AudioManager.h>
#include <TimingData.h>
#include <Clock.h>
#include <string>
#include <list>
#include "GameObject.h"
#include "CircleGameObject.h"
#include "TextGameObject.h"

enum SUCCESSSTATE { NONE, BAD, GOOD, PERFECT };

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

	void updateText(char currentKeyCode);

	sf::RenderWindow* m_window;

	std::list<GameObject*> m_gameObjects;

	sf::Font m_font;
	TextGameObject m_errorText;

	TimingData m_timingData;
	Clock m_clock;

	int currentEvent = 0;
	bool record = false;

	SUCCESSSTATE m_currentSuccessState = NONE;

	std::string m_timingFile = "./timing.bin";
};