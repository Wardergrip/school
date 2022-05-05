#pragma once
#include <unordered_map>
class Texture;
using MyMap = std::unordered_map<std::string, Texture*>;

class TextureManager final
{
public:
	TextureManager(TextureManager& textureManager) = delete;
	TextureManager& operator=(TextureManager& textureManager) = delete;
	TextureManager(TextureManager&& textureManager) = delete;
	TextureManager& operator=(TextureManager&& textureManager) = delete;
	~TextureManager();

	Texture* GetTexturePointer(const std::string& filename);

private:
	MyMap m_Map;
};

