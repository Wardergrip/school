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
		test
	};

	ResourceManager() = delete;

	static void Init(const std::string& filePath);
	static void CleanUp();

	static Texture* GetTexture(ResourceManager::Textures key);
	static Texture* GetTexture(const std::string& name);

	static SoundEffect* GetSFX(ResourceManager::SoundEffects key);
	static SoundEffect* GetSFX(const std::string& name);
	static SoundEffect* SFXPlay(const std::string& name, int loops = 0);
	static void SFXMuteAll();
	static void SFXUnmuteAll();
	static void SFXStopAll();
	static void SFXPauseAll();
	static void SFXResumeAll();
private:
	static std::string KeyToStr(ResourceManager::Textures key);
	static std::string KeyToStr(ResourceManager::SoundEffects key);

	static TextureManager* c_TextureManager;
	static SoundEffectManager* c_SoundEffectManager;
};

