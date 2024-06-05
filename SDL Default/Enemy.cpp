#include "Enemy.h"
#include <string>

#include "TextureManager.h"

#include "Input.h"

#include "SDL.h"
#include "SDL_render.h"
#include <ostream>


Enemy::Enemy(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency)
{
	m_pRenderer = renderer;

	FileName = fileName;

	m_x = xpos;
	m_y = ypos;

	mPosX = xpos;
	mPosY = ypos;

	mVelX = 0;
	mVelY = 0;

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

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	m_x += mVelX;
	if (m_x > 900)
	{
		mVelX = -3;
	}
	else if (m_x < 150)
	{
		mVelX = 3;
	}

	m_y += mVelY;
	if (m_y > 800)
	{
		mVelY = -3;
	}
	else if (m_y < 150)
	{
		mVelY = 3;
	}
}

void Enemy::HandleCollisions(std::vector<Bitmap*> scenehir)
{
	for (Bitmap* other : scenehir)
	{
		if (checkCollision(this->GetCollider(), other->GetCollider()))
		{
			SDL_Quit;
		}
	}
}