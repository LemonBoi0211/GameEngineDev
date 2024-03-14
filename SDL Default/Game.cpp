#include "SDL.h"
#include "Game.h"
#include "Input.h"
#include "Bitmap.h"
#include <iostream>
#include <SDL_ttf.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"
#include <filesystem>
#include <io.h>
#include "Profiler.h"
#include <fstream>
#include "TextureManager.h"


Bitmap* Game::gameobjSelect(ImVec2 mousePos)
{
	for (Bitmap* gameObj: sceneHier)
	{
		if (mousePos.x >= gameObj->GetOBJPosX() && mousePos.x <= gameObj->GetOBJPosX() + gameObj->GetObjWidth() 
			&& mousePos.y >= gameObj->GetOBJPosY() && mousePos.y <= gameObj->GetOBJPosY() + gameObj->GetObjHeight())
		{
			return gameObj;
		}
		
	}

	return nullptr;
}


Game::Game()
{
		m_Window = nullptr;
		m_Renderer = nullptr;


		//start up
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();


		//create the window
		m_Window = SDL_CreateWindow(
			"My First Window",             //title
			SDL_WINDOWPOS_CENTERED,        //initial x pos
			SDL_WINDOWPOS_CENTERED,        //initial y pos
			1200,                          //width in pixels
			1000,                          //height in pixels
			SDL_WINDOW_RESIZABLE           //window behaviour flags(ignore atm)
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

		//ImGUI Setup

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		SDL_DisplayMode DisplayMode;
		SDL_GetCurrentDisplayMode(0, &DisplayMode);
		ImGuiSDL::Initialize(m_Renderer, DisplayMode.w, DisplayMode.h);
		ImGuiIO& io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnabled;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());


		//ImGUI asset window
		std::string path = "../SDL Default/assets";
		for (const auto& entry : std::filesystem::directory_iterator(path)) //directory_iterator(path) //recursive_
		{
			if (entry.path().extension() == ".bmp" || entry.path().extension() == ".jpg" || entry.path().extension() == ".png")
			{
				Bitmap* Asset = new Bitmap(m_Renderer, entry.path().string(), 0, 0, true);
				content.push_back(Asset);

			}
			else if (entry.is_directory())
			{
				std::cout << "dir " << entry << std::endl;
			}
			//debug
			std::cout << entry.path() << std::endl;
		}

		//Details Panel
		detailsPanel = new DetailsPanel(&sceneHier);

		//create monster bitmap
		m_monsterTransKeyed = new Bitmap(m_Renderer, "./assets/monsterTrans.bmp", 300, 100);

		sceneHier.push_back(m_monsterTransKeyed);
		sceneTwo.push_back(m_monsterTransKeyed);

		//read in font
		m_pSmallFont = TTF_OpenFont("assets/DejaVuSans.ttf", 15);
		m_pBigFont = TTF_OpenFont("assets/DejaVuSans.ttf", 50);

}

	//method for adding and using font for text
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

	//allows control of changing the background colour
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

	//change background colour with RGB keys
	void Game::Run()
	{
		while (!Input::Instance()->KeyIsPressed(KEY_ESCAPE))
		{
			Input::Instance()->Update();

			//change colour of background with respective keys
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

	//save and load functions
	void Game::Save()
	{
		string saveFileName = "..\\saves\\sceneData.dat";
		ofstream outFile;
		outFile.open(saveFileName, fstream::trunc);

		for (Bitmap* bits : sceneHier)
		{
			outFile << bits->SaveData();
			outFile << "\n";
		}
		outFile.close();
	}

	vector<string> getData(string data)
	{
		vector<string>returnVec;
		string currentLine = "";
		data.erase(data.cbegin());
		for(char ch: data)
		{
			if (ch == '-')
			{
				returnVec.push_back(currentLine);
				currentLine = "";
			}
			else if (ch == '|')
			{
				returnVec.push_back(currentLine);
				break;
			}
			else
			{
				currentLine.push_back(ch);
			}
		}
		return returnVec;
	}

	void Game::Load()
	{
		std::vector<Bitmap*> loadScene;
		ifstream inFile ("..\\saves\\sceneData.dat");
		string fileLine = " ";
		while (getline(inFile, fileLine))
		{
			vector<string>sepData = getData(fileLine);
			loadScene.push_back(new Bitmap(m_Renderer, sepData[0], stoi(sepData[1]), stoi(sepData[2])));
		}


		sceneHier = loadScene;
	}

	//collsion detection stuff



	//main game loop
	void Game::Update()
	{
		{
			auto tempProf = Profile("mainUpdate");
		}

		//clear and create new ImGui frame
		ImGui::NewFrame();
		ImGui_ImplSDL2_NewFrame(m_Window);

		//clears display
		SDL_RenderClear(m_Renderer);

		CheckEvents();

		//select and move gameobjects
		if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			auto gameObj = gameobjSelect(ImGui::GetMousePos());
			if (gameObj != nullptr)
			{
				gameObj->SetOBJPosX(ImGui::GetMousePos().x - (gameObj->GetObjWidth() / 2));
				gameObj->SetOBJPosY(ImGui::GetMousePos().y - (gameObj->GetObjHeight() / 2));
				detailsPanel->ChangeObj(gameObj);
			}
		}

		//details panel update
		detailsPanel->Update();

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
		

		//save and load buttons
		if(ImGui::BeginMainMenuBar());
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
				{
					Save();
				}
				if (ImGui::MenuItem("Load"))
				{
					Load();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
		
		

		//scene hierarchy stuff
		for (Bitmap* bmpScene:sceneHier)
		{
			bmpScene->Draw();
		}

		//Scene Hierarchy Window
		ImGui::Begin("Scene Hierarchy", 0);

		

		for (int i = 0; i < sceneHier.size(); i++)
		{
			ImGui::PushID(i);

			ImGui::Text("%s", sceneHier[i]->FileName.c_str());
			
			if(ImGui::BeginPopupContextItem(std::to_string(i).c_str(),ImGuiMouseButton_Left))
			{
				ImGui::Text("Test");

				ImGui::EndPopup();
			}

			ImGui::PopID();
		}

		ImGui::End();


		//my imgui test windows
		ImGui::Begin("Test Window");

		//show controls
		ImGui::Text("Hover Over Me For Game Controls");
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("WASD to Move, Esc to Quit");

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


		//asset editor gui

		if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && AssetMousDrag != nullptr)
		{
			//cout << "Test" << endl;
			int x, y;
			SDL_GetMouseState(&x, &y);
			Bitmap* s = new Bitmap(m_Renderer, AssetMousDrag->FileName, x, y, true);
			//s->Transfrom.ParentSet(GameWindow::Instance().GetHierarcy());
			//sceneRoot.Children.push_back(&s->M_Transform);
			sceneHier.push_back(s);

			AssetMousDrag = nullptr;
		}


		ImGui::Begin("Asset Editor");
		ImGui::BeginChild("Content Window", ImVec2(), true);
		//ImGui::BeginTable("Content browser", 3);
		
		for (int i = 0; i < content.size(); i++)
		{
			ImGui::PushID(i);

			ImGui::ImageButton((ImTextureID)content[i]->GetTextureRef(), { 100,100 });


			//for dragging
			if (ImGui::BeginDragDropSource())
			{
				AssetMousDrag = content[i];
				ImGui::Image((ImTextureID)content[i]->GetTextureRef(), { 100,100 });
				ImGui::EndDragDropSource();
			}
			ImGui::PopID();
			ImGui::SameLine();
		}

		//ImGui::EndTabItem();

		ImGui::EndChild();
		ImGui::End();



		//imgui demo
		bool show = true;
		//ShowExampleAppDockSpace(&show);

		ImGui::ShowDemoWindow(nullptr);

		ImGui::Render();
		ImGuiSDL::Render(ImGui::GetDrawData());

		//shows what drawn
		SDL_RenderPresent(m_Renderer);

		SDL_Delay(8);

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

		if (detailsPanel)
		{
			delete detailsPanel;	
			detailsPanel = nullptr;
		}
	}
