#include "Core.h"
#include "GameFunc_Platform.h"

Platform::Platform()
{
}

void Platform::Update()
{
}

void Platform::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 0, 255);
	SDL_RenderClear(g_renderer);

	UserInterface::Show_UI();

	SDL_RenderPresent(g_renderer);
}

void Platform::HandleEvents()
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
				g_current_game_phase = PHASE_RUNNING;
			}
			break;

		default:
			break;
		}
	}
}

Platform::~Platform()
{
}