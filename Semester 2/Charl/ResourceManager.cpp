#include "pch.h"
#include "ResourceManager.h"

#include "TextureManager.h"
#include "SoundEffectManager.h"

TextureManager* ResourceManager::c_TextureManager{nullptr};
SoundEffectManager* ResourceManager::c_SoundEffectManager{nullptr};

void ResourceManager::Init(const std::string& filePath)
{
	if (c_TextureManager || c_SoundEffectManager)
	{
		return;
	}
	c_TextureManager = new TextureManager{ filePath };
	c_SoundEffectManager = new SoundEffectManager{ filePath };
}

void ResourceManager::CleanUp()
{
	delete c_TextureManager;
	c_TextureManager = nullptr;
	delete c_SoundEffectManager;
	c_SoundEffectManager = nullptr;
}

Texture* ResourceManager::GetTexture(ResourceManager::Textures key)
{
	std::string str{ KeyToStr(key) };
	if (str.empty())
	{
		return nullptr;
	}
	return GetTexture(str);
}

Texture* ResourceManager::GetTexture(const std::string& name)
{
    return c_TextureManager->GetTexture(name);
}

SoundEffect* ResourceManager::GetSoundEffect(ResourceManager::SoundEffects key)
{
	return c_SoundEffectManager->GetSoundEffect(KeyToStr(key));
}

SoundEffect* ResourceManager::GetSoundEffect(const std::string& name)
{
	return c_SoundEffectManager->GetSoundEffect(name);
}

SoundEffect* ResourceManager::Play(const std::string& name, int loops)
{
	return c_SoundEffectManager->Play(name,loops);
}

void ResourceManager::MuteAll()
{
	c_SoundEffectManager->MuteAll();
}

void ResourceManager::UnmuteAll()
{
	c_SoundEffectManager->UnmuteAll();
}

void ResourceManager::StopAll()
{
	c_SoundEffectManager->StopAll();
}

void ResourceManager::PauseAll()
{
	c_SoundEffectManager->PauseAll();
}

void ResourceManager::ResumeAll()
{
	c_SoundEffectManager->ResumeAll();
}

std::string ResourceManager::KeyToStr(ResourceManager::Textures key)
{
	switch (key)
	{
	case ResourceManager::Textures::missing:
		return "missing";
		break;
	default:
		break;
	}
    return std::string();
}

std::string ResourceManager::KeyToStr(ResourceManager::SoundEffects key)
{
	switch (key)
	{
	case ResourceManager::SoundEffects::test:
		return "test";
		break;
	default:
		break;
	}
	return std::string();
}
