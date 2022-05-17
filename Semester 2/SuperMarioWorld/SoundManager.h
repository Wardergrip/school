#pragma once
#include <map>
class SoundEffect;
class SoundStream;
class SoundManager final
{
public:
	SoundManager() = delete;
	SoundManager(const SoundManager& s) = delete;
	SoundManager& operator=(const SoundManager& s) = delete;
	SoundManager(SoundManager&& s) = delete;
	SoundManager& operator=(SoundManager&& s) = delete;
	~SoundManager() = delete;

	// Volume is by default full volume (100)
	static SoundEffect* GetSoundEffect(const std::string& filename);
	// Volume is by default full volume (100)
	static SoundStream* GetSoundStream(const std::string& filename);
	// true = full volume
	static void ToggleSound(bool state);

	static void CleanUp();

private:
	static std::map<std::string, SoundEffect*> m_pSoundEffects;
	static std::map<std::string, SoundStream*> m_pSoundStreams;

	static int m_FullVolume;
};

