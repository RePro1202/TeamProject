#include "Core.h"
#include "GameFunc_Ending.h"

Ending::Ending()
{
	ending_font_ = TTF_OpenFont("../../Resources/ALBAS___.ttf", 120);
	black_ = { 0,0,0,0 };
	SDL_Surface* tmp_surface = TTF_RenderText_Blended(ending_font_, "Ending", black_);
	ending_title_rect_ = { 0, 0, tmp_surface->w, tmp_surface->h };
	ending_title_texture_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	TTF_CloseFont(ending_font_);
}

void Ending::Update()
{
}

void Ending::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_Rect tmp_r;
	tmp_r = { 400, 200, ending_title_rect_.w, ending_title_rect_.h };
	SDL_RenderCopy(g_renderer, ending_title_texture_, &ending_title_rect_, &tmp_r);

	SDL_RenderPresent(g_renderer);
}

void Ending::HandleEvents()
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
				g_current_game_phase = PHASE_INTRO;
			}
			break;

		default:
			break;
		}
	}
}

Ending::~Ending()
{
	SDL_DestroyTexture(ending_title_texture_);
}