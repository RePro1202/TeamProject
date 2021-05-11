#pragma once

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

void InitGame();
void ClearGame();

// ���� ������(����ü�� ���)
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