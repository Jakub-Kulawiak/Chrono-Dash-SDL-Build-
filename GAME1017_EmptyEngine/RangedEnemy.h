#pragma once
#ifndef _RANGED_
#define _RANGED_

#include <vector>
#include "GameObject.h"


class EnemyBullet : public SpriteObject
{
private:
	bool m_active;
	double m_angle;
	int	m_time = 0;

public:

	EnemyBullet(SDL_Rect s, SDL_FRect d, double angle);
	~EnemyBullet() = default;

	void Update() override;
	void Render() override;

	void setStatus(bool status);
	bool getStatus();
	
};

class RangedEnemy : public AnimatedSpriteObject
{
private:
	SDL_FPoint m_center;
	int m_timer,
		m_state;
	
	double m_angle,
		m_bulletAngle,
		m_radius,
		m_accelX,
		m_accelY,
		m_velX,
		m_maxVelX,
		m_velY,
		m_maxVelY,
		m_drag,
		m_grav;
	
	bool m_grounded, m_facingLeft; // basic checks
	vector<EnemyBullet*> m_bullets;

	enum RangedState {CAMPING, MOVING, JUMPING}; // enemy states

public:

	RangedEnemy(SDL_Rect s, SDL_FRect d, RangedState);
	~RangedEnemy() = default;
	void Update() override;
	void Render() override;
	bool IsGrounded() const;
	void SetGrounded(bool g);
	double GetVelX() const;
	double GetVelY() const;
	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(double a);
	void SetAccelY(double a);

	void ChangeDirection();
};





#endif

//Jakub Kulawiak