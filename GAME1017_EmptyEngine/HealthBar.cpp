#include "HealthBar.h"
#include "Engine.h"

HealthBar::HealthBar(SDL_Rect s, SDL_FRect d) : SpriteObject(s, d) {}

void HealthBar::Update()
{
	
}

void HealthBar::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture("Health Bar"), &m_src, &m_dst);
}