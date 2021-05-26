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

	board_rect_ = {250, 300, 700, 350};

	render_complete = true;
}

void Ending::Update()
{
}

void Ending::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_SetRenderDrawColor(g_renderer, 127, 127, 127, 255);
	SDL_RenderFillRect(g_renderer, &board_rect_);

	SDL_Rect tmp_r;
	tmp_r = { 400, 50, ending_title_rect_.w, ending_title_rect_.h };
	SDL_RenderCopy(g_renderer, ending_title_texture_, &ending_title_rect_, &tmp_r);

	// 한번만 Render하기 위한 조건문
	if (render_complete)
	{
		PhaseInterface::SetEndingTimeFont();
		PhaseInterface::SetEndingScoreFont();
		render_complete = false;
	}
	// Time
	SDL_Rect tmp_r2 = { 350, 380, 500, 60 };
	SDL_Texture* tmp_texture2 = PhaseInterface::GetTimeTexture();
	SDL_Rect tmp_rect2 = PhaseInterface::GetTimeRect();
	SDL_RenderCopy(g_renderer, tmp_texture2, &tmp_rect2, &tmp_r2);

	// Score
	SDL_Rect tmp_r3 = { 350, 520, 500, 60 };
	SDL_Texture* tmp_texture3 = PhaseInterface::GetScoreTexture();
	SDL_Rect tmp_rect3 = PhaseInterface::GetScoreRect();
	SDL_RenderCopy(g_renderer, tmp_texture3, &tmp_rect3, &tmp_r3);

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
				g_flag_running = false;
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