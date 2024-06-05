#pragma once
#include "I_GUIWindow.h"
#include <string>
#include <vector>

class Game;

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

/// @param Vector2 Calculation
/// @brief calculates the bitmaps vector2
/// @return Returns an X and Y value 
struct Vector2 
{ 
	Vector2(float x, float y) : X(x), Y(y) {};

	float X;
	float Y;
};

/// @param Variables for a collision circle
/// @brief 
/// @return 
struct Circle
{
	int x, y;
	int r;
};

class Bitmap:public I_GUIWindow
{
protected:

	SDL_Surface* m_pbitmapSurface;
	SDL_Texture* m_pbitmapTexture;
	SDL_Renderer* m_pRenderer;

/// @brief variables for objects and collisions positions
protected:
	int m_x, m_y;
	int mPosX, mPosY;
	int mVelX, mVelY;
	Circle mCollider;
	static const int DOT_VEL = 1;


public:
	Bitmap();
	Bitmap(SDL_Renderer* renderer, std::string fileName, int xpos, int ypos, Game* owningGame, bool useTransparency = true);
	virtual ~Bitmap();

	virtual SDL_Texture* GetTextureRef()
	{
		return m_pbitmapTexture;
	}

	virtual void Draw();

	std::string FileName;

	/// @brief Updates the Bitmap logic
	virtual void Update();

	/// @brief Inherited via I_GUIWindow
	virtual void GuiDraw() override;

	

	/// @brief Get Set X and Y
	/// @param allows the system to find and set the gameobjs x and y pos
	/// @return The X and Y value and Sets X and Y values
	virtual int GetOBJPosX();
	virtual int SetOBJPosX(int newObjX);

	virtual int GetOBJPosY();
	virtual int SetOBJPosY(int newObjY);

	///Get bmp/obj width and height
	virtual int GetObjWidth();
	virtual int GetObjHeight();

	///collider function
	Circle& GetCollider();
	void ShiftCollider();

	virtual void HandleCollisions(std::vector<Bitmap*> scenehir);

	///Circle/Circle collision detector
	bool checkCollision(Circle& a, Circle& b);

	///Calculates distance squared between two points
	double distanceSquared(int x1, int y1, int x2, int y2);


	///save/load stuff
	virtual std::string SaveData();
};