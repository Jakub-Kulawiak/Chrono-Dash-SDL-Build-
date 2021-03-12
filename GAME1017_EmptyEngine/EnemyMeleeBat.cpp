#include "EnemyMeleeBat.h"

EnemyMeleeBat::EnemyMeleeBat(SDL_Rect s, SDL_FRect d) : AnimatedSpriteObject(s, d)
{
	m_state = IDLE;
	m_velX = 0.0;
	m_velY = 0.0;
	m_accelX = 0.0;
	m_accelY = 0.0;
	m_grounded = true;
	SetAnimation(1, 0, 1);
}

void EnemyMeleeBat::Update()
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

void EnemyMeleeBat::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemyMeleeBat"),
		&m_src, &m_dst, m_grounded, nullptr, SDL_FLIP_NONE);
}

// Getters

double EnemyMeleeBat::GetVelX()
{
	return m_velX;
}

double EnemyMeleeBat::GetVelY()
{
	return m_velY;
}

bool EnemyMeleeBat::IsGrounded()
{
	return m_grounded;
}

// Setters

void EnemyMeleeBat::SetAccelX(double a)
{
	m_accelX = a;
}

void EnemyMeleeBat::SetAccelY(double a)
{
	m_accelY = a;
}

void EnemyMeleeBat::SetGrounded(bool g)
{
	m_grounded = g;
}

