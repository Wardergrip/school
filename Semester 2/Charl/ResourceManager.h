#pragma once

#include "TextureManager.h"
#include "SoundEffectManager.h"
//class Texture;
//class SoundEffect;

class ResourceManager final
{
public:
	enum class Textures
	{
		missing
	};
	enum class SoundEffects
	{
		
	};

	ResourceManager() = delete;

	static Texture* GetTexture(ResourceManager::Textures key);
	static Texture* GetTexture(const std::string& name);

	static SoundEffect* GetSoundEffect(ResourceManager::SoundEffects key);
	static SoundEffect* GetSoundEffect(const std::string& name);
	static SoundEffect* Play(const std::string& name, int loops = 0);
	static void MuteAll();
	static void UnmuteAll();
	static void StopAll();
	static void PauseAll();
	static void ResumeAll();
private:
	static std::string KeyToStr(ResourceManager::Textures key);
	static std::string KeyToStr(ResourceManager::SoundEffects key);

	static TextureManager c_TextureManager;
	static SoundEffectManager c_SoundEffectManager;
};

