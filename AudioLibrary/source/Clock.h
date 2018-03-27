#pragma once
#include <chrono>

// wrapper around time stuff
class Clock
{
public:

	Clock();

	int64_t getTimeSeconds();
	int64_t getTimeMilliseconds();
	int64_t getTimeMicroseconds();

	void update();

	float getDeltaTime();

private:

	std::chrono::high_resolution_clock m_timer;

	// time that this clock was created
	std::chrono::time_point<std::chrono::high_resolution_clock> m_creationTime;

	std::chrono::time_point<std::chrono::high_resolution_clock> m_lastTime;

	float deltaTime = 0.0f;
};
