#pragma once
#ifndef __PLAYER__
#define __PLAYER__
#include "Engine.h"
#define JUMPFORCE 50

class Player : public Sprite
{
private:
	const Uint8* m_keystates;
	int m_speed;
	int m_gravity;
	int m_jumpForce;
	int m_accelY;
	int m_velY;
	int m_maxVelY;
public:
	Player();
	~Player();

	void Update();
	void Jump();
	
	int GetSpeed()
	{
		return m_speed;
	}

	int GetGravity()
	{
		return m_gravity;
	}
	int GetJumpForce()
	{
		return m_jumpForce;
	}
};

#endif /* defined (__PLAYER__) */