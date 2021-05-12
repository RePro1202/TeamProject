#pragma once

#include "Core.h"

class Platform : public PhaseInterface
{
private:
	SDL_Texture* platform_texture_;
	SDL_Rect platform_source_rect_;
	SDL_Rect platform_destination_rect_;
public:
	Platform();
	~Platform();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};