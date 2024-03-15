#ifndef GAME_H
#define GAME_H
#include <string>
#include <SDL.h>
#include "SDL_ttf.h"
#include <stdio.h>
#include <vector>
#include "DetailsPanel.h"

using namespace std;

struct SDL_Window;
struct SDL_Renderer;
class Bitmap;

struct ImVec2;

class Game 
{
private:
	/// @brief sdl stuff
	SDL_Window* m_Window;
	SDL_Renderer *m_Renderer;

	/// @brief bitmaps
	Bitmap* m_monsterTransKeyed;

	/// @brief scene hierarchy
	vector<Bitmap*> sceneHier;
	vector<Bitmap*> sceneTwo;

	/// @brief font variable names for setup
	TTF_Font* m_pSmallFont;
	TTF_Font* m_pBigFont;

	/// @brief stuff for display color
	Uint8 r = 127, g = 127, b = 127, a = 255;

	/// @brief stuff for Imgui
	vector<Bitmap*> content;
	Bitmap* assetMousDrag;
	Bitmap* gameobjSelect(ImVec2 mousePos);
	DetailsPanel* detailsPanel;


public:
	Game();
	~Game();
	
	/// @brief 
	/// @param R 
	/// @param G 
	/// @param B 
	/// @param A 
	void SetDisplayColour(Uint8 R, Uint8 G, Uint8 B, Uint8 A);
	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);

	/// @brief 
	void Update();
	void CheckEvents();
	void Run();

	/// @brief save and load stuff
	void Save();
	void Load();

};


#endif