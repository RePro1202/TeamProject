#include "GameFunc_Intro.h"

Intro::Intro()
{
	g_button_rect_1 = { 322, 406, 217, 90 };
	g_button_rect_2 = { 637, 406, 217, 90 };

	SDL_Surface* intro_surface = IMG_Load("../../Resources/Intro.png");
	intro_texture_ = SDL_CreateTextureFromSurface(g_renderer, intro_surface);
	SDL_FreeSurface(intro_surface);
	intro_source_rect_ = { 0, 0 ,1200 ,800 };
	intro_destination_rect_ = { 0, 0, intro_source_rect_.w, intro_source_rect_.h };

	// Font
	TTF_Font* font1 = TTF_OpenFont("../../Resources/ALBAS___.ttf", 100);
	SDL_Color black = { 0,0,0,0 };
	SDL_Surface* tmp_surface = TTF_RenderText_Blended(font1, "Train Game", black);
	intro_title_rect_ = { 0, 0, tmp_surface->w, tmp_surface->h };
	intro_title_texture_ = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	TTF_CloseFont(font1);
}

void Intro::Update()
{
}

void Intro::Render()
{
	SDL_RenderCopy(g_renderer, intro_texture_, &intro_source_rect_, &intro_destination_rect_);

	SDL_Rect tmp_r;
	tmp_r = { 320, 150, intro_title_rect_.w, intro_title_rect_.h };
	SDL_RenderCopy(g_renderer, intro_title_texture_, &intro_title_rect_, &tmp_r);

	PhaseInterface::FadeIn();

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

			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				// 게임시작 버튼
				if (mouse_x > g_button_rect_1.x &&
					mouse_y > g_button_rect_1.y &&
					mouse_x < g_button_rect_1.x + g_button_rect_1.w &&
					mouse_y < g_button_rect_1.y + g_button_rect_1.h) {

					PhaseInterface::EndFade();
					g_current_game_phase = PHASE_PLATFORM;
				}
					

				// 게임종료 버튼
				else if (mouse_x > g_button_rect_2.x &&
					mouse_y > g_button_rect_2.y &&
					mouse_x < g_button_rect_2.x + g_button_rect_2.w &&
					mouse_y < g_button_rect_2.y + g_button_rect_2.h)
					g_flag_running = false;
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
	SDL_DestroyTexture(intro_title_texture_);
}