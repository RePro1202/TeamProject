#include "Core.h"
#include "GameFunc_Running.h"

Running::Running()
{
	SDL_Surface* background_surface = IMG_Load("../../Resources/Background.png");
	g_background_texture = SDL_CreateTextureFromSurface(g_renderer, background_surface);
	SDL_FreeSurface(background_surface);
	g_background_source_rect = { 0, 0 ,1200 ,800 };
	g_background_destination_rect = { 0, 0, g_background_source_rect.w, g_background_source_rect.h };
}

void Running::Update()
{
}

void Running::Render()
{
	SDL_RenderCopy(g_renderer, g_background_texture, &g_background_source_rect, &g_background_destination_rect);

	PhaseInterface::ShowUI();

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