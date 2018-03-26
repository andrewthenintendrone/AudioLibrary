#pragma once
#include <cstdint>

// holds info about an input event
struct InputEvent
{
	char Key; // key that was involved in the event
	int64_t TimeStamp; // time that the event occured
};