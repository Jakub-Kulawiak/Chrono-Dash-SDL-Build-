#pragma once
#ifndef _LOSE_STATE_OBJECTS_
#define _LOSE_STATE_OBJECTS_
#include "GameObject.h"

//WIP

class LoseStateObjects : public AnimatedSpriteObject
{
public: // Methods.
	LoseStateObjects(SDL_Rect s, SDL_FRect d);
	void Update();
	void Render();
private:
	bool m_grounded;
};

#endif  #pragma once
