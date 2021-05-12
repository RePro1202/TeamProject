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
	source_rectangle_[0].x = 9;
	source_rectangle_[0].y = 7;
	source_rectangle_[0].w = 201 - source_rectangle_[0].x;
	source_rectangle_[0].h = 138 - source_rectangle_[0].y;

	destination_rectangle_[0].x = 50;
	destination_rectangle_[0].y = 20;
	destination_rectangle_[0].w = 200;
	destination_rectangle_[0].h = 120;

	// Score
	source_rectangle_[1].x = 215;
	source_rectangle_[1].y = 40;
	source_rectangle_[1].w = 421 - source_rectangle_[1].x;
	source_rectangle_[1].h = 136 - source_rectangle_[1].y;

	destination_rectangle_[1].x = 950;
	destination_rectangle_[1].y = 20;
	destination_rectangle_[1].w = 200;
	destination_rectangle_[1].h = 120;

	// Speed
	source_rectangle_[2].x = 436;
	source_rectangle_[2].y = 65;
	source_rectangle_[2].w = 676 - source_rectangle_[2].x;
	source_rectangle_[2].h = 136 - source_rectangle_[2].y;

	destination_rectangle_[2].x = 950;
	destination_rectangle_[2].y = 160;
	destination_rectangle_[2].w = 200;
	destination_rectangle_[2].h = 100;

	// Train_pos
	source_rectangle_[3].x = 12;
	source_rectangle_[3].y = 151;
	source_rectangle_[3].w = 576 - source_rectangle_[3].x;
	source_rectangle_[3].h = 294 - source_rectangle_[3].y;

	destination_rectangle_[3].x = 340;
	destination_rectangle_[3].y = 20;
	destination_rectangle_[3].w = 520;
	destination_rectangle_[3].h = 140;
}

PhaseInterface::~PhaseInterface()
{
	SDL_DestroyTexture(texture_);
}

void PhaseInterface::ShowUI()
{
	for (int i = 0; i < 4; i++) {
		SDL_RenderCopy(g_renderer, texture_, &source_rectangle_[i], &destination_rectangle_[i]);
	}
}