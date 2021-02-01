#pragma once
#ifndef __EndGoal__
#define __EndGoal__
#include <SDL_rect.h>
#include "SDL_image.h"
#include "SDL.h"

class EndGoal 
{
private:
	SDL_Rect m_src;
	SDL_Rect m_dst;

public:
	void SetRekts(const SDL_Rect src, const SDL_Rect dst);
	SDL_Rect* GetRectSrc();
	SDL_Rect* GetRectDst();
};

#endif
#pragma once
