#include "SDL.h"
#include "Game.h"
#include "Input.h"
#include "Bitmap.h"
#include <iostream>
#include <SDL_ttf.h>


	Game::Game()
	{
		m_Window = nullptr;
		m_Renderer = nullptr;


		//start up
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();

		//create the window
		m_Window = SDL_CreateWindow(
			"My First Window",  //title
			250,                //initial x pos
			50,                 //initial y pos
			640,                //width in pixels
			480,                //height in pixels
			0                   //window behaviour flags(ignore atm)
		);

		if (!m_Window)
		{
			printf("Window Initialisaition Failed: %s\n", SDL_GetError());
			printf("Press Any Key To Continue\n");
			getchar();
			return;
		}

		//create renderer
		m_Renderer = SDL_CreateRenderer(
			m_Window,   //link renderer to created window
			-1,         //index rendering drive(ignore)
			0           //renderer behaviour flags(ignore)
		);

		if (!m_Renderer)
		{
			printf("Renderer Initialisation Failed: %s\n", SDL_GetError());
			printf("Press Any Key To Continue\n");
			getchar();
			return;
		}

		//create monster bitmap
		m_monsterTransKeyed = new Bitmap(m_Renderer, "./assets/monsterTrans.bmp", 300, 100);

		//read in font
		m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf", 15);
		m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf", 50);

	}

	void Game::UpdateText(string msg, int x, int y, TTF_Font* font, SDL_Color colour) 
	{
		SDL_Surface* surface = nullptr;
		SDL_Texture* texture = nullptr;

		int texW = 0;
		int texH = 0;

		surface = TTF_RenderText_Solid(font, msg.c_str(), colour);
		if (!surface) 
		{
			printf("SURFACE For Font Not Loaded! \n");
			printf("%s\n", SDL_GetError());
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
			if (!texture)
			{
				printf("TEXTURE For Font Not Loaded! \n");
				printf("%s\n", SDL_GetError());
			}
			else
			{
				SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
				SDL_Rect textRect = { x,y,texW,texH };

				SDL_RenderCopy(m_Renderer, texture, NULL, &textRect);
			}
		}

		if (texture)
			SDL_DestroyTexture(texture);

		if (surface)
			SDL_FreeSurface(surface);
	}

	void Game::Run()
	{
		while (!Input::Instance()->KeyIsPressed(KEY_ESCAPE))
		{
			Input::Instance()->Update();

			//change colour of bg
			if (Input::Instance()->KeyIsPressed(KEY_R))
			{
				if (++r > 255) r = 0;
			}

			if (Input::Instance()->KeyIsPressed(KEY_G))
			{
				if (++g > 255) g = 0;
			}

			if (Input::Instance()->KeyIsPressed(KEY_B))
			{
				if (++b > 255) b = 0;
			}


			SetDisplayColour(r, g, b, a);
			Update();
		}
	}

	void Game::SetDisplayColour(Uint8 R, Uint8 G, Uint8 B, Uint8 A)
	{
		if (m_Renderer)
		{
			int result = SDL_SetRenderDrawColor(
				m_Renderer,
				R,
				G,
				B,
				A
			);
		}
	}

	void Game::Update()
	{
		//clears display
		SDL_RenderClear(m_Renderer);

		CheckEvents();

		m_monsterTransKeyed->Update();
		//display bitmap
		m_monsterTransKeyed->Draw();

		//draws text
		UpdateText("Small Red", 50, 10, m_pSmallFont, { 255,0,0 });
		UpdateText("Big Blue", 50, 40, m_pBigFont, { 0,0,255 });

		char char_array[] = "Big White";
		UpdateText(char_array, 50, 140, m_pBigFont, { 255,255,255 });

		string MyString = "Big Green";
		UpdateText(MyString, 50, 70, m_pBigFont, { 0,255,0 });

		int testNumber = 69420;
		string testString = "Test Number: ";
		testString += to_string(testNumber);
		UpdateText(testString, 50, 210, m_pBigFont, { 255,255,255 });

		//shows what drawn
		SDL_RenderPresent(m_Renderer);

		SDL_Delay(16);

	}

	void Game::CheckEvents()
	{

	}

	Game::~Game()
	{
		
		//clean up
		//destroy reverse order

		//destroy fonts
		TTF_CloseFont(m_pBigFont);
		TTF_CloseFont(m_pSmallFont);

		//destroy bitmaps
		if (m_monsterTransKeyed)
			delete m_monsterTransKeyed;

		if (m_Renderer)
		{
			SDL_DestroyRenderer(m_Renderer);
		}

		if (m_Window)
		{
			SDL_DestroyWindow(m_Window);
		}
	}
