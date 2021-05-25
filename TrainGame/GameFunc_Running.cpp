#include "GameFunc_Running.h"


Running::Running()
{
	// Background
	SDL_Surface* background_surface = IMG_Load("../../Resources/Background.png");
	background_texture_ = SDL_CreateTextureFromSurface(g_renderer, background_surface);
	SDL_FreeSurface(background_surface);
	background_source_rect_[0] = { 0, 0 ,2400 ,485 };
	background_destination_rect_[0] = { 0, 0, background_source_rect_[0].w, background_source_rect_[0].h };
	background_source_rect_[1] = { 0, 485 ,2400 ,318 };
	background_destination_rect_[1] = { 0, 485, background_source_rect_[1].w, background_source_rect_[1].h };
	// Train
	SDL_Surface* train_surface = IMG_Load("../../Resources/Train.png");
	SDL_SetColorKey(train_surface, SDL_TRUE, SDL_MapRGB(train_surface->format, 100, 170, 150));
	train_texture_ = SDL_CreateTextureFromSurface(g_renderer, train_surface);
	SDL_FreeSurface(train_surface);
	train_source_rect_ = { 93, 57 ,1753 ,184 };
	train_destination_rect_ = { -1188, 530, train_source_rect_.w, train_source_rect_.h };
	// arrow
	SDL_Surface* arrow_surface = IMG_Load("../../Resources/UI.png");
	SDL_SetColorKey(arrow_surface, SDL_TRUE, SDL_MapRGB(arrow_surface->format, 200, 200, 250));
	arrow_texture_ = SDL_CreateTextureFromSurface(g_renderer, arrow_surface);
	SDL_FreeSurface(arrow_surface);
	arrow_source_rect_ = { 687, 63 ,31 ,63 };
	arrow_destination_rect_ = { 1065, 173, arrow_source_rect_.w, arrow_source_rect_.h };

	speed_ = 10;
	distance_ = 0;
	arrow_speed_ = 1.0;

	eve_ = new Events;
}

void Running::Update()
{
	eve_->runEvent(distance_);	// distance값으로 이벤트 발생조건 검사
	
	// 이벤트 처리하는 동안 속도, 속도계 고정
	if (!eve_->getEventState()) {
		speed_ -= 1;	// speed 자동 감소(최솟값 20, 최댓값 50)
		if (speed_ < 20)
			speed_ = 20;
		else if (speed_ > 50)
			speed_ = 50;

		arrow_destination_rect_.x -= arrow_speed_;
	}

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
	// 속도계 화살표
	
	if (arrow_destination_rect_.x < 950) {
		arrow_destination_rect_.x = 950;
	}
	if (arrow_destination_rect_.x > 1100) {
		arrow_destination_rect_.x = 1100;
	}
	if (arrow_destination_rect_.x < 1050) {  //속도계 눈금 벗어났을때 감점..조건절 추후 변경예정..
		PhaseInterface::DecreaseScore();
	}
	if (arrow_destination_rect_.x > 1080) {  //조건절 추후 변경예정..
		PhaseInterface::DecreaseScore();
	}

	arrow_speed_ = 1.0;

	// 페이즈 전환
	if (distance_ == 5)
	{
		background_destination_rect_[0].x = 0;
		background_destination_rect_[1].x = 0;

		train_destination_rect_.x += 40;
		if (train_destination_rect_.x > BLOCK_X_MAX)
		{
			g_current_game_phase = PHASE_PLATFORM;
			PhaseInterface::TrainPosUpdate();
			PhaseInterface::EndFade();

			speed_ = 20;
			distance_ = 0;
			train_destination_rect_.x = -1188;
			arrow_destination_rect_.x = 1065;


			g_time_update = true;
			g_train_pos_update = true;
			++g_day;// 시간대 변경
			g_goal_time_update = true;
		}
	}

	// Time값 Update
	PhaseInterface::TimeUpdate();
	if (g_time_sec % 10 == 0)
		g_time_update = true;
}

void Running::Render()
{
	// Background
	SDL_RenderCopy(g_renderer, background_texture_, &background_source_rect_[0], &background_destination_rect_[0]);
	SDL_RenderCopy(g_renderer, background_texture_, &background_source_rect_[1], &background_destination_rect_[1]);

	// Train
	SDL_RenderCopy(g_renderer, train_texture_, &train_source_rect_, &train_destination_rect_);

	if (g_train_pos_update == true)
	{
		PhaseInterface::TrainPosUpdate();
		g_train_pos_update = false;
	}
	PhaseInterface::ShowUI();
	eve_->showEvent();

	// 목표시간 Render
	if (g_goal_time_update)
	{
		PhaseInterface::SetGoalTimeFont();
		g_goal_time_update = false;
	}
	SDL_Rect tmp_r = { 145, 23, 110, 60 };
	SDL_Texture* tmp_texture = PhaseInterface::GetGoalTimeTexture();
	SDL_Rect tmp_rect = PhaseInterface::GetGoalTimeRect();
	SDL_RenderCopy(g_renderer, tmp_texture, &tmp_rect, &tmp_r);
	// Time 최신화
	if (g_time_update)
	{
		PhaseInterface::SetTimeFont();
		g_time_update = false;
	}
	// Time Render
	SDL_Rect tmp_r2 = { 145, 92, 110, 60 };
	SDL_Texture* tmp_texture2 = PhaseInterface::GetGoalTimeTexture();
	SDL_Rect tmp_rect2 = PhaseInterface::GetGoalTimeRect();
	SDL_RenderCopy(g_renderer, tmp_texture2, &tmp_rect2, &tmp_r2);

	//arrow
	SDL_RenderCopy(g_renderer, arrow_texture_, &arrow_source_rect_, &arrow_destination_rect_);

	// Fade in and out
	if (distance_ == 0) {
		PhaseInterface::FadeIn();
	}
	else if (distance_ == 1) {
		PhaseInterface::EndFade();
	}
	else if (distance_ == 5) {
		PhaseInterface::FadeOut(5);
	}

	SDL_RenderPresent(g_renderer);
}

void Running::HandleEvents()
{
	SDL_Event event;

	eve_->commandHandel();
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_RIGHT)
			{	// 오른쪽 키를 누르면 speed값 증가
				speed_ += 5;
				arrow_speed_ = -3.0;
			}
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
	SDL_DestroyTexture(train_texture_);
	SDL_DestroyTexture(arrow_texture_);

}