#include "Core.h"
#include "GameFunc_Platform.h"

Platform::Platform()
{
	SDL_Surface* platform_surface = IMG_Load("../../Resources/Platform.png");
	SDL_SetColorKey(platform_surface, SDL_TRUE, SDL_MapRGB(platform_surface->format, 200, 191, 231));
	g_platform_texture = SDL_CreateTextureFromSurface(g_renderer, platform_surface);
	SDL_FreeSurface(platform_surface);
	g_platform_source_rect = { 0, 0 ,1200 ,800 };
	g_platform_destination_rect = { 0, 0, g_platform_source_rect.w, g_platform_source_rect.h };
}

void Platform::Update()
{
}

void Platform::Render()
{
	SDL_RenderCopy(g_renderer, g_platform_texture, &g_platform_source_rect, &g_platform_destination_rect);

	PhaseInterface::ShowUI();

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