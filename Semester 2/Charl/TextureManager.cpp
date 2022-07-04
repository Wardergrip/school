#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include <fstream>
#include <iostream>

std::map<std::string, Texture*> TextureManager::m_pTextures{};

Texture* TextureManager::GetTexture(const std::string& name)
{
	return (m_pTextures[name]);
}

Texture* TextureManager::GetTexture(Key key)
{
	std::string str{ KeyToString(key) };
	if (str.empty())
	{
		return nullptr;
	}
	return GetTexture(str);
}

void TextureManager::InitiateTexturesFromFile(const std::string& filepath)
{
	using json = nlohmann::json;
	std::ifstream input{ filepath };
	json jFile{};
	input >> jFile;
	json jTextures{ jFile.at("textures") };
	//std::cout << std::setw(4) << jTextures << '\n';
	for (json::iterator it = jTextures.begin(); it != jTextures.end(); ++it)
	{
		//std::cout << it.key() << " : " << it.value() << "\n";
		m_pTextures[it.key()] = new Texture{it.value()};
	}
}

void TextureManager::CleanUp()
{
	for (std::pair<std::string, Texture*> pair : m_pTextures)
	{
		delete pair.second;
	}
	m_pTextures.clear();
}

std::string TextureManager::KeyToString(Key k)
{
	switch (k)
	{
	case TextureManager::missing:
		return "missing";
		break;
	default:
		break;
	}
	return std::string();
}
