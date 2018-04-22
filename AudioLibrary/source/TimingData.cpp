#include "TimingData.h"
#include <fstream>
#include <iostream>
#include <algorithm>

void TimingData::addEvent(const InputEvent& event)
{
	m_events.push_back(event);
}

void TimingData::addEvent(char keyCode, int64_t timeStamp)
{
	m_events.push_back(InputEvent{ keyCode, timeStamp });
}

void TimingData::writeEvents(const std::string& filename, bool append)
{
	std::ofstream file;

	if (append)
	{
		file.open(filename, std::ios::app | std::ios::binary);
	}
	else
	{
		file.open(filename, std::ios::trunc | std::ios::binary);
	}

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename.c_str() << " for writing. Is it being used by another process?\n";
		return;
	}

	for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
	{
		file.write(reinterpret_cast<char*>(&iter->KeyCode), sizeof(char));
		file.write(reinterpret_cast<char*>(&iter->TimeStamp), sizeof(int64_t));
	}

	file.close();
}

void TimingData::serializeEvents(const std::string& filename, bool append)
{
	std::ofstream file;

	if (append)
	{
		file.open(filename, std::ios::app);
	}
	else
	{
		file.open(filename, std::ios::trunc);
	}

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename.c_str() << " for writing. Is it being used by another process?\n";
		return;
	}

	for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
	{
		file << (int)iter->KeyCode << " ";
		file << iter->TimeStamp;

		if (std::next(iter) != m_events.end())
		{
			file << std::endl;
		}
	}

	file.close();
}

void TimingData::readEvents(const std::string& filename)
{
	std::ifstream file(filename, std::ios::_Nocreate | std::ios::binary | std::ios::ate);

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename.c_str() << " for reading. Does it exist?\n";
		return;
	}

	int64_t numEvents = (int64_t)file.tellg() / (sizeof(char) + sizeof(int64_t));

	file.seekg(0, std::ios::beg);

	for(int i = 0; i < numEvents; i++)
	{
		InputEvent currentEvent;

		file.read(reinterpret_cast<char*>(&currentEvent.KeyCode), sizeof(char));
		file.read(reinterpret_cast<char*>(&currentEvent.TimeStamp), sizeof(int64_t));

		m_events.push_back(currentEvent);
	}

	file.close();

	// order the read events
	orderEvents();
}

void TimingData::deserializeEvents(const std::string& filename)
{
	std::ifstream file(filename, std::ios::_Nocreate);

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename.c_str() << " for reading. Does it exist?\n";
		return;
	}

	while (!file.eof())
	{
		InputEvent currentEvent;

		int keyCode;
		int64_t timeStamp;

		file >> std::dec >> keyCode;
		file >> timeStamp;

		currentEvent.KeyCode = (char)keyCode;
		currentEvent.TimeStamp = timeStamp;
		/*file.read(reinterpret_cast<char*>(&currentEvent.KeyCode), sizeof(char));
		file.read(reinterpret_cast<char*>(&currentEvent.TimeStamp), sizeof(int64_t));*/

		m_events.push_back(currentEvent);
	}

	file.close();

	// order the read events
	orderEvents();
}

// add an event that repeats every 
void TimingData::addRepeatingEvent(const char keyCode, const int64_t timeStamp, const int time, const int count)
{
	InputEvent currentEvent;
	currentEvent.KeyCode = keyCode;
	currentEvent.TimeStamp = timeStamp;

	for (int i = 0; i < count; i++)
	{
		m_events.push_back(currentEvent);
		currentEvent.TimeStamp += time;
	}

	orderEvents();
}

// 
float TimingData::getRatioToNextEvent(int64_t currentTime)
{
	// no events have happened yet
	if (currentTime <= m_events.front().TimeStamp)
	{
		return (float)(currentTime) / (float)m_events.front().TimeStamp;
	}

	// all events have finished
	if (currentTime >= m_events.back().TimeStamp)
	{
		return 1.0f;
	}

	InputEvent currentEvent;
	InputEvent nextEvent;

	for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
	{
		if (currentTime >= iter->TimeStamp)
		{
			currentEvent = *iter;
			nextEvent = *std::next(iter);
		}
	}

	/*if (number == 0)
	{
		currentEvent = InputEvent{ m_events.front().KeyCode, 0 };
		nextEvent = m_events.front();
	}
	else
	{
		currentEvent = getEvent(number - 1);
		nextEvent = getEvent(number);
	}*/

	int64_t timeSinceEvent = currentTime - currentEvent.TimeStamp;
	int64_t timeBetweenEvents = nextEvent.TimeStamp - currentEvent.TimeStamp;

	// events are simultaneous
	if (timeBetweenEvents == 0)
	{
		// (avoid divide by 0)
		return 1.0f;
	}

	return (float)(timeSinceEvent) / (float)(timeBetweenEvents);
}

