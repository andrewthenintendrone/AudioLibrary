#include "Clock.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include "AudioManager.h"

// set creation time
Clock::Clock()
{
	m_creationTime = std::chrono::high_resolution_clock::now();
}

// record input timings
void Clock::recordTiming()
{
	while (true)
	{
		if (_kbhit())
		{
			int keyCode = _getch();

			if (keyCode == 13)
			{
				std::cout << "you pressed enter\n";
				break;
			}
			else
			{
				std::cout << "Pressed " << char(keyCode) << " at time " << getTimeMilliseconds() / 1000.0f << std::endl;
				m_eventTimes.push_back(getTimeMilliseconds());
			}
		}
		else
		{
			continue;
		}
	}
}

// write times to a txt file
void Clock::readTiming(const std::string& filename)
{
	std::ifstream file(filename, std::ios::_Nocreate);

	while (!file.eof())
	{
		int64_t t;
		file >> t;
		m_eventTimes.push_back(t);
	}

	file.close();
}

// write times to a txt file
void Clock::writeTiming(const std::string& filename)
{
	std::ofstream file(filename, std::ios::trunc);

	for (auto iter = m_eventTimes.begin(); iter != m_eventTimes.end(); iter++)
	{
		file << *iter << std::endl;
	}

	file.close();
}

void Clock::showTiming()
{
	for (auto iter = m_eventTimes.begin(); iter != m_eventTimes.end(); iter++)
	{
		while (getTimeMilliseconds() < *iter)
		{
			AudioManager::getInstance().update();
		}
		std::cout << "a";
		AudioManager::getInstance().playAudio("C:/Users/s170837/Documents/AudioLibrary/AudioLibrary/bin/beep.wav");
	}
}

// get number of seconds since this clocks creation
int64_t Clock::getTimeSeconds()
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_creationTime).count();
}

// get number of milliseconds since this clocks creation
int64_t Clock::getTimeMilliseconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_creationTime).count();
}
