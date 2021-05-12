#pragma once

#include "Core.h"

class Running : public PhaseInterface
{
private:
	SDL_Texture* g_background_texture;
	SDL_Rect g_background_source_rect;
	SDL_Rect g_background_destination_rect;
public:
	Running();
	~Running();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};