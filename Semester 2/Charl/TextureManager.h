#pragma once
#include <map>

class Texture;

class TextureManager final
{
public:
	enum class Key
	{ 
		missing 
	};

	TextureManager(const std::string& filePath);
	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;
	~TextureManager();

	Texture* GetTexture(const std::string& name);
	Texture* GetTexture(TextureManager::Key key);
private:
	static std::string KeyToString(Key k);
	std::map<std::string, Texture*> m_pTextures;
};

