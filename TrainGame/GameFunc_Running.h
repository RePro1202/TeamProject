#pragma once

#include "Core.h"

class Running : public PhaseInterface
{
private:
	SDL_Texture* background_texture_;
	SDL_Rect background_source_rect_[2];
	SDL_Rect background_destination_rect_[2];

	int speed_;
	int distance_;

public:
	Running();
	~Running();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};