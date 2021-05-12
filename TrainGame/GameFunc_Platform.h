#pragma once

#include "Core.h"

class Platform : public UserInterface
{
public:
	Platform();
	~Platform();
	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
};