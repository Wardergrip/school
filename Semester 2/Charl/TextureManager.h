#pragma once
#include <map>

class Texture;

class TextureManager final
{
public:
	enum Key{ missing };
	TextureManager() = delete;

	static Texture* GetTexture(const std::string& name);
	static Texture* GetTexture(Key key);
	static void InitiateTexturesFromFile(const std::string& filepath);

	static void CleanUp();
private:
	static std::string KeyToString(Key k);
	static std::map<std::string, Texture*> m_pTextures;
};

