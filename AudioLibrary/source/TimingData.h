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

	void writeEvents(const std::string& filename, bool append);
	void readEvents(const std::string& filename);

	void addRepeatingEvent(const char keyCode, const int64_t timeStamp, const int time, const int count);
	float getRatioToNextEvent(int number, int64_t currentTime);

	void averageEvents(std::list<std::string> filenames);

	InputEvent getClosestEvent(int64_t currentTime);
	int64_t getClosestEventOffset(int64_t currentTime);

	InputEvent getEvent(int number);
	size_t getNumEvents();

private:

	void orderEvents();

	std::list<InputEvent> m_events;
};