#include "Core.h"
#include "GameFunc_Intro.h"

Intro::Intro()
{
	SDL_Surface* intro_surface = IMG_Load("../../Resources/intro.png");
	intro_texture_ = SDL_CreateTextureFromSurface(g_renderer, intro_surface);
	SDL_FreeSurface(intro_surface);
	intro_source_rect_ = { 0, 0 ,1200 ,800 };
	intro_destination_rect_ = { 0, 0, intro_source_rect_.w, intro_source_rect_.h };
}

void Intro::Update()
{
}

void Intro::Render()
{
	SDL_RenderCopy(g_renderer, intro_texture_, &intro_source_rect_, &intro_destination_rect_);

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
	SDL_DestroyTexture(intro_texture_);
}