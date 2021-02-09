#include "Player.h"

Player::Player()
{
	SetRects({ 0,0,43,53 }, { 250, 400, 43,53 });
	int m_speed = 4;
	int m_gravity = GRAVITY;
	int m_jumpForce = JUMPFORCE;
	int m_accelY;
	int m_velY;
	int m_maxVelY;
}

Player::~Player()
{

}

void Player::Jump()
{
	
}