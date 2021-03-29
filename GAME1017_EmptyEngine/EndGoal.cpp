#include "EndGoal.h"


void EndGoal::SetRekts(const SDL_Rect src, const SDL_Rect dst)
{
	m_src = src;
	m_dst = dst;
}
SDL_Rect* EndGoal::GetRectSrc()
{
	return &m_src;
}
SDL_Rect* EndGoal::GetRectDst()
{
	return &m_dst;
}

void EndGoal::Update()
{
	this->m_dst.x -= 2;
}


