#include "EnemySpider.h"


EnemySpider::EnemySpider(SDL_Rect s, SDL_FRect d) : AnimatedSpriteObject(s, d)
{
	m_state = MOVE;
	m_velX = 0.0;
	m_velY = 0.0;
	m_accelX = 0.0;
	m_accelY = 0.0;
	m_frame = 0;
	m_facingLeft = false;
	m_grounded = true;
	m_timer = 0;


}

void EnemySpider::Update()
{


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

		break;
	}

	}


	m_velX += m_accelX;
	m_dst.x += (float)m_velX; // May have to cast to (int)


	m_accelX = m_accelY = 0.0; // Resetting acceleration every frame.



	// Invoke the animation.
	Animate();
}

void EnemySpider::Render()
{
	if (m_facingLeft == true)
	{
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemySpider"),
			&m_src, &m_dst, m_grounded, nullptr, SDL_FLIP_NONE);
	}
	else if (m_facingLeft == false)
	{
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("enemySpider"),
			&m_src, &m_dst, m_grounded, nullptr, SDL_FLIP_HORIZONTAL);
	}
}

// Getters

double EnemySpider::GetVelX()
{
	return m_velX;
}

double EnemySpider::GetVelY()
{
	return m_velY;
}

bool EnemySpider::IsGrounded()
{
	return m_grounded;
}

// Setters

void EnemySpider::SetAccelX(double a)
{
	m_accelX = a;
}

void EnemySpider::SetAccelY(double a)
{
	m_accelY = a;
}

void EnemySpider::SetGrounded(bool g)
{
	m_grounded = g;
}



