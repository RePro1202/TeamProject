#pragma once

#include "Core.h"
#include "GameFunc_Events.h"

class Running : public PhaseInterface
{
private:
	SDL_Texture* background_texture_;
	SDL_Rect background_source_rect_[2];
	SDL_Rect background_destination_rect_[2];
	SDL_Texture* train_texture_;
	SDL_Rect train_source_rect_;
	SDL_Rect train_destination_rect_;
	int speed_;
	int distance_;

	Events* eve;
public:
	Running();
	~Running();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};