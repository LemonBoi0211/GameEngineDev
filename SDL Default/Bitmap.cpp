#include <string>
#include "bitmap.h"

#include "TextureManager.h"

#include "Input.h"

#include "SDL.h"
#include "SDL_render.h"
#include "Game.h"


using namespace std;

Bitmap::Bitmap()
{

}

/// @brief SetUp and inits for the Bitmap class
/// @param renderer 
/// @param fileName 
/// @param xpos 
/// @param ypos 
/// @param useTransparency 
Bitmap::Bitmap(SDL_Renderer* renderer, string fileName, int xpos, int ypos, Game* owningGame, bool useTransparency)
{
	m_pRenderer = renderer;

	FileName = fileName;
	
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
/// @brief draws the bitmap
void Bitmap::Draw()
{
	if (m_pbitmapTexture) 
	{
		SDL_Rect destRect = { m_x, m_y, m_pbitmapSurface->w, m_pbitmapSurface->h };
		SDL_RenderCopy(m_pRenderer, m_pbitmapTexture, NULL, &destRect);
	}
}

/// @brief gets an objects x position
/// @return returns objects current x position
int Bitmap::GetOBJPosX()
{
	return m_x;
}

/// @brief sets an objects x position
/// @param changes current x position with new objects x position
/// @return returns the objects new x position
int Bitmap::SetOBJPosX(int newObjX)
{
	m_x = newObjX;
	return m_x;
}

/// @brief 
/// @return returns objects current y position
int Bitmap::GetOBJPosY()
{
	return m_y;
}

/// @brief sets an objects y position
/// @param changes current y position with new objects y position
/// @return returns the objects new y position 
int Bitmap::SetOBJPosY(int newObjY)
{
	m_y = newObjY;
	return m_y;
}

/// @brief 
/// @return returns the objects current bitmap width
int Bitmap::GetObjWidth()
{
	return m_pbitmapSurface->w;
}

/// @brief 
/// @return returns the objects current bitmap height
int Bitmap::GetObjHeight()
{
	return m_pbitmapSurface->h;
}

/// @brief function used to find the collider attached to the object
/// @return returns the current collider attached to the object
Circle& Bitmap::GetCollider()
{
	return mCollider;
}

/// @brief offsets collider to center of an object
void Bitmap::ShiftCollider()
{
	//Align collider to center of dot
	mCollider.x = m_x;
	mCollider.y = m_y;
}

void Bitmap::HandleCollisions(std::vector<Bitmap*> scenehir)
{
	
}


/// @brief checks if a collision betwen 2 circles occured
/// @param a 
/// @param b 
/// @return returns a boolean if collisions have occured between objects
bool Bitmap::checkCollision(Circle& a, Circle& b)
{
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	//If the distance between the centers of the circles is less than the sum of their radii
	if (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared))
	{
		//The circles have collided
		return true;
	}

	//If not
	return false;
}

/// @brief  squares the distance between objects for collision calcs
/// @param x1 
/// @param y1 
/// @param x2 
/// @param y2 
/// @return returns the squared distance between object colliders
double Bitmap::distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

/// @brief gives some chars for the save file to differentiate between diff things
/// @return 
string Bitmap::SaveData()
{
	string gObjdata = "@";
	gObjdata += FileName;
	gObjdata += "-";

	gObjdata += to_string(m_x);
	gObjdata += "-";

	gObjdata += to_string(m_y);
	gObjdata += "|";

	return gObjdata;
}


void Bitmap::Update()
{
	
}

/// @brief  Draw Function for the Gui
void Bitmap::GuiDraw()
{
	ImGui::Begin("ObjName");

	//button for counting
	ImGui::AlignTextToFramePadding();
	ImGui::Text("Hold to Count Fast:");
	ImGui::SameLine();
	static int counter = 0;
	float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);

	if (ImGui::Button("Press to Count"))
	{
		ImGui::SameLine(0.0f, spacing);
		counter++;
	}

	ImGui::PopButtonRepeat();
	ImGui::SameLine();
	ImGui::Text("%d", counter);

	ImGui::End();
}

/// @brief Bitmap Deconstructor
Bitmap::~Bitmap() 
{
	
}
