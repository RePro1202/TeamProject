#include "Core.h"

void InitGame() {
	g_flag_running = true;
}

void ClearGame() {
}


//// UserInterface////
PhaseInterface::PhaseInterface()
{
	SDL_Surface* temp_surface = IMG_Load("../../Resources/UI.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);
	
	// Time
	ui_source_rectangle_[0] = { 9, 7, 192, 131 };
	ui_destination_rectangle_[0] = { 50, 20, 200, 120 };

	// Score
	ui_source_rectangle_[1] = { 215, 40, 206, 96 };
	ui_destination_rectangle_[1] = { 950, 20, 200, 120 };

	// Speed
	ui_source_rectangle_[2] = { 436, 65, 240, 71 };
	ui_destination_rectangle_[2] = { 950, 160, 200, 100 };

	// Train_pos
	ui_source_rectangle_[3] = { 12, 151, 564, 143 };
	ui_destination_rectangle_[3] = { 340, 20, 520, 140 };
}

PhaseInterface::~PhaseInterface()
{
	SDL_DestroyTexture(texture_);
}

void PhaseInterface::ShowUI()
{
	for (int i = 0; i < 4; i++) {
		SDL_RenderCopy(g_renderer, texture_, &ui_source_rectangle_[i], &ui_destination_rectangle_[i]);
	}
}