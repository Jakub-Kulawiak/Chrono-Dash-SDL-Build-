#include "LoseStateObjects.h"

LoseStateObjects::LoseStateObjects(SDL_Rect s, SDL_FRect d) : AnimatedSpriteObject(s, d)
{
	m_grounded = false;
}

void LoseStateObjects::Update()
{
}

void LoseStateObjects::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("gameOver"),
		&m_src, &m_dst, m_grounded, nullptr, SDL_FLIP_NONE);
}
