#include "EnemyMelee.h"
#include "PlatformPlayer.h"

EnemyMelee::EnemyMelee(SDL_Rect s, SDL_FRect d) : AnimatedSpriteObject(s, d)
{
	m_state = IDLE; 
	m_velX = 0.0;
	m_velY = 0.0; 
	m_accelX = 0.0;
	m_accelY = 0.0;
	m_grounded = true; 
	SetAnimation(1, 0, 1);
}

void EnemyMelee::Update()
{
	switch (m_state)
	{
	case IDLE:
		//SetAnimation(1, 0, 1);
	
	break;
	case MOVE:

		break;
	
	case ATTACK:

		break;
	}	
	
	Animate();

}

void EnemyMelee::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemyMelee"),
		&m_src, &m_dst, m_grounded, nullptr, SDL_FLIP_NONE);
}

// Getters

double EnemyMelee::GetVelX()
{
	return m_velX;
}

double EnemyMelee::GetVelY()
{
	return m_velY;
}

bool EnemyMelee::IsGrounded()
{
	return m_grounded;
}

// Setters

void EnemyMelee::SetAccelX(double a)
{
	m_accelX = a; 
}

void EnemyMelee::SetAccelY(double a)
{
	m_accelY = a;
}

void EnemyMelee::SetGrounded(bool g)
{
	m_grounded = g; 
}

