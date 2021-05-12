#include "Core.h"
#include "GameFunc_Running.h"

Running::Running()
{
	SDL_Surface* background_surface = IMG_Load("../../Resources/background.png");
	background_texture_= SDL_CreateTextureFromSurface(g_renderer, background_surface);
	SDL_FreeSurface(background_surface);
	
	background_source_rect_[0] = { 0, 0, 2400, 485 };
	background_destination_rect_[0] = { 0, 0, background_source_rect_[0].w, background_source_rect_[0].h };

	background_source_rect_[1] = { 0, 485 ,2400 ,318 };
	background_destination_rect_[1] = { 0, 485, background_source_rect_[1].w, background_source_rect_[1].h };

	//Speed 초기화
	speed_ = 10;
	distance_ = 0;
}

void Running::Update()
{
	
	background_destination_rect_[0].x -= 8;
	if (background_destination_rect_[0].x == -1200)
		background_destination_rect_[0].x = 0;

	background_destination_rect_[1].x -= 15;
	if (background_destination_rect_[1].x == -1200)
		background_destination_rect_[1].x = 0;
		
	// 속도 조절 추가
	speed_ -= 1;
	if (speed_ < 5)
		speed_ = 10;
	else if (speed_ > 30)
		speed_ = 30;

	background_destination_rect_[0].x -= speed_ * 0.4;
	background_destination_rect_[1].x -= speed_;

	// 화면이 전환될때마다 distance 증가
	if (background_destination_rect_[0].x < -1200) {
		background_destination_rect_[0].x = 0;
	}
	if (background_destination_rect_[1].x < -1200) {
		background_destination_rect_[1].x = 0;
		++distance_;
	}

	// distance가 20이 되면 platform으로 화면 전환
	if (distance_ == 20)
	{
		background_destination_rect_[1].x = 0;
		g_current_game_phase = PHASE_PLATFORM;

		speed_ = 10;
		distance_ = 0;
	}
}

void Running::Render()
{
	SDL_RenderCopy(g_renderer, background_texture_, &background_source_rect_[0], &background_destination_rect_[0]);
	SDL_RenderCopy(g_renderer, background_texture_, &background_source_rect_[1], &background_destination_rect_[1]);

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

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_RIGHT)
				// 오른쪽 키를 누르면 speed값 증가
				speed_ += 3;

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