#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

TextureManager::~TextureManager()
{
    for (std::pair<std::string, Texture*> pair : m_Map)
    {
        delete pair.second;
    }
    m_Map.clear();
}

Texture* TextureManager::GetTexturePointer(const std::string& filename)
{
    if (m_Map.find(filename) == m_Map.end()) // Not found in map
    {
        m_Map[filename] = new Texture{ filename };
    }
    return m_Map[filename];

#pragma region Alternative Method
    if (!m_Map[filename])
    {
        m_Map[filename] = new Texture{ filename };
    }
    return m_Map[filename];
#pragma endregion

}
