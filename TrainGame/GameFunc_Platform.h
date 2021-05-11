#pragma once

#include "Core.h"

class Platform : public PhaseInterface
{
public:
	Platform();
	~Platform();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};