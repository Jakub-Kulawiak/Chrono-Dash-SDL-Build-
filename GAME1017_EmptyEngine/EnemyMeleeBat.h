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

<<<<<<< Updated upstream
=======

>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
	int m_timer;

>>>>>>> Stashed changes
	enum enemyMeleeState { IDLE, MOVE, ATTACK } m_state;

};

<<<<<<< Updated upstream
#endif  
=======
#endif  #pragma once
>>>>>>> Stashed changes
