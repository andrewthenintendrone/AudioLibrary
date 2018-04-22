#include "GameObject.h"
#include "AudioManager.h"

void GameObject::playSound()
{
	AudioManager::getInstance().playAudio(m_soundEffect);
}