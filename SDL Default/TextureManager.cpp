#include "TextureManager.h"

using namespace std;



TextureManager::TextureManager()
{

}

/// @brief Texture manager deconstructor
TextureManager::~TextureManager()
{
	for (auto value : m_textureMap)
	{
		delete value.second;
		value.second = nullptr;
	}
}

/// @brief unloads textures within the program
/// @param fileName 
void TextureManager::Unload(const string fileName)
{
	auto searchResult = m_textureMap.find(fileName);
	if(searchResult != m_textureMap.end())
	{
		delete m_textureMap[fileName];
		m_textureMap[fileName] = nullptr;
		m_textureMap.erase(searchResult);
	}
}

TextureManager* TextureManager::GetInstance()
{
	if (!instance)
	{
		instance = new TextureManager();
	}
	return instance;
}

/// @brief loads a texture based on the file name
/// @param fileName 
/// @param useTransparancy 
/// @param PRenderer 
/// @return 
SDL_Texture* TextureManager::Load(const string fileName, bool useTransparancy, SDL_Renderer* PRenderer)
{
	SDL_Texture* m_pbitmapTexture = nullptr;
	
	//check map for file name existance
	auto searchresult = m_textureMap.find(fileName);
	if (searchresult != m_textureMap.end())
	{
		m_pbitmapTexture = m_textureMap[fileName];
	}
	else // not found, load, save and return
	{

		//if file does not exist in map
		SDL_Surface* pTempSurface = SDL_LoadBMP(fileName.c_str());
		if (!pTempSurface)
		{
			printf("SURFACE for bitmap '%s' not loaded\n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}
		else
		{
			if (useTransparancy)
			{
				Uint32 colourKey = SDL_MapRGB(pTempSurface->format, 255, 0, 255);
				SDL_SetColorKey(pTempSurface, SDL_TRUE, colourKey);
			}
			m_pbitmapTexture = SDL_CreateTextureFromSurface(PRenderer, pTempSurface);
			if (!m_pbitmapTexture)
			{
				printf("TEXTURE for bitmap '%s' not loaded!\n", fileName.c_str());
				printf("%s\n", SDL_GetError());
			}

			m_textureMap[fileName] = m_pbitmapTexture;
		}
	}
	return m_pbitmapTexture;
}

TextureManager* TextureManager::instance = 0;