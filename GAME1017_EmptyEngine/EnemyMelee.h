#pragma once
#ifndef _ENEMYMELEE_H_
#define _ENEMYMELEE_H_
#include "GameObject.h"

//WIP

class EnemyMelee : public AnimatedSpriteObject
{
public: // Methods.
	EnemyMelee(SDL_Rect s, SDL_FRect d);
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
	enum enemyMeleeState { IDLE, MOVE, ATTACK} m_state;

};

#endif  