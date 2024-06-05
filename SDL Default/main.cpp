#include "SDL.h"
#include <SDL_ttf.h>

#include "Game.h"


int main(int argc, char* argv[]) 
{
	Game* game = new Game();
	
	if (game)
	{
		game->Run();
	}

	delete game; 
	game = nullptr; 

	return 0;
}

//bitmap ("name", texturemanager(file location), 10,10)