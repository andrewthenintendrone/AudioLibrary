#include "Clock.h"
#include <fstream>
#include "AudioManager.h"

// set creation time
Clock::Clock()
{
	m_creationTime = m_timer.now();
	m_lastTime = m_creationTime;
}

// get number of seconds since this clocks creation
int64_t Clock::getTimeSeconds()
{
	return std::chrono::duration_cast<std::chrono::seconds>(m_timer.now() - m_creationTime).count();
}

// get number of milliseconds since this clocks creation
int64_t Clock::getTimeMilliseconds()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(m_timer.now() - m_creationTime).count();
}

// get number of milliseconds since this clocks creation
int64_t Clock::getTimeMicroseconds()
{
	return std::chrono::duration_cast<std::chrono::microseconds>(m_timer.now() - m_creationTime).count();
}

void Clock::update()
{
	deltaTime = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(m_timer.now() - m_lastTime).count() / 1000.0f;
	m_lastTime = m_timer.now();
}

float Clock::getDeltaTime()
{
	return deltaTime;
}

