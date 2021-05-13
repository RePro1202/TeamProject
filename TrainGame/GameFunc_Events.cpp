#include "GameFunc_Events.h"

Events::Events()
{
	SDL_Surface* event_surface = IMG_Load("../../Resources/Event.png");
	SDL_SetColorKey(event_surface, SDL_TRUE, SDL_MapRGB(event_surface->format, 120, 150, 190));
	events_texture_ = SDL_CreateTextureFromSurface(g_renderer, event_surface);
	SDL_FreeSurface(event_surface);

	// Event Box
	events_source_rect_[0] = { 800, 397 , 250 , 219 };
	events_destination_rect_[0] = { 0, 0, 200, 180 };

	// 더위
	events_source_rect_[1] = { 27, 8 ,247 , 300 };
	events_destination_rect_[1] = { 0, 0, 200, 180 };
	// 추위
	events_source_rect_[2] = { 290, 10 , 255 , 300 };
	events_destination_rect_[2] = { 0, 0, 200, 180 };
	// 잡상인
	events_source_rect_[3] = { 608, 30 , 186 , 285 };
	events_destination_rect_[3] = { 0, 0, 200, 180 };
	// 사이비
	events_source_rect_[4] = { 850, 51 , 138 , 229 };
	events_destination_rect_[4] = { 0, 0, 200, 180 };
	// 긴급정지
	events_source_rect_[5] = { 76, 435 , 148 , 146 };
	events_destination_rect_[5] = { 0, 0, 200, 180 };
	// 야생동물
	events_source_rect_[6] = { 286, 437 , 180 , 153 };
	events_destination_rect_[6] = { 0, 0, 200, 180 };
	// 취객
	events_source_rect_[7] = { 590, 422 , 205 , 196 };
	events_destination_rect_[7] = { 0, 0, 200, 180 };
}

Events::~Events()
{
	SDL_DestroyTexture(events_texture_);
}

Events Events::getEvent(int num)
{
	getEventTexture();
	getEventSource(num);
	getEventDestination(num);
}

SDL_Texture* Events::getEventTexture()
{
	return events_texture_;
}

SDL_Rect Events::getEventSource(int num)
{
	return events_source_rect_[num];
}

SDL_Rect Events::getEventDestination(int num)
{
	return events_destination_rect_[num];
}