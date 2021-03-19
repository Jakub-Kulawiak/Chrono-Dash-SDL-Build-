#include "EnemyMeleeBat.h"
<<<<<<< Updated upstream

EnemyMeleeBat::EnemyMeleeBat(SDL_Rect s, SDL_FRect d) : AnimatedSpriteObject(s, d)
{
	m_state = IDLE;
=======
#include "PlatformPlayer.h"




EnemyMeleeBat::EnemyMeleeBat(SDL_Rect s, SDL_FRect d) : AnimatedSpriteObject(s, d)
{
	m_state = MOVE;
>>>>>>> Stashed changes
	m_velX = 0.0;
	m_velY = 0.0;
	m_accelX = 0.0;
	m_accelY = 0.0;
<<<<<<< Updated upstream
	m_grounded = true;
	SetAnimation(1, 0, 1);
=======
	m_frame = 0;
	m_facingLeft = false;
	m_grounded = true;
	m_timer = 0;


>>>>>>> Stashed changes
}

void EnemyMeleeBat::Update()
{
<<<<<<< Updated upstream
	switch (m_state)
	{
	case IDLE:
		//SetAnimation(1, 0, 1);

		break;
	case MOVE:

		break;

	case ATTACK:
=======


	switch (m_state)
	{
	case IDLE:
	{
		// fMax, sMin, sMax, srcY

		SetAnimation(5, 1, 5);




		break;
	}

	case MOVE:
	{

			
		// Right
		if (m_facingLeft == false)
		{

			m_accelX += 0.01;
			m_timer += 1;
		}

		// Left
		else if (m_facingLeft == true)
		{
			m_accelX -= 0.01;
			m_timer -= 1;
		}

		if (m_timer == 120)
		{
			m_facingLeft = true;
		}

		else if (m_timer == -120)
		{
			m_facingLeft = false;
		}





		std::cout << m_timer << endl;





		break;
	}


	case ATTACK:
	{
>>>>>>> Stashed changes

		break;
	}

<<<<<<< Updated upstream
	Animate();

=======
	}


	m_velX += m_accelX;
	m_dst.x += (float)m_velX; // May have to cast to (int)


	m_accelX = m_accelY = 0.0; // Resetting acceleration every frame.

	Animate();

	// Invoke the animation.
	//Animate();
>>>>>>> Stashed changes
}

void EnemyMeleeBat::Render()
{
<<<<<<< Updated upstream
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemyMeleeBat"),
		&m_src, &m_dst, m_grounded, nullptr, SDL_FLIP_NONE);
=======
	if (m_facingLeft == false)
	{
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemyMeleeBat"),
			&m_src, &m_dst, m_grounded, nullptr, SDL_FLIP_NONE);
	}
	else if (m_facingLeft == true)
	{
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemyMeleeBat"),
			&m_src, &m_dst, m_grounded, nullptr, SDL_FLIP_HORIZONTAL);
	}
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
