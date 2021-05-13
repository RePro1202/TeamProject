#include "Core.h"
#include "GameFunc_Platform.h"

Platform::Platform()
{
	SDL_Surface* platform_surface = IMG_Load("../../Resources/platform.png");
	SDL_SetColorKey(platform_surface, SDL_TRUE, SDL_MapRGB(platform_surface->format, 200, 191, 231));
	platform_texture_ = SDL_CreateTextureFromSurface(g_renderer, platform_surface);
	SDL_FreeSurface(platform_surface);
	platform_source_rect_ = { 0, 0 ,1200 ,800 };
	platform_destination_rect_ = { 0, 0, platform_source_rect_.w, platform_source_rect_.h };

	SDL_Surface* train_surface = IMG_Load("../../Resources/train.png");
	SDL_SetColorKey(train_surface, SDL_TRUE, SDL_MapRGB(train_surface->format, 100, 170, 150));
	train_texture_ = SDL_CreateTextureFromSurface(g_renderer, train_surface);
	SDL_FreeSurface(train_surface);
	train_source_rect_ = { 50, 50 ,1800 ,250 };
	train_destination_rect_ = { -1600 , 350, train_source_rect_.w, train_source_rect_.h };

	train_state_ = TRAIN_IN;
	train_speed_ = 0;
	stop_destination_ = -775;
	end_destination_ = 1200;
	consumption_time_ = 3; // 정지까지 필요한 시간
}

void Platform::Update()
{
	if (train_state_ == TRAIN_IN) {
		train_speed_ = (2 * (stop_destination_ - train_destination_rect_.x)) / (30 * consumption_time_) + 2;
		if (train_destination_rect_.x > stop_destination_) {
			train_destination_rect_.x = stop_destination_;
			train_state_ = 1;
		}
	}
	else if (train_state_ == TRAIN_STOP)
	{
		train_speed_ = 0;
		consumption_time_ = 2; //나갈때 까지 걸리는 시간
	}
	else if (train_state_ == TRAIN_OUT) {
		train_speed_ = 2 * (end_destination_ - stop_destination_) / (30 * consumption_time_) + 2
			- (2 * (end_destination_ - train_destination_rect_.x)) / (30 * consumption_time_);
		// 화면 밖으로 나가면 running페이즈로 전환(변수 초기화)
		if (train_destination_rect_.x > end_destination_)
		{
			g_current_game_phase = PHASE_RUNNING;

			train_destination_rect_.x = -1600;
			train_state_ = TRAIN_IN;
			train_speed_ = 0;
			consumption_time_ = 3;
		}
	}

	train_destination_rect_.x += train_speed_;
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
				if (train_state_ == TRAIN_STOP)
					train_state_ = TRAIN_OUT;
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
	SDL_DestroyTexture(platform_texture_);
	SDL_DestroyTexture(train_texture_);
}