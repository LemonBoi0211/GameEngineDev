#pragma once
#include "Bitmap.h"



class Hero:public Bitmap
{
public:
	Hero(SDL_Renderer* renderer, std::string fileName,int xpos, int ypos, bool useTransparency = true);
	~Hero();

	virtual void Update() override;



};