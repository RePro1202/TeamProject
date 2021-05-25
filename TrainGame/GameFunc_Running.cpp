#include "GameFunc_Running.h"

Running::Running()
{
	// Background
	SDL_Surface* background1_surface = IMG_Load("../../Resources/Background_morning.png");
	background_texture_[0] = SDL_CreateTextureFromSurface(g_renderer, background1_surface);
	SDL_FreeSurface(background1_surface);
	background_source_rect_[0] = { 0, 0 ,2400 ,485 };
	background_destination_rect_[0] = { 0, 0, background_source_rect_[0].w, background_source_rect_[0].h };

	SDL_Surface* background2_surface = IMG_Load("../../Resources/Background_daytime.png");
	background_texture_[1] = SDL_CreateTextureFromSurface(g_renderer, background2_surface);
	SDL_FreeSurface(background2_surface);
	background_source_rect_[1] = { 0, 0 ,2400 ,485 };
	background_destination_rect_[1] = { 0, 0, background_source_rect_[1].w, background_source_rect_[1].h };

	SDL_Surface* background3_surface = IMG_Load("../../Resources/Background_evening.png");
	background_texture_[2] = SDL_CreateTextureFromSurface(g_renderer, background3_surface);
	SDL_FreeSurface(background3_surface);
	background_source_rect_[2] = { 0, 0 ,2400 ,485 };
	background_destination_rect_[2] = { 0, 0, background_source_rect_[2].w, background_source_rect_[2].h };
	// Track
	SDL_Surface* track_surface = IMG_Load("../../Resources/Track.png");
	track_texture_ = SDL_CreateTextureFromSurface(g_renderer, track_surface);
	SDL_FreeSurface(track_surface);
	track_source_rect_ = { 0, 0 ,2400 ,318 };
	track_destination_rect_ = { 0, 485, track_source_rect_.w, track_source_rect_.h };
	// Train
	SDL_Surface* train_surface = IMG_Load("../../Resources/Train.png");
	SDL_SetColorKey(train_surface, SDL_TRUE, SDL_MapRGB(train_surface->format, 100, 170, 150));
	train_texture_ = SDL_CreateTextureFromSurface(g_renderer, train_surface);
	SDL_FreeSurface(train_surface);
	train_source_rect_ = { 93, 57 ,1753 ,184 };
	train_destination_rect_ = { -1188, 530, train_source_rect_.w, train_source_rect_.h };
	// Arrow
	SDL_Surface* arrow_surface = IMG_Load("../../Resources/UI.png");
	SDL_SetColorKey(arrow_surface, SDL_TRUE, SDL_MapRGB(arrow_surface->format, 200, 200, 250));
	arrow_texture_ = SDL_CreateTextureFromSurface(g_renderer, arrow_surface);
	SDL_FreeSurface(arrow_surface);
	arrow_source_rect_ = { 697, 76 ,12 ,35 };
	arrow_destination_rect_ = { 1080, 186, arrow_source_rect_.w, arrow_source_rect_.h };

	train_speed_ = 40;
	train_distance_ = 0;
	arrow_speed_ = 1.3;

	eve_ = new Events;

}

