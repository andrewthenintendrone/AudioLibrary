#pragma once
#include "Clock.h"
#include "InputEvent.h"
#include <list>

// holds a list of timing data
class TimingData
{
public:

	TimingData();

	void addEvent(const InputEvent& event);
	void addEvent(const char keyCode, const int64_t timeStamp);

	void writeEvents(const std::string& filename);
	void readEvents(const std::string& filename);

	InputEvent getEvent(int number);
	size_t getNumEvents();

private:

	std::list<InputEvent> m_events;
};