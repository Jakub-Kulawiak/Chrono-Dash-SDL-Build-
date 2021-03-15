#include "RangedEnemy.h"
#include "PlatformPlayer.h"

//adjustments could be made to change the sprite according to what type of enemy, currently only is hard coded for a single type of enemy
// could be changed to become more of a template than it already is 

EnemyBullet::EnemyBullet(SDL_Rect s, SDL_FRect d, double angle) : SpriteObject(s,d) // TODO: find sprite for enemy bullet
{
	m_angle = angle;
	setStatus(true);
}

void EnemyBullet::Update()
{
	// will check the angle the bullet was given by the enemy and update it accordingly
	if (m_angle >= 180)
	{
		m_dst.x -= 7;
	}
	else if (m_angle <= 0)
	{
		m_dst.x += 7;
	}

	if (m_time == 200) // plan to use this to limit the bullet's range rather than have it go for infinity
	{
		std::cout << "time has been reached" << std::endl; // remove when testing is done
		setStatus(false);
		m_time = 0; 
	}
	
	m_time++;
}

void EnemyBullet::Render()
{
	//TODO: bullet sprite
	SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture("Circle"), 
		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
}

void EnemyBullet::setStatus(bool status)
{
	m_active = status;
}

bool EnemyBullet::getStatus()
{
	return m_active;
}

RangedEnemy::RangedEnemy(SDL_Rect s, SDL_FRect d, RangedState state) : AnimatedSpriteObject(s,d)
{
	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
	// enemies will default facing left
	m_angle = 0; 
	m_timer = 0; // used to decide when direction changes
	m_radius = 30; //will be changed once sprite is decided upon
	m_state = state;
	m_facingLeft = true;
	m_bulletAngle = 180; // aids bullet creation 
	m_accelX = m_accelY = m_velX = m_velY = 0.0;
	m_grounded = true; // a check will be needed within the game state
	
}

void RangedEnemy::Update()
{
	if(m_timer >= 300) 
	{
		// spawns bullets 
		m_bullets.push_back(new EnemyBullet({ 0,0,29,18 }, { this->GetDst()->x,this->GetDst()->y + 25, 20,20 }, m_bulletAngle));
		m_bullets.shrink_to_fit();
		// change direction 
		ChangeDirection();
		m_timer = 0;
	}

	switch (m_state) // currently a enemy won't change between states, but that can be reworked in later renditions
	{
		
	case CAMPING: // enemy will stay and turn in place
		{
		break;
		}
	case MOVING: // will move left and right
		{
		if (m_facingLeft == true)
			m_accelX = -1.5;

		else if (m_facingLeft == false)
			m_accelX = +1.5;
	
		break;
		}
	case JUMPING: // will jump up and down
		{
		m_accelY = -JUMPFORCE;
		m_grounded = false;
		
		break;
		}
	}

	if( IsGrounded() == false)
	{
		m_accelY = +GRAV;
	}
	// enemy movement calculations
	m_velX += m_accelX;
	m_velX *= (m_grounded ? m_drag : 1.0); // Cheeky deceleration.
	m_velX = std::min(std::max(m_velX, -m_maxVelX), m_maxVelX);
	m_dst.x += (float)m_velX; // May have to cast to (int)

	m_velY += m_accelY + m_grav;
	m_velY = std::min(std::max(m_velY, -m_maxVelY), m_maxVelY); 
	m_dst.y += (float)m_velY;

	m_accelX = m_accelY = 0.0; // Resetting acceleration every frame.


	// bullet update
	for(auto i = 0; i < m_bullets.size(); i++)
	{
		if(m_bullets[i]->getStatus() == false)
		{
			delete m_bullets[i];
			m_bullets[i] = nullptr;
			m_bullets.erase(m_bullets.begin() + i);
			m_bullets.shrink_to_fit();
			break;
		}
		m_bullets[i]->Update();
	}

	m_timer++;
}

void RangedEnemy::Render() //TODO: select enemy sprite
{
	if (m_facingLeft == false)
	{
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture(""),
			&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
	}
	else if (m_facingLeft == true)
	{
		SDL_RenderCopyExF(Engine::Instance().GetRenderer(), TEMA::GetTexture(""),
			&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_HORIZONTAL);
	}

	for(auto i = 0; i < m_bullets.size(); i++)
	{
		m_bullets[i]->Render();
	}
}

bool RangedEnemy::IsGrounded() const
{
	return m_grounded;
}

void RangedEnemy::SetGrounded(bool g)
{
	m_grounded = g;
}

double RangedEnemy::GetVelX() const
{
	return m_velX;
}

double RangedEnemy::GetVelY() const
{
	return m_velY;
}

void RangedEnemy::Stop()
{
	StopX();
	StopY();
}

void RangedEnemy::StopX()
{
	m_velX = 0.0;
}

void RangedEnemy::StopY()
{
	m_velY = 0.0;
}

void RangedEnemy::SetAccelX(double a)
{
	m_accelX = a;
}

void RangedEnemy::SetAccelY(double a)
{
	m_accelY = a;
}

void RangedEnemy::ChangeDirection()
{
	if (m_facingLeft == true)
	{
		m_facingLeft = false;
		m_bulletAngle = 180;
	}
	else if(m_facingLeft == false)
	{
		m_facingLeft = true;
		m_bulletAngle = 0;
	}
}