void Running::Update()
{
	eve_->runEvent(train_distance_);	// distance������ �̺�Ʈ �߻����� �˻�
	
	// �̺�Ʈ ó���ϴ� ���� �ӵ�, �ӵ��� ����
	if (!eve_->getEventState()) {
		train_speed_ -= 1;	// speed �ڵ� ����(�ּڰ� 20, �ִ� 50)
		if (train_speed_ < 5)
			train_speed_ = 5;
		else if (train_speed_ > 60)
			train_speed_ = 60;

		arrow_destination_rect_.x -= arrow_speed_;
		if (arrow_destination_rect_.x > 1096) //�ӵ���󿡼��� ���� �ӵ� ����
			train_speed_ = 60; 
	}

	// ���� ���
	background_destination_rect_[g_day].x -= train_speed_ / 2;

	if (background_destination_rect_[g_day].x < -1200) {
		background_destination_rect_[g_day].x = 0;
		++train_distance_;
	}
	// �Ʒ��� ���
	track_destination_rect_.x -= train_speed_ * 2;

	if (track_destination_rect_.x < -1200) {

		track_destination_rect_.x = 0;
	}

	// �ӵ��� ȭ��ǥ
	
	if (arrow_destination_rect_.x < 954) {
		arrow_destination_rect_.x = 954;
	}
	else if (arrow_destination_rect_.x > 1131) {
		arrow_destination_rect_.x = 1131;
	}
	else if (arrow_destination_rect_.x < 1064 || arrow_destination_rect_.x > 1096) {  //�ӵ��� ���� ������� ����..������ ���� ���濹��..
		PhaseInterface::DecreaseScore();
	}

	arrow_speed_ = 1.3;


	// ������ ��ȯ
	if (train_distance_ == 8)
	{
		background_destination_rect_[g_day].x = 0;
		track_destination_rect_.x = 0;

		train_destination_rect_.x += 40;
		if (train_destination_rect_.x > BLOCK_X_MAX)
		{
			g_current_game_phase = PHASE_PLATFORM;

			train_speed_ = 50;
			train_distance_ = 0;
			train_destination_rect_.x = -1188;
			arrow_destination_rect_.x = 1080;
			Mix_PauseMusic();

			g_time_update = true;
			g_train_pos_update = true;
			g_goal_time_update = true;
			++g_day;// �ð��� ����

		}
	}

	// Time�� Update
	PhaseInterface::TimeUpdate();
	if (g_time_sec % 10 == 0)
		g_time_update = true;
}

void Running::Render()
{
	// Background
	SDL_RenderCopy(g_renderer, background_texture_[g_day], &background_source_rect_[g_day], &background_destination_rect_[g_day]);
	SDL_RenderCopy(g_renderer, track_texture_, &track_source_rect_, &track_destination_rect_);

	// Train
	SDL_RenderCopy(g_renderer, train_texture_, &train_source_rect_, &train_destination_rect_);

	if (g_train_pos_update == true)
	{
		PhaseInterface::TrainPosUpdate();
		g_train_pos_update = false;
	}
	PhaseInterface::ShowUI();
	eve_->showEvent();

	// ��ǥ�ð� Render
	if (g_goal_time_update)
	{
		PhaseInterface::SetGoalTimeFont();
		g_goal_time_update = false;
	}
	SDL_Rect tmp_r = { 145, 23, 110, 60 };
	SDL_Texture* tmp_texture = PhaseInterface::GetGoalTimeTexture();
	SDL_Rect tmp_rect = PhaseInterface::GetGoalTimeRect();
	SDL_RenderCopy(g_renderer, tmp_texture, &tmp_rect, &tmp_r);
	// Time �ֽ�ȭ
	if (g_time_update)
	{
		PhaseInterface::SetTimeFont();
		g_time_update = false;
	}
	// Time Render
	SDL_Rect tmp_r2 = { 145, 92, 110, 60 };
	SDL_Texture* tmp_texture2 = PhaseInterface::GetTimeTexture();
	SDL_Rect tmp_rect2 = PhaseInterface::GetTimeRect();
	SDL_RenderCopy(g_renderer, tmp_texture2, &tmp_rect2, &tmp_r2);

	//arrow
	SDL_RenderCopy(g_renderer, arrow_texture_, &arrow_source_rect_, &arrow_destination_rect_);

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
			{	// ������ Ű�� ������ speed�� ����
				train_speed_ += 2.5;
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
	SDL_DestroyTexture(background_texture_[0]);
	SDL_DestroyTexture(background_texture_[1]);
	SDL_DestroyTexture(background_texture_[2]);
	SDL_DestroyTexture(track_texture_);
	SDL_DestroyTexture(train_texture_);
	SDL_DestroyTexture(arrow_texture_);
}