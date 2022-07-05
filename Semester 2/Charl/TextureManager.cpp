#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include <fstream>
#include <iostream>

TextureManager::TextureManager(const std::string& filePath)
{
	using json = nlohmann::json;
	std::ifstream input{ filePath };
	json jFile{};
	input >> jFile;
	json jTextures{ jFile.at("textures") };
	//std::cout << std::setw(4) << jTextures << '\n';
	for (json::iterator it = jTextures.begin(); it != jTextures.end(); ++it)
	{
		//std::cout << it.key() << " : " << it.value() << "\n";
		m_pTextures[it.key()] = new Texture{ it.value() };
	}
}

TextureManager::~TextureManager()
{
	for (std::pair<std::string, Texture*> pair : m_pTextures)
	{
		delete pair.second;
	}
	m_pTextures.clear();
}

Texture* TextureManager::GetTexture(const std::string& name)
{
	return (m_pTextures[name]);
}

Texture* TextureManager::GetTexture(TextureManager::Key key)
{
	std::string str{ KeyToString(key) };
	if (str.empty())
	{
		return nullptr;
	}
	return GetTexture(str);
}

std::string TextureManager::KeyToString(Key k)
{
	switch (k)
	{
	case TextureManager::Key::missing:
		return "missing";
		break;
	default:
		break;
	}
	return std::string();
}
