#include <string>
#include "bitmap.h"

#include "Input.h"

#include "SDL.h"
#include "SDL_render.h"

using namespace std;

Bitmap::Bitmap(SDL_Renderer* renderer, string fileName,int xpos, int ypos, bool useTransparency ) 
{
	m_pRenderer = renderer;

	m_x = xpos;
	m_y = ypos;

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

		m_pbitmapTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pbitmapSurface);
		if (!m_pbitmapTexture)
		{
			printf("Texture For Bitmap '%s' Not Loaded! \n", fileName.c_str());
			printf("%s\n", SDL_GetError());
		}
	}
}

//draws the bitmap
void Bitmap::Draw()
{
	if (m_pbitmapTexture) 
	{
		SDL_Rect destRect = { m_x, m_y, m_pbitmapSurface->w,m_pbitmapSurface->h };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
	
}

//update for the bitmap to allow the sprite to be moved via player input
void Bitmap::Update()
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

Bitmap::~Bitmap() 
{
	if(m_pbitmapTexture)
		SDL_DestroyTexture(m_pbitmapTexture);
	if (m_pbitmapSurface)
		SDL_FreeSurface(m_pbitmapSurface);
}