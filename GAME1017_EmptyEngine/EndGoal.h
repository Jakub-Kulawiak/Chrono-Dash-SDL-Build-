#pragma once
#ifndef __EndGoal__
#define __EndGoal__
#include <SDL_rect.h>
#include "GameObject.h"
#include "States.h"
#include "StateManager.h"
#include "SDL_image.h"
#include "SDL.h"

class EndGoal : public SpriteObject 
{
private:


public:
	EndGoal(SDL_Rect src, SDL_FRect dst);
	~EndGoal();
	void Update() override;
	void Render() override;
};

#endif
#pragma once
