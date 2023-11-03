#include "SDL.h"
#include "game.h"

#include "bitmap.h"

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