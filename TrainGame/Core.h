#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

using namespace std;

#define BLOCK_X_MAX 1200
#define BLOCK_Y_MAX 800

void InitGame();
void ClearGame();

// ���� ������(����ü�� ���)
enum Phase
{
	PHASE_INTRO,
	PHASE_PLATFORM,
	PHASE_RUNNING,
	PHASE_ENDING
};

enum Day
{
	DAY_MORNING,
	DAY_DAYTIME,
	DAY_EVENING,
	DAY_NIGHT
};

// ���� ��ü�� �������� �ʰ� ����ؾ��ϹǷ� ���������� ����
extern int g_current_game_phase;
extern int g_day;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern int g_time_hour;
extern int g_time_min;
extern int g_time_sec;
extern int g_train_pos;

extern bool g_goal_time_update;
extern bool g_time_update;
extern bool g_train_pos_update;


class PhaseInterface
{
private:
	// ui ��ü �̹����ε� ����
	SDL_Texture* ui_texture_;
	SDL_Rect ui_source_rectangle_[5];
	SDL_Rect ui_destination_rectangle_[5];
	// Font ���� ����
	TTF_Font* UI_font_;
	SDL_Color darkblue_;
	// Time ���� ����
	SDL_Rect time_rect_;
	SDL_Texture* time_texture_;
	const char* time_char_;
	char buf_[256];
	int time_speed_;
	// ��ǥ�ð� ���� ����
	SDL_Rect goal_time_rect_;
	SDL_Texture* goal_time_texture_;
	const char* goal_time_char_;
	int goal_time_hour_;
	int goal_time_min_;
	int goal_morning_h_;
	int goal_daytime_h_;
	int goal_evening_h_;
	int goal_morning_m_;
	int goal_daytime_m_;
	int goal_evening_m_;
	int score; // ������ ���ھ�


	SDL_Texture* black_texture_;
	SDL_Rect black_source_rect_;
	SDL_Rect black_destination_rect_;
	int alpha_;

public:
	PhaseInterface();
	~PhaseInterface();

	void ShowUI();
	// Time ���� �Լ�
	void SetTimeFont();
	void TimeUpdate();
	SDL_Texture* GetTimeTexture() { return time_texture_; };
	SDL_Rect GetTimeRect() { return time_rect_; };
	// �����ð� ���� �Լ�
	void SetGoalTimeFont();
	SDL_Texture* GetGoalTimeTexture() { return goal_time_texture_; };
	SDL_Rect GetGoalTimeRect() { return goal_time_rect_; };
	// TrainPos ���� �Լ�
	void TrainPosUpdate();
	void DecreaseScore();

	//���̵� ��, �ƿ�
	void FadeIn();
	void FadeOut(int);
	void EndFade();

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};