// averages the timings of files
void TimingData::readAverageEvents(std::list<std::string> filenames)
{
	for (auto iter = filenames.begin(); iter != filenames.end(); iter++)
	{
		std::ifstream file(*iter, std::ios::_Nocreate | std::ios::binary | std::ios::ate);

		if (!file.is_open())
		{
			std::cout << "Failed to open " << *iter->c_str() << " for reading. Does it exist?\n";
			return;
		}

		int64_t numEvents = (int64_t)file.tellg() / (sizeof(char) + sizeof(int64_t));

		file.seekg(0, std::ios::beg);

		for(int i = 0; i < numEvents; i++)
		{
			InputEvent currentEvent;

			file.read(reinterpret_cast<char*>(&currentEvent.KeyCode), sizeof(char));
			file.read(reinterpret_cast<char*>(&currentEvent.TimeStamp), sizeof(int64_t));

			m_events.push_back(currentEvent);
		}

		file.close();
	}

	// order the read events
	orderEvents();

	// iterate through events and average them
	std::list<InputEvent> averagedEvents;

	for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
	{
		InputEvent currentEvent = *iter;

		for (size_t i = 0; i < filenames.size() - 1; i++)
		{
			iter++;
			currentEvent.TimeStamp += iter->TimeStamp;
		}

		currentEvent.TimeStamp /= filenames.size();

		averagedEvents.push_back(currentEvent);
	}

	m_events = averagedEvents;
}

void TimingData::deserializeAverageEvents(std::list<std::string> filenames)
{
	for (auto iter = filenames.begin(); iter != filenames.end(); iter++)
	{
		std::ifstream file(*iter, std::ios::_Nocreate);

		if (!file.is_open())
		{
			std::cout << "Failed to open " << *iter->c_str() << " for reading. Does it exist?\n";
			return;
		}

		while(!file.eof())
		{
			InputEvent currentEvent;

			int keyCode;
			int64_t timeStamp;

			file >> std::dec >> keyCode;
			file >> timeStamp;

			currentEvent.KeyCode = (char)keyCode;
			currentEvent.TimeStamp = timeStamp;
			/*file.read(reinterpret_cast<char*>(&currentEvent.KeyCode), sizeof(char));
			file.read(reinterpret_cast<char*>(&currentEvent.TimeStamp), sizeof(int64_t));*/

			m_events.push_back(currentEvent);
		}

		file.close();
	}

	// order the read events
	orderEvents();

	// iterate through events and average them
	std::list<InputEvent> averagedEvents;

	for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
	{
		InputEvent currentEvent = *iter;

		for (size_t i = 0; i < filenames.size() - 1; i++)
		{
			iter++;
			currentEvent.TimeStamp += iter->TimeStamp;
		}

		currentEvent.TimeStamp /= filenames.size();

		averagedEvents.push_back(currentEvent);
	}

	m_events = averagedEvents;
}

// returns the event that is closest in timing to the current time
InputEvent TimingData::getClosestEvent(int64_t currentTime)
{
	int64_t closestTime = INT64_MAX;
	InputEvent closestEvent;

	for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
	{
		if (std::abs((*iter).TimeStamp - currentTime) < closestTime)
		{
			closestTime = std::abs((*iter).TimeStamp - currentTime);
			closestEvent = (*iter);
		}
	}

	return closestEvent;
}

// returns the time difference between the closest event to now and now
int64_t TimingData::getClosestEventOffset(int64_t currentTime)
{
	int64_t closestTime = INT64_MAX;

	for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
	{
		if (std::abs((*iter).TimeStamp - currentTime) < closestTime)
		{
			closestTime = std::abs((*iter).TimeStamp - currentTime);
		}
	}

	return closestTime;
}

// predicate for sorting events
bool eventSort(const InputEvent& a, const InputEvent& b)
{
	return (a.TimeStamp < b.TimeStamp);
}

// sorts events in chronological order
void TimingData::orderEvents()
{
	m_events.sort(eventSort);
}

// get an event by number
InputEvent TimingData::getEvent(unsigned int number)
{
	if (number < m_events.size())
	{
		return *std::next(m_events.begin(), number);
	}

	return m_events.back();
}

// returns the number of events
size_t TimingData::getNumEvents()
{
	return m_events.size();
}
