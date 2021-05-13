#pragma once

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

using namespace std;

void InitGame();
void ClearGame();

// 게임 페이즈(열거체를 사용)
enum Phase
{
	PHASE_INTRO,
	PHASE_RUNNING,
	PHASE_PLATFORM,
	PHASE_ENDING
};

// 따로 객체를 생성하지 않고 사용해야하므로 전역변수로 설정
extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;

class PhaseInterface
{
private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect ui_source_rectangle_[4]; // the rectangle for source image
	SDL_Rect ui_destination_rectangle_[4]; // for destination

public:
	PhaseInterface();
	~PhaseInterface();
	void ShowUI();
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};