#pragma once
#include "I_GUIWindow.h"
#include <string>

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class Bitmap:public I_GUIWindow
{
private:

	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

	int m_x, m_y;

public:
	Bitmap(SDL_Renderer* renderer, std::string fileName,int xpos, int ypos, bool useTransparency = true);
	~Bitmap();

	SDL_Texture* GetTextureRef() 
	{
		return m_pbitmapTexture;
	}

	void Draw();

	std::string FileName;

	// Updates the Bitmap logic
	void Update(); 

	// Inherited via I_GUIWindow
	void GuiDraw() override;

	//Get Set m_x m_y
	int GetOBJPosX();
	int SetOBJPosX(int newObjX);

	int GetOBJPosY();
	int SetOBJPosY(int newObjY);

	//Get bmp/obj width and height
	int GetObjWidth();
	int GetObjHeight();
};