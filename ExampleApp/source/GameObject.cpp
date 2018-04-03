#include "GameObject.h"
#include "AudioManager.h"

void GameObject::update(float dt)
{
	m_hitTimer = std::max(0.0f, m_hitTimer - dt);
}

void GameObject::playSound()
{
	AudioManager::getInstance().playAudio(m_soundEffect);
}