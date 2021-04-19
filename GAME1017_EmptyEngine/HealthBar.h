#pragma once
#ifndef _HEALTH_BAR_
#define _HEALTH_BAR_
#include "GameObject.h"

class HealthBar : public SpriteObject
{
public:
	HealthBar(SDL_Rect s, SDL_FRect d);
	void Update();
	void Render();
	void LoseHealth();
};

#endif