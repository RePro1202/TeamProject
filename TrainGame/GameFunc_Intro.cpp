#include "Core.h"
#include "GameFunc_Intro.h"

Intro::Intro()
{
}

void Intro::Update()
{
}

void Intro::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);


	SDL_RenderPresent(g_renderer);
}

void Intro::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_current_game_phase = PHASE_PLATFORM;
			}
			break;

		default:
			break;
		}
	}
}

Intro::~Intro()
{
}