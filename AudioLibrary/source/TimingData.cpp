#include "TimingData.h"
#include <fstream>
#include <iostream>

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

void TimingData::writeEvents(const std::string& filename)
{
	std::ofstream file(filename, std::ios::trunc | std::ios::binary);

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
