#pragma once

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

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

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;

class PhaseInterface
{
public:
	
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

class UserInterface :public PhaseInterface
{
private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_[4]; // the rectangle for source image
	SDL_Rect destination_rectangle_[4]; // for destination

public:
	UserInterface();
	~UserInterface();

	void Show_UI();
};