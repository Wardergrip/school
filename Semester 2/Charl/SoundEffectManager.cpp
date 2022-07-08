#include "pch.h"
#include "SoundEffectManager.h"
#include "SoundEffect.h"
#include <fstream>
#include <iostream>

SoundEffectManager::SoundEffectManager(const std::string& filePath)
	:m_pPreviousVolumes{}
{
	using json = nlohmann::json;
	std::ifstream input{ filePath };
	try
	{
		if (input.fail())
		{
			throw 1;
		}
	}
	catch (int errC)
	{
		if (errC == 1)
		{
			std::cout << "[SoundEffectManager] Failed to load: " << filePath << "\n";
			return;
		}
	}
	json jFile{};
	input >> jFile;
	json jTextures{ jFile.at("soundeffects") };
	//std::cout << std::setw(4) << jTextures << '\n';
	for (json::iterator it = jTextures.begin(); it != jTextures.end(); ++it)
	{
		//std::cout << it.key() << " : " << it.value() << "\n";
		m_pSoundEffects[it.key()] = new SoundEffect{ it.value() };
	}
}

SoundEffectManager::~SoundEffectManager()
{
	for (std::pair<std::string, SoundEffect*> pair : m_pSoundEffects)
	{
		delete pair.second;
	}
	m_pSoundEffects.clear();
}

SoundEffect* SoundEffectManager::operator[](const std::string& name)
{
	return GetSoundEffect(name);
}

const SoundEffect* SoundEffectManager::operator[](const std::string& name) const
{
	return GetSoundEffect(name);
}

SoundEffect* SoundEffectManager::GetSoundEffect(const std::string& name)
{
	return m_pSoundEffects[name];
}

const SoundEffect* SoundEffectManager::GetSoundEffect(const std::string& name) const
{
	return m_pSoundEffects.at(name);
}

SoundEffect* SoundEffectManager::Play(const std::string& name, int loops)
{
	GetSoundEffect(name)->Play(loops);
	return GetSoundEffect(name);
}

const SoundEffect* SoundEffectManager::Play(const std::string& name, int loops) const
{
	GetSoundEffect(name)->Play(loops);
	return GetSoundEffect(name);
}

void SoundEffectManager::MuteAll()
{
	m_pPreviousVolumes.reserve(m_pSoundEffects.size());
	for (auto pair : m_pSoundEffects)
	{
		m_pPreviousVolumes.push_back(pair.second->GetVolume());
		pair.second->SetVolume(0);
	}
}

void SoundEffectManager::UnmuteAll()
{
	int ticker{ 0 };
	for (auto pair : m_pSoundEffects)
	{
		pair.second->SetVolume(m_pPreviousVolumes[ticker]);
		++ticker;
	}
	m_pPreviousVolumes.clear();
}

void SoundEffectManager::StopAll()
{
	SoundEffect::StopAll();
}

void SoundEffectManager::PauseAll()
{
	SoundEffect::PauseAll();
}

void SoundEffectManager::ResumeAll()
{
	SoundEffect::ResumeAll();
}
