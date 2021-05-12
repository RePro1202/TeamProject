#include "Core.h"
#include "GameFunc_Running.h"

Running::Running()
{
}

void Running::Update()
{
}

void Running::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 0, 255, 255);
	SDL_RenderClear(g_renderer);

	UserInterface::Show_UI();

	SDL_RenderPresent(g_renderer);
}

void Running::HandleEvents()
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
				g_current_game_phase = PHASE_ENDING;
			}
			break;

		default:
			break;
		}
	}
}

Running::~Running()
{
}