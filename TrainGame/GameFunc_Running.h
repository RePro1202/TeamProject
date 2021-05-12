#pragma once

#include "Core.h"

class Running : public UserInterface
{
public:
	Running();
	~Running();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};