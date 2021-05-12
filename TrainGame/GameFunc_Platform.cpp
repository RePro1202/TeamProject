#include "Core.h"
#include "GameFunc_Platform.h"

Platform::Platform()
{
	SDL_Surface* platform_surface = IMG_Load("../../Resources/Platform.png");
	SDL_SetColorKey(platform_surface, SDL_TRUE, SDL_MapRGB(platform_surface->format, 200, 191, 231));
	platform_texture_ = SDL_CreateTextureFromSurface(g_renderer, platform_surface);
	SDL_FreeSurface(platform_surface);
	platform_source_rect_ = { 0, 0 ,1200 ,800 };
	platform_destination_rect_ = { 0, 0, platform_source_rect_.w, platform_source_rect_.h };

	SDL_Surface* train_surface = IMG_Load("../../Resources/Train.png");
	SDL_SetColorKey(train_surface, SDL_TRUE, SDL_MapRGB(train_surface->format, 100, 170, 150));
	train_texture_ = SDL_CreateTextureFromSurface(g_renderer, train_surface);
	SDL_FreeSurface(train_surface);
	train_source_rect_ = { 93, 57 ,1753 ,184 };
	train_destination_rect_ = { -1730, 350, train_source_rect_.w, train_source_rect_.h };

	speed_ = 0;
	train_state_ = TRAIN_IN;
	stop_pos_ = -730;
	train_out_ = false;
}

void Platform::Update()
{
	// 기차 현재 위치에 따른 상태변화
	if (train_destination_rect_.x < stop_pos_)
		train_state_ = TRAIN_IN;
	else if (train_destination_rect_.x == stop_pos_)
		train_state_ = TRAIN_STOP;
	else
		train_state_ = TRAIN_OUT;

	// 기차 상태에 따른 속도변화(실제 기차 움직임처럼 구현)
	switch (train_state_)
	{
	case TRAIN_IN:
		if (train_destination_rect_.x < stop_pos_ * 1.8)
			speed_ = 30;
		else if (train_destination_rect_.x >= stop_pos_ * 1.8 && train_destination_rect_.x < stop_pos_ * 1.5)
			speed_ = 20;
		else if (train_destination_rect_.x >= stop_pos_ * 1.5 && train_destination_rect_.x < stop_pos_ * 1.2)
			speed_ = 10;
		else
			speed_ = 5;
		break;
	case TRAIN_STOP:
		speed_ = 0;
		if (train_out_)
			speed_ = 5;
		break;
	case TRAIN_OUT:
		if (train_destination_rect_.x < stop_pos_ * 0.8)
			speed_ = 5;
		else if (train_destination_rect_.x >= stop_pos_ * 0.8 && train_destination_rect_.x < stop_pos_ * 0.5)
			speed_ = 10;
		else if (train_destination_rect_.x >= stop_pos_ * 0.5 && train_destination_rect_.x < stop_pos_ * 0.2)
			speed_ = 20;
		else
			speed_ = 30;
		break;
	}

	train_destination_rect_.x += speed_;

	// 기차모습이 사라지면 running페이즈로 전환(변수값 초기화)
	if (train_destination_rect_.x > 1200)
	{
		g_current_game_phase = PHASE_RUNNING;

		train_destination_rect_.x = -1730;
		train_out_ = false;
	}
}

void Platform::Render()
{
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, train_texture_, &train_source_rect_, &train_destination_rect_);

	SDL_RenderCopy(g_renderer, platform_texture_, &platform_source_rect_, &platform_destination_rect_);

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

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_UP)
				// 위쪽 방향키를 누르면 기차가 다시 출발
				train_out_ = true;
			break;

		case SDL_MOUSEBUTTONDOWN:

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
	SDL_DestroyTexture(platform_texture_);
	SDL_DestroyTexture(train_texture_);
}