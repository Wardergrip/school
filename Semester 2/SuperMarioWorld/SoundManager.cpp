#include "pch.h"
#include "SoundManager.h"
#include "SoundEffect.h"
#include "SoundStream.h"

std::map<std::string,SoundEffect*> SoundManager::m_pSoundEffects{};
std::map<std::string,SoundStream*> SoundManager::m_pSoundStreams{};

int SoundManager::m_FullVolume{ 100 };

SoundEffect* SoundManager::GetSoundEffect(const std::string& filename)
{
    if (m_pSoundEffects.find(filename) == m_pSoundEffects.end()) // Not found in map
    {
        m_pSoundEffects[filename] = new SoundEffect{ filename };
        m_pSoundEffects[filename]->SetVolume(m_FullVolume);
    }
    return m_pSoundEffects[filename];
}

SoundStream* SoundManager::GetSoundStream(const std::string& filename)
{
    if (m_pSoundStreams.find(filename) == m_pSoundStreams.end()) // Not found in map
    {
        m_pSoundStreams[filename] = new SoundStream{ filename };
        m_pSoundStreams[filename]->SetVolume(m_FullVolume);
    }
    return m_pSoundStreams[filename];
}

void SoundManager::ToggleSound(bool state)
{
    for (std::pair<std::string, SoundEffect*> pair : m_pSoundEffects)
    {
        pair.second->SetVolume((state ? m_FullVolume : 0));
    }
    for (std::pair<std::string, SoundStream*> pair : m_pSoundStreams)
    {
        pair.second->SetVolume((state ? m_FullVolume : 0));
    }
}

void SoundManager::CleanUp()
{
    for (std::pair<std::string, SoundEffect*> pair : m_pSoundEffects)
    {
        delete pair.second;
    }
    m_pSoundEffects.clear();

    for (std::pair<std::string, SoundStream*> pair : m_pSoundStreams)
    {
        delete pair.second;
    }
    m_pSoundEffects.clear();
}
