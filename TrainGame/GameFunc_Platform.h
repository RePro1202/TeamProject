#pragma once

#include "Core.h"

enum TrainState
{
	TRAIN_IN,
	TRAIN_STOP,
	TRAIN_OUT
};

class Platform : public PhaseInterface
{
private:
	SDL_Texture* platform_texture_;
	SDL_Rect platform_source_rect_;
	SDL_Rect platform_destination_rect_;

	SDL_Texture* train_texture_;
	SDL_Rect train_source_rect_;
	SDL_Rect train_destination_rect_;
	int train_state_, train_speed_, stop_destination_, consumption_time_;
public:
	Platform();
	~Platform();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};