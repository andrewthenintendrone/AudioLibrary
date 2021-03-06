#include "AudioManager.h"
#include <iostream>
#include "fmod\fmod_errors.h"
#include <string>

// get the instance of AudioManager (singleton)
AudioManager& AudioManager::getInstance()
{
	static AudioManager instance;
	return instance;
}

// updates FMOD sound system
void AudioManager::update()
{
	m_soundSystem->update();
}

// ensure an audio file is in memory to prevent stuttering
bool AudioManager::preloadAudio(const std::string& filename)
{
	for (auto it = m_audio.begin(); it != m_audio.end(); it++)
	{
		if (it->second == filename)
		{
			// the file has already been loaded
			return true;
		}
	}

	// load the new audio file
	FMOD::Sound* sound;

	FMOD_RESULT result = m_soundSystem->createSound(filename.c_str(), FMOD_CREATESAMPLE | FMOD_2D, 0, &sound);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
		return false;
	}

	// add audio file to the list
	m_audio.push_back(std::pair<FMOD::Sound*, std::string>(sound, filename));

	return true;
}

// play an audio file
bool AudioManager::playAudio(const std::string& filename)
{
	FMOD_RESULT result;
	FMOD::Channel* pchannel;

	for (auto it = m_audio.begin(); it != m_audio.end(); it++)
	{
		// play already loaded audio
		if (it->second == filename)
		{
			result = m_soundSystem->playSound(it->first, 0, false, &pchannel);

			if (result != FMOD_OK)
			{
				std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
				return false;
			}

			return true;
		}
	}

	// new audio file load it
	FMOD::Sound* sound;

	result = m_soundSystem->createSound(filename.c_str(), FMOD_CREATESAMPLE | FMOD_2D, 0, &sound);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
		return false;
	}

	m_audio.push_back(std::pair<FMOD::Sound*, std::string>(sound, filename));
	m_soundSystem->playSound(sound, 0, false, &pchannel);

	return true;
}

// stream audio file
bool AudioManager::playStream(const std::string& filename)
{
	FMOD_RESULT result;
	FMOD::Channel* pchannel;

	for (auto it = m_audio.begin(); it != m_audio.end(); it++)
	{
		// play already loaded audio
		if (it->second == filename)
		{
			result = m_soundSystem->playSound(it->first, 0, false, &pchannel);

			if (result != FMOD_OK)
			{
				std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
				return false;
			}

			return true;
		}
	}

	// new audio file load it
	FMOD::Sound* sound;

	result = m_soundSystem->createSound(filename.c_str(), FMOD_CREATESTREAM | FMOD_2D, 0, &sound);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
		return false;
	}

	m_audio.push_back(std::pair<FMOD::Sound*, std::string>(sound, filename));
	m_soundSystem->playSound(sound, 0, false, &pchannel);

	return true;
}

AudioManager::AudioManager()
{
	init();
}

AudioManager::~AudioManager()
{
	// cleanup fmod
	for (auto it = m_audio.begin(); it != m_audio.end(); it++)
	{
		it->first->release();
	}

	m_audio.clear();
	m_soundSystem->close();
	m_soundSystem->release();
}

bool AudioManager::init()
{
	FMOD_RESULT result;

	// create sound system
	result = FMOD::System_Create(&m_soundSystem);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
		return false;
	}

	// Initialize FMOD with 512 channels
	result = m_soundSystem->init(512, FMOD_2D, 0);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
		return false;
	}

	return true;
}
