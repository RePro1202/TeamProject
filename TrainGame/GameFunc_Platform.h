#pragma once

#include "Core.h"

class Platform : public PhaseInterface
{
private:
	SDL_Texture* g_platform_texture;
	SDL_Rect g_platform_source_rect;
	SDL_Rect g_platform_destination_rect;
public:
	Platform();
	~Platform();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};