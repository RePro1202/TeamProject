#pragma once

#include "Core.h"

enum EventsName
{
	EVENT_NONE,
	EVENT_HEAT,
	EVENT_COLD,
	EVENT_MERCHANT,
	EVENT_PSEUDO,
	EVENT_EMERGENCY,
	EVENT_WILD,
	EVENT_DRUNK
};

class Events
{
private:
	SDL_Texture* events_texture_;
	SDL_Rect events_source_rect_[8];
	SDL_Rect events_destination_rect_[8];
public:
	Events();
	~Events();

	Events getEvent(int num);

	SDL_Texture* getEventTexture();
	SDL_Rect getEventSource(int num);
	SDL_Rect getEventDestination(int num);
};