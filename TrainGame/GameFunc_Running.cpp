#include "Core.h"
#include "GameFunc_Running.h"

Running::Running()
{
	SDL_Surface* background_surface = IMG_Load("../../Resources/background.png");
	background_texture_ = SDL_CreateTextureFromSurface(g_renderer, background_surface);
	SDL_FreeSurface(background_surface);
	background_source_rect_ = { 0, 0 ,2400 ,800 };
	background_destination_rect_ = { 0, 0, background_source_rect_.w, background_source_rect_.h };
}

void Running::Update()
{
	
	background_destination_rect_.x -= 10;
	if (background_destination_rect_.x == -1200)
		background_destination_rect_.x = 0;
		
}

void Running::Render()
{
	SDL_RenderCopy(g_renderer, background_texture_, &background_source_rect_, &background_destination_rect_);

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
	SDL_DestroyTexture(background_texture_);
}