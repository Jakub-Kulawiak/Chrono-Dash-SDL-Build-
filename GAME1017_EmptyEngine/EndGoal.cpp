#include "EndGoal.h"


EndGoal::EndGoal(SDL_Rect src, SDL_FRect dst) : SpriteObject(src,dst)
{
}

EndGoal::~EndGoal() = default;


void EndGoal::Update()
{
	
}

void EndGoal::Render()
{
	
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("portal"),
		&m_src, &m_dst,0.0, nullptr, SDL_FLIP_HORIZONTAL);
}


