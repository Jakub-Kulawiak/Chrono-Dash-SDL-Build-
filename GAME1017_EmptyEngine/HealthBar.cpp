#include "HealthBar.h"
#include "Engine.h"

HealthBar::HealthBar(SDL_Rect s, SDL_FRect d) : SpriteObject(s, d) { }

void HealthBar::Update()
{

}

void HealthBar::Render()
{
	SDL_RenderCopyF(Engine::Instance().GetRenderer(), TEMA::GetTexture("HealthBar"), &m_src, &m_dst);
}

void HealthBar::LoseHealth()
{
	if (m_src.x == 64)
	{
		m_src.y += m_src.h;
		m_src.x = 0;
	}
	else
	{
		m_src.x += m_src.w;
	}
}