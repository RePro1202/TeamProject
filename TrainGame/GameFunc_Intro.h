#pragma once

#include "Core.h"

class Intro : public PhaseInterface
{
private:
	SDL_Texture* intro_texture_;
	SDL_Rect intro_source_rect_;
	SDL_Rect intro_destination_rect_;
public:
	Intro();
	~Intro();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};