#pragma once
#include "Bitmap.h"

/// @brief overrides the bitmap update so that this can have its own update
class Enemy : public Bitmap
{
	virtual void Update() override;
};