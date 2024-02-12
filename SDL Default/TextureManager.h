#pragma once
#include <map>
#include <SDL.h>
#include <string>

using namespace std;

class TextureManager
{
public:
	map<string, SDL_Texture*> m_textureMap;
	TextureManager();
	~TextureManager();


	SDL_Texture* Load(const string fileName, bool useTransparancy, SDL_Renderer* PRenderer);

	void Unload(const string fileName);

	static TextureManager* GetInstance();
	

private:

	static TextureManager* instance;

};

