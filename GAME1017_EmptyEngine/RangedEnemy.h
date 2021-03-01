#pragma once
#ifndef _RANGED_
#define _RANGED_

#include "GameObject.h"


class EnemyBullet : public SpriteObject
{
private:

	int m_angle;

public:

	EnemyBullet(SDL_Rect s, SDL_FRect d);
	~EnemyBullet() = default;

	void Update() override;
	void Render() override;
	
};

class RangedEnemy : public AnimatedSpriteObject
{
private:
	SDL_FPoint m_center;
	int m_timer;
	double m_angle,
		m_radius,
		m_accelX,
		m_accelY,
		m_velX,
		m_maxVelX,
		m_velY,
		m_maxVelY,
		m_drag,
		m_grav;
	
	bool m_grounded, m_facingLeft;

	enum RangedState {CAMPING, MOVING, JUMPING};

public:

	RangedEnemy(SDL_Rect s, SDL_FRect d, RangedState);
	~RangedEnemy() = default;
	void Update() override;
	void Render() override;
	bool IsGrounded();
	void SetGrounded(bool g);
	double GetVelX();
	double GetVelY();
	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(double a);
	void SetAccelY(double a);
};





#endif

//Jakub Kulawiak