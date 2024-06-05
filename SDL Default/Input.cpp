#include "iostream"
#include "SDL.h"
#include "Input.h"
#include "Game.h"
#include <backends/imgui_impl_sdl.h>

/// @brief for loop that goes through the enum of inputs
Input::Input() 
{
	for (int i = 0; i < KEYS_PRESSED_LIST::SIZE_OF_KEYS_PRESSED_ENUM; i++)
	{
		m_keysPressed[i] = false;
	}
}

/// @brief main update loop for the polling of key press events
/// @param polls the events to check which key is pressed 
void Input::Update(void) 
{
	while (SDL_PollEvent(&m_event) != NULL) 
	{
		ImGui_ImplSDL2_ProcessEvent(&m_event);

		if (m_event.type == SDL_KEYDOWN) 
		{
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			switch(keyPressed)
			{
				case SDLK_ESCAPE:
					m_keysPressed[KEY_ESCAPE] = true;
					break;
				case SDLK_r:
					m_keysPressed[KEY_R] = true;
					break;
				case SDLK_g:
					m_keysPressed[KEY_G] = true;
					break;
				case SDLK_b:
					m_keysPressed[KEY_B] = true;
					break;
				case SDLK_w:
					m_keysPressed[KEY_W] = true;
					break;
				case SDLK_a:
					m_keysPressed[KEY_A] = true;
					break;
				case SDLK_s:
					m_keysPressed[KEY_S] = true;
					break;
				case SDLK_d:
					m_keysPressed[KEY_D] = true;
					break;
			}
		}

		else if (m_event.type == SDL_KEYUP) 
		{
			SDL_Keycode keyPressed = m_event.key.keysym.sym;

			switch (keyPressed)
			{
			
				case SDLK_r:
					m_keysPressed[KEY_R] = false;
					break;
				case SDLK_g:
					m_keysPressed[KEY_G] = false;
					break;
				case SDLK_b:
					m_keysPressed[KEY_B] = false;
					break;
				case SDLK_w:
					m_keysPressed[KEY_W] = false;
					break;
				case SDLK_a:
					m_keysPressed[KEY_A] = false;
					break;
				case SDLK_s:
					m_keysPressed[KEY_S] = false;
					break;
				case SDLK_d:
					m_keysPressed[KEY_D] = false;
					break;
			}
		}
	}
}

/// @brief a simple bool function that lets the program know if is has had a key pressed or not
/// @param designate which is being pressed
/// @return returns true or false on key press
bool Input::KeyIsPressed(KEYS_PRESSED_LIST key)
{
	return m_keysPressed[key];
}


Input::~Input()
{

}


Input* Input::_instance;
Input*  Input::Instance()
{
	if (!_instance)
	{
		_instance = new Input();
	}
	return _instance;
}
