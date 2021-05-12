#include "Core.h"
#include "GameFunc_Running.h"

Running::Running()
{
	for (int i = 0; i <= 1; i++) {
		SDL_Surface* background_surface = IMG_Load("../../Resources/background.png");
		background_texture_[i] = SDL_CreateTextureFromSurface(g_renderer, background_surface);
		SDL_FreeSurface(background_surface);
	}

	background_source_rect_[0] = { 0, 0, 2400, 485 };
	background_destination_rect_[0] = { 0, 0, background_source_rect_[0].w, background_source_rect_[0].h };

	background_source_rect_[1] = { 0, 485 ,2400 ,318 };
	background_destination_rect_[1] = { 0, 485, background_source_rect_[1].w, background_source_rect_[1].h };
}

void Running::Update()
{
	
	background_destination_rect_[0].x -= 8;
	if (background_destination_rect_[0].x == -1200)
		background_destination_rect_[0].x = 0;

	background_destination_rect_[1].x -= 15;
	if (background_destination_rect_[1].x == -1200)
		background_destination_rect_[1].x = 0;
		
}

void Running::Render()
{
	SDL_RenderCopy(g_renderer, background_texture_[0], &background_source_rect_[0], &background_destination_rect_[0]);
	SDL_RenderCopy(g_renderer, background_texture_[1], &background_source_rect_[1], &background_destination_rect_[1]);

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
	SDL_DestroyTexture(background_texture_[0]);
	SDL_DestroyTexture(background_texture_[1]);

}