#pragma once
#include <cstdint>

// holds info about an input event
struct InputEvent
{
	char KeyCode = 'a'; // key that was involved in the event
	int64_t TimeStamp = 0; // time that the event occured
};