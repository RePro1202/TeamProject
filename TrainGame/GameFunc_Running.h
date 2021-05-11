#pragma once

#include "Core.h"

class Running : public PhaseInterface
{
public:
	Running();
	~Running();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};