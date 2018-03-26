#include <iostream>
#include "Clock.h"
#include "AudioManager.h"

int main(int argc, char* argv[])
{
	//AudioManager::getInstance().playStream("C:/Users/s170837/Documents/AudioLibrary/AudioLibrary/bin/music.mp3");

	Clock clock;

	//clock.recordTiming();
	//clock.writeTiming("C:/Users/s170837/Desktop/timings.txt");
	clock.readTiming("C:/Users/s170837/Desktop/timings.txt");
	clock.showTiming();

	std::cin.get();

	return 0;
}