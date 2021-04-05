#pragma once
#ifndef _ENEMYSPIDER_H_
#define _ENEMYSPIDER_H_
#include "GameObject.h"

//WIP

class EnemySpider : public AnimatedSpriteObject
{
public: // Methods.
	EnemySpider(SDL_Rect s, SDL_FRect d);
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

	enum enemySpiderState { IDLE, MOVE, ATTACK } m_state;

};

#endif  