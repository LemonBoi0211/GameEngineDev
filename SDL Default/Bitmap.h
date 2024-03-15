#pragma once
#include "I_GUIWindow.h"
#include <string>

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

struct Vector2 
{ 
	Vector2(float x, float y) : X(x), Y(y) {};

	float X;
	float Y;
};

struct Circle
{
	int x, y;
	int r;
};

class Bitmap:public I_GUIWindow
{
private:

	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

protected:
	int m_x, m_y;
	int mPosX, mPosY;
	int mVelX, mVelY;
	Circle mCollider;
	static const int DOT_VEL = 1;

public:
	Bitmap(SDL_Renderer* renderer, std::string fileName,int xpos, int ypos, bool useTransparency = true);
	virtual ~Bitmap();

	virtual SDL_Texture* GetTextureRef()
	{
		return m_pbitmapTexture;
	}

	virtual void Draw();

	std::string FileName;

	// Updates the Bitmap logic
	virtual void Update();

	// Inherited via I_GUIWindow
	virtual void GuiDraw() override;



	//Get Set m_x m_y
	virtual int GetOBJPosX();
	virtual int SetOBJPosX(int newObjX);

	virtual int GetOBJPosY();
	virtual int SetOBJPosY(int newObjY);

	//Get bmp/obj width and height
	virtual int GetObjWidth();
	virtual int GetObjHeight();

	//collider function
	Circle& GetCollider();
	void ShiftCollider();

	//Circle/Circle collision detector
	bool checkCollision(Circle& a, Circle& b);

	//Calculates distance squared between two points
	double distanceSquared(int x1, int y1, int x2, int y2);


	//save/load stuff
	virtual std::string SaveData();
};