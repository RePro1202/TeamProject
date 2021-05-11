#pragma once

#include "Core.h"

class Intro : public PhaseInterface
{
public:
	Intro();
	~Intro();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};