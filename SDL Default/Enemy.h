#pragma once
#include "Bitmap.h"


class Enemy :public Bitmap
{
public:
	Enemy(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = true);
	~Enemy();

	virtual void Update() override;

	void HandleCollisions(std::vector<Bitmap*> scenehir);

};