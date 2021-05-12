#include "Core.h"

void InitGame() {
	g_flag_running = true;
}

void ClearGame() {
}


//// UserInterface////
UserInterface::UserInterface()
{
	SDL_Surface* temp_surface = IMG_Load("../../Resources/UI.png");
	texture_ = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	// Time
	source_rectangle_[0].x = 9;
	source_rectangle_[0].y = 7;
	source_rectangle_[0].w = 201 - source_rectangle_[0].x;
	source_rectangle_[0].h = 138 - source_rectangle_[0].y;

	destination_rectangle_[0].x = 10;
	destination_rectangle_[0].y = 10;
	destination_rectangle_[0].w = source_rectangle_[0].w;
	destination_rectangle_[0].h = source_rectangle_[0].h;

	// Score
	source_rectangle_[1].x = 215;
	source_rectangle_[1].y = 40;
	source_rectangle_[1].w = 421 - source_rectangle_[1].x;
	source_rectangle_[1].h = 136 - source_rectangle_[1].y;

	destination_rectangle_[1].x = 800;
	destination_rectangle_[1].y = 10;
	destination_rectangle_[1].w = source_rectangle_[1].w;
	destination_rectangle_[1].h = source_rectangle_[1].h;

	// Speed
	source_rectangle_[2].x = 436;
	source_rectangle_[2].y = 65;
	source_rectangle_[2].w = 676 - source_rectangle_[2].x;
	source_rectangle_[2].h = 136 - source_rectangle_[2].y;

	destination_rectangle_[2].x = 800;
	destination_rectangle_[2].y = 130;
	destination_rectangle_[2].w = source_rectangle_[2].w;
	destination_rectangle_[2].h = source_rectangle_[2].h;
	
	// Train_pos
	source_rectangle_[3].x = 12;
	source_rectangle_[3].y = 151;
	source_rectangle_[3].w = 576 - source_rectangle_[3].x;
	source_rectangle_[3].h = 294 - source_rectangle_[3].y;

	destination_rectangle_[3].x = 220;
	destination_rectangle_[3].y = 10;
	destination_rectangle_[3].w = source_rectangle_[3].w;
	destination_rectangle_[3].h = source_rectangle_[3].h;
}

UserInterface::~UserInterface()
{
	SDL_DestroyTexture(texture_);
}

void UserInterface::Show_UI() 
{
	for (int i = 0; i < 4; i++) {
		SDL_RenderCopy(g_renderer, texture_, &source_rectangle_[i], &destination_rectangle_[i]);
	}
}