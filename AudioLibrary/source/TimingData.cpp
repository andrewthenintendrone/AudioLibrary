#include "TimingData.h"
#include <fstream>
#include <iostream>
#include <algorithm>

TimingData::TimingData()
{

}

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
		InputEvent currentEvent = *iter;

		file.write(reinterpret_cast<char*>(&currentEvent.KeyCode), sizeof(char));
		file.write(reinterpret_cast<char*>(&currentEvent.TimeStamp), sizeof(int64_t));
	}

	file.close();
}

void TimingData::readEvents(const std::string& filename)
{
	std::ifstream file(filename, std::ios::_Nocreate | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename.c_str() << " for reading. Does it exist?\n";
		return;
	}

	while(!file.eof())
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

// averages the timings of 2 files
void TimingData::averageEvents(const std::string& filename1, const std::string& filename2)
{
	std::ifstream file(filename1, std::ios::_Nocreate | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename1.c_str() << " for reading. Does it exist?\n";
		return;
	}

	while (!file.eof())
	{
		InputEvent currentEvent;

		file.read(reinterpret_cast<char*>(&currentEvent.KeyCode), sizeof(char));
		file.read(reinterpret_cast<char*>(&currentEvent.TimeStamp), sizeof(int64_t));

		m_events.push_back(currentEvent);
	}

	file.close();

	file.open(filename2, std::ios::_Nocreate | std::ios::binary);

	if (!file.is_open())
	{
		std::cout << "Failed to open " << filename2.c_str() << " for reading. Does it exist?\n";
		return;
	}

	while (!file.eof())
	{
		InputEvent currentEvent;

		file.read(reinterpret_cast<char*>(&currentEvent.KeyCode), sizeof(char));
		file.read(reinterpret_cast<char*>(&currentEvent.TimeStamp), sizeof(int64_t));

		m_events.push_back(currentEvent);
	}

	file.close();

	// order the read events
	orderEvents();

	// iterate through events and average them
	std::list<InputEvent> averagedEvents;

	for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
	{
		InputEvent currentEvent = *iter;

		iter++;

		currentEvent.TimeStamp += iter->TimeStamp;

		currentEvent.TimeStamp /= 2;

		averagedEvents.push_back(currentEvent);
	}

	m_events = averagedEvents;
}

// predicate for sorting events
bool eventSort(const InputEvent& a, const InputEvent& b)
{
	return (a.TimeStamp < b.TimeStamp);
}

// make sure all events are in order
void TimingData::orderEvents()
{
	m_events.sort(eventSort);
}

InputEvent TimingData::getEvent(int number)
{
	if (number < m_events.size())
	{
		return *std::next(m_events.begin(), number);
	}
	else
	{
		return *m_events.end();
	}
}

size_t TimingData::getNumEvents()
{
	return m_events.size();
}
