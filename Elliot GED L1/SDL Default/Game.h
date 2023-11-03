#ifndef GAME_H
#define GAME_H
#include <string>
#include <SDL.h>
#include "SDL_ttf.h"
#include <stdio.h>

using namespace std;

struct SDL_Window;
struct SDL_Renderer;
class Bitmap;



class Game 
{
private:
	//sdl stuff
	SDL_Window* m_Window;
	SDL_Renderer *m_Renderer;

	//bitmaps
	Bitmap* m_monsterTransKeyed;

	//font stuff
	TTF_Font* m_pSmallFont;
	TTF_Font* m_pBigFont;

	//stuff for display color
	Uint8 r = 127, g = 127, b = 127, a = 255;

public:
	Game();
	~Game();
	
	void SetDisplayColour(Uint8 R, Uint8 G, Uint8 B, Uint8 A);
	void Update();
	void CheckEvents();
	void UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour);
	void Run();
};


#endif