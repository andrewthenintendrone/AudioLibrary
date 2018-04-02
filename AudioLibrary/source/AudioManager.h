#pragma once
#include "fmod\fmod.hpp"
#include <list>
#include <utility>

class AudioManager
{
public:

	static AudioManager& getInstance();

	void update();

	bool preloadAudio(const std::string& filename);

	bool playAudio(const std::string& filename);
	bool playStream(const std::string& filename);

private:

	// constructor
	AudioManager();

	// destructor
	~AudioManager();

	bool init();

	FMOD::System* m_soundSystem = nullptr;

	// list of audio with keys
	std::list<std::pair<FMOD::Sound*, std::string>> m_audio;
};
