#pragma once
#ifndef _ENGINE_H_
#define _ENGINE_H_

#include<vector>
#include "SDL_image.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <iostream>
#include<time.h>
#include "EndGoal.h"
#define FPS 120
#define WIDTH 1024
#define HEIGHT 768
using namespace std;

class Sprite
{
protected:
	SDL_Rect m_src;
	SDL_Rect m_dst;
public:

	void SetRekts(const SDL_Rect src, const SDL_Rect dst)
	{
		m_src = src;
		m_dst = dst;
	}
	SDL_Rect* GetRectSrc()
	{
		return &m_src;
	}
	SDL_Rect* GetRectDst()
	{
		return &m_dst;
	}
	void Update()
	{
		m_dst.x -= 2;
	}


};

class AnimatedSprite :public Sprite
{
private:
	int m_frame = 0, // "current frame" property
		m_frameMax = 15, // number of frames to display each sprite
		m_sprite = 0, // which sprite is on display
		m_spriteMax = 2; // number of sprites in the animation

public:
	int m_flip = 0;
	void SetRects(SDL_Rect s, SDL_Rect d)
	{
		m_src = s;
		m_dst = d;
	}
	bool m_faceLeft = 0; // 1 = left | 0 = right
	void FlipLeft()
	{
		if (m_faceLeft == 0)
			m_faceLeft = 1;
	}
	void FlipRight()
	{
		if (m_faceLeft == 1)
			m_faceLeft = 0;
	}


	void Animate()
	{
		if (m_sprite >= m_spriteMax)
		{
			m_sprite = 0;
		}
		if (m_frame == m_frameMax) // if max frames has been hit
		{
			m_frame = 0;
			m_sprite++;

			if (m_sprite == m_spriteMax) // if sprite limit is hit
			{
				m_sprite = 0;
			}
			m_src.x = m_src.w * m_sprite; // sets the source box location on x axis
		}
		m_frame++;
	}
};

class EnemySprite :public Sprite
{
private:

public:

	void SetRects(SDL_Rect s, SDL_Rect d)
	{
		m_src = s;
		m_dst = d;
	}




};

class Bullet
{
private:
	SDL_Rect m_rect; // rect ofr dst
public:
	Bullet(SDL_Point spawnLoc = { 512, 384 }) // non-defalut constrctor
	{
		this->m_rect.x = spawnLoc.x;
		this->m_rect.y = spawnLoc.y;
		this->m_rect.w = 8;
		this->m_rect.h = 8;

	}

	~Bullet() // Destructor
	{
		cout << "de-alocating bullet" << endl;
	}

	void SetLoc(SDL_Point loc)
	{
		m_rect.x = loc.x;
		m_rect.y = loc.y;
	}

	void Update()
	{
		this->m_rect.x += 3;
	}
	void Render(SDL_Renderer* rend)
	{
		SDL_SetRenderDrawColor(rend, 255, 25, 0, 255);
		SDL_RenderFillRect(rend, &m_rect);
	}

	SDL_Rect* GetRekt()
	{
		return &m_rect;
	}
};

class Engine
{
private: // private properties.
	bool m_running = false;
	Uint32 m_start, m_end, m_delta, m_fps;
	const Uint8* m_keystates;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	// variables (temporary)
	int m_speed = 4, m_gravity = 6, m_jumpForce = 100;

	
	// textures (consider implementing texture map when figured out)
	SDL_Texture* m_testBackground, * m_realBackground0, * m_realBackground1, * m_realBackground2;
	SDL_Texture* m_testPlayer;
	SDL_Texture* m_endGoalTexture;
	SDL_Texture* m_testEnemy;
	// sprites
	Sprite m_ground, m_ground2, m_back0, m_back1, m_back1Scroll, m_back2, m_back2Scroll;
	AnimatedSprite m_player;
	EndGoal m_endGoal;
	EnemySprite m_enemy;
	vector<Bullet*> m_bullets;
	// Sounds
	Mix_Chunk* m_jump;
	Mix_Chunk* m_damage;
	Mix_Chunk* m_shoot;
	


private: // private method prototypes.
	int Init(const char* title, int xPos, int yPos, int width, int height, int flags);
	void Clean();
	void Wake();
	void HandleEvents();
	bool KeyDown(SDL_Scancode c);
	void Update();
	void Render();
	void Sleep();
	

public: // public method prototypes.
	int Run();
};

#endif

// Reminder: you can ONLY have declarations in headers, not logical code
