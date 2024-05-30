#include "Hero.h"
#include <string>

#include "TextureManager.h"

#include "Input.h"

#include "SDL.h"
#include "SDL_render.h"


Hero::Hero(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency)
{
	m_pRenderer = renderer;

	FileName = fileName;

	m_x = xpos;
	m_y = ypos;

	mPosX = xpos;
	mPosY = ypos;




	m_pbitmapSurface = SDL_LoadBMP(fileName.c_str());
	if (!m_pbitmapSurface)
	{
		printf("Surface For Bitmap '%s' Not Loaded! \n", fileName.c_str());
		printf("%s\n", SDL_GetError());
	}
	else
	{
		if (useTransparency)
		{
			Uint32 colourKey = SDL_MapRGB(m_pbitmapSurface->format, 255, 0, 255);
			SDL_SetColorKey(m_pbitmapSurface, SDL_TRUE, colourKey);
		}

		//m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
		m_pbitmapTexture = TextureManager::GetInstance()->Load(FileName, true, m_pRenderer);

		if (!m_pbitmapTexture)
		{
			printf("Texture For Bitmap '%s' Not Loaded! \n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}
	}

	int width = GetObjWidth();
	mCollider.r = width / 2;
	ShiftCollider();
}

Hero::~Hero()
{

}

void Hero::Update()
{
	if (Input::Instance()->KeyIsPressed(KEY_W))
	{
		m_y--;
	}
	if (Input::Instance()->KeyIsPressed(KEY_S))
	{
		m_y++;
	}
	if (Input::Instance()->KeyIsPressed(KEY_A))
	{
		 m_x--;
	}
	if (Input::Instance()->KeyIsPressed(KEY_D))
	{
		m_x++;
	}
}