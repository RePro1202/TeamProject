#include "GameFunc_Running.h"
#include "GameFunc_Events.h"

Running::Running()
{
	SDL_Surface* background_surface = IMG_Load("../../Resources/Background.png");
	background_texture_ = SDL_CreateTextureFromSurface(g_renderer, background_surface);
	SDL_FreeSurface(background_surface);
	background_source_rect_[0] = { 0, 0 ,2400 ,485 };
	background_destination_rect_[0] = { 0, 0, background_source_rect_[0].w, background_source_rect_[0].h };

	background_source_rect_[1] = { 0, 485 ,2400 ,318 };
	background_destination_rect_[1] = { 0, 485, background_source_rect_[1].w, background_source_rect_[1].h };

	SDL_Surface* train_surface = IMG_Load("../../Resources/Train.png");
	SDL_SetColorKey(train_surface, SDL_TRUE, SDL_MapRGB(train_surface->format, 100, 170, 150));
	train_texture_ = SDL_CreateTextureFromSurface(g_renderer, train_surface);
	SDL_FreeSurface(train_surface);
	train_source_rect_ = { 93, 57 ,1753 ,184 };
	train_destination_rect_ = { -1188, 540, train_source_rect_.w, train_source_rect_.h };

	//Speed 초기화
	speed_ = 10;
	distance_ = 0;
}

void Running::Update()
{
	// speed 자동 감소(최솟값 10, 최댓값 50)
	speed_ -= 1;
	if (speed_ < 10)
		speed_ = 10;
	else if (speed_ > 50)
		speed_ = 50;

	// 위쪽 배경
	background_destination_rect_[0].x -= speed_ / 2;

	if (background_destination_rect_[0].x < -1200) {
		background_destination_rect_[0].x = 0;
		++distance_;
	}

	// 아래쪽 배경
	background_destination_rect_[1].x -= speed_ * 2;

	if (background_destination_rect_[1].x < -1200) {
		background_destination_rect_[1].x = 0;
	}

	// distance가 5가 되면 platform페이즈로 전환(변수값 초기화)
	if (distance_ == 5)
	{
		g_current_game_phase = PHASE_PLATFORM;

		background_destination_rect_[0].x = 0;
		background_destination_rect_[1].x = 0;
		speed_ = 10;
		distance_ = 0;
	}
}

void Running::Render()
{
	// Background
	SDL_RenderCopy(g_renderer, background_texture_, &background_source_rect_[0], &background_destination_rect_[0]);
	SDL_RenderCopy(g_renderer, background_texture_, &background_source_rect_[1], &background_destination_rect_[1]);

	// Train
	SDL_RenderCopy(g_renderer, train_texture_, &train_source_rect_, &train_destination_rect_);

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
				speed_ += 5;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				g_current_game_phase = PHASE_ENDING;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT)
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
	SDL_DestroyTexture(train_texture_);
}