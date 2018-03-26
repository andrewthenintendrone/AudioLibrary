#pragma once
#include <chrono>
#include <list>

// wrapper around std::chrono
class Clock
{
public:

	Clock();

	void recordTiming();

	void readTiming(const std::string& filename);
	void writeTiming(const std::string& filename);
	void showTiming();

	int64_t getTimeSeconds();
	int64_t getTimeMilliseconds();

private:

	// time that this clock was created
	std::chrono::time_point<std::chrono::high_resolution_clock> m_creationTime;

	std::list<int64_t> m_eventTimes;
};