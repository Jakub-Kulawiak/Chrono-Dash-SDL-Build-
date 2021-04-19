#pragma once
#ifndef _PLATFORMPLAYER_H_
#define _PLATFORMPLAYER_H_
#include <vector>
#include "GameObject.h"
#define GRAV 0.0
#define JUMPFORCE 25.0

class PlayerBullet : public AnimatedSpriteObject
{
public:
	PlayerBullet(SDL_Rect s, SDL_FRect d, bool facingLeft);
	void Update();
	void Render();
private:
	int m_bulletSpeed;
	int m_facingLeft;
};

class PlatformPlayer : public AnimatedSpriteObject
{
public: // Methods.
	PlatformPlayer(SDL_Rect s, SDL_FRect d);
	void Update();
	void Render();
	void Stop();
	void StopX();
	void StopY();
	void SetAccelX(double a);
	void SetAccelY(double a);
	bool IsFacingLeft();
	bool IsGrounded();
	void SetGrounded(bool g);
	double GetVelX();
	double GetVelY();
	void SetX(float x);
	void SetY(float y);
	int GetHealth();
	void LoseHealth();
private: // Properties.
	vector<PlayerBullet*> m_bullets;
	int m_shootCounter = 0, m_deathCounter = 0;
	bool m_grounded, m_facingLeft;
	double m_accelX,
		m_accelY,
		m_velX,
		m_maxVelX,
		m_velY,
		m_maxVelY,
		m_drag,
		m_grav;
	enum PlayerState { STATE_IDLING, STATE_RUNNING, STATE_JUMPING, STATE_SHOOTING, STATE_DEAD } m_state;
	int m_health;
};

#endif