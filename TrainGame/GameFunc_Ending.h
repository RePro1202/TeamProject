#pragma once

#include "Core.h"

class Ending : public PhaseInterface
{
public:
	Ending();
	~Ending();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};