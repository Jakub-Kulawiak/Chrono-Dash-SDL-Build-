#pragma once
#ifndef _ENEMYMELEEBAT_H_
#define _ENEMYMELEEBAT_H_
#include "GameObject.h"

//WIP

class EnemyMeleeBat : public AnimatedSpriteObject
{
public: // Methods.
	EnemyMeleeBat(SDL_Rect s, SDL_FRect d);
	void Update();
	void Render();
	void SetAccelX(double a);
	void SetAccelY(double a);
	double GetVelX();
	double GetVelY();
	bool IsGrounded();
	void SetGrounded(bool g);


private: // Properties.
	bool m_grounded, m_facingLeft;
	double m_accelX,
		m_accelY,
		m_velX,
		m_maxVelX,
		m_velY,
		m_maxVelY,
		m_drag,
		m_grav;
	int m_timer;

	enum enemyMeleeBatState { IDLE, MOVE, ATTACK } m_state;

};

#endif  