#include "RangedEnemy.h"

//adjustments could be made to change the sprite according to what type of enemy, currently only is hard coded for a single type of enemy
// could be changed by creating an enemy enum class and using that as a texture controller

EnemyBullet::EnemyBullet(SDL_Rect s, SDL_FRect d) : SpriteObject(s,d) // TODO: find sprite for enemy bullet
{

	


	
}

void EnemyBullet::Update()
{
	// will check the angle the bullet was given by the enemy and update it accordingly
	if (m_angle == 180)
	{
		m_dst.x -= 7;
	}
	else if (m_angle == 0)
	{
		m_dst.x += 7;
	}

	if (m_time == 200) // plan to use to limit the bullet's range rather than have it go for infinity
	{
		m_time = 0; // TODO: decide whether the de-spawning will be done in bullet object or will be linked to enemy
	}
	
	m_time++;
}

void EnemyBullet::Render()
{
	//TODO: bullet sprite
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture(""), 
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
}

RangedEnemy::RangedEnemy(SDL_Rect s, SDL_FRect d, RangedState state) : AnimatedSpriteObject(s,d)
{
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	
	m_angle = 0;
	m_timer = 0;
	m_radius = 30; //will be changed once sprite is decided upon
	m_state = state;
	
}

void RangedEnemy::Update()
{
	switch (m_state)
	{
		
	case CAMPING: // enemy will only stay in one place and maybe turn in place
		{
		if (m_facingLeft)
		{
			m_facingLeft = false;
			m_bulletAngle = 180;
		}	
		else if (!m_facingLeft)
		{
			m_facingLeft = true;
			m_bulletAngle = 0;
		}	
		break;
		}
	case MOVING: // will move left and right
		{
		if (m_facingLeft == true)
		{
			
		}
		else if (m_facingLeft == false)
		{

		}
		break;
		}
	case JUMPING: // will jump up and down
		{
		// just place upwards velocity increase


			
		break;
		}
	default: ;
	}

	if( IsGrounded() == false)
	{
		//place downwards velocity below
		
	}
	
	
}

void RangedEnemy::Render()
{
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture(""),
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
	// if bullets will be part of enemy and not the level, bullet render function below

	
}

bool RangedEnemy::IsGrounded()
{
}

void RangedEnemy::SetGrounded(bool g)
{
}

double RangedEnemy::GetVelX()
{
}

double RangedEnemy::GetVelY()
{
}
