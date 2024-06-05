#pragma once
#include "Bitmap.h"


class MeatPickup :public Bitmap
{
public:
	MeatPickup(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, bool useTransparency = true);
	~MeatPickup();

	virtual void Update() override;

	virtual void HandleCollisions(std::vector<Bitmap*> scenehir) override;


};