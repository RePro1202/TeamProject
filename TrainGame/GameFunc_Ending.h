#pragma once

#include "Core.h"

class Ending : public PhaseInterface
{
private:
	SDL_Texture* ending_title_texture_;
	SDL_Rect ending_title_rect_;
	TTF_Font* ending_font_;
	SDL_Color black_;
public:
	Ending();
	~Ending();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};