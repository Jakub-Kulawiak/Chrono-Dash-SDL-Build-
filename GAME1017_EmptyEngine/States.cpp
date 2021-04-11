#include "States.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "Engine.h"
#include "EventManager.h"
#include "PlatformPlayer.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Primitives.h"
#include "Button3.h"
#include "EnemyMelee.h"
#include "EnemyMeleeBat.h"
#include "EnemySpider.h"
#include "LoseStateObjects.h"
#include <iostream>

using namespace std;

void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

void State::Resume() {}

GameObject* State::GetGo(const std::string& s)
{ // Using 'std' just to show origin.
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		});
	if (it != m_objects.end())
		return it->second;
	else return nullptr;
}

auto State::GetIt(const std::string& s)
{
	auto it = std::find_if(m_objects.begin(), m_objects.end(),
		[&](const std::pair<std::string, GameObject*>& element)
		{
			return element.first == s;
		});
	return it;
}

// Begin TitleState
TitleState::TitleState() {}

void TitleState::Enter()
{

	TEMA::Load("Img/PholderButton.png", "play");
	TEMA::Load("Img/Thing.png", "bg");
	TEMA::Load("Img/PholderTitle.png", "title");
	m_objects.emplace(pair<string, GameObject*>("bg",
		new Image({ 0, 0, 1015, 768 }, { 0, 0, 1024, 768 }, "bg")));
	m_objects.emplace(pair<string, GameObject*>("play",
		new PlayButton({ 0, 0, 410, 100 }, { 412, 700, 200, 50 }, "play")));

	m_objects.emplace(pair<string, GameObject*>("title",
		new Image({ 0, 0, 927, 215 }, { 50, 50, 927, 215 }, "title")));
	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(32);
}

void TitleState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}

}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void TitleState::Exit()
{
	TEMA::Unload("title");
	TEMA::Unload("play");
	TEMA::Unload("bg");
	SOMA::StopMusic();
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr; // ;)
	}
}
// End TitleState

// Begin GameState
GameState::GameState() {}

void GameState::Enter() // Used for initialization.
{
	


	//Enemy Objects
	//Golem
	TEMA::Load("Img/Mini Golem Sprite Sheet.png", "enemyMelee");
	m_objects.emplace("enemyMelee", new PlatformPlayer({ 0, 0, 35,35 }, { 630.0f, 460.0f, 90.0f, 90.0f }));

	//Bat
	TEMA::Load("Img/Bat.png", "enemyMeleeBat");
	m_objects.emplace("enemyMeleeBat", new EnemyMeleeBat({ 0, 0, 16,16 }, { 120.0f, 370.0f, 80.0f, 80.0f }));

	//Spider
	TEMA::Load("Img/Spider Sprite Sheet.png", "enemySpider");
	m_objects.emplace("enemySpider", new EnemySpider({ 0, 0, 33,41 }, { 245.0f, 630.0f, 120.0f, 120.0f }));


	//Player Object
	TEMA::Load("Img/Player.png", "player");
	TEMA::Load("Img/Bullet.png", "Bullet");
	m_objects.emplace("player", new PlatformPlayer({ 0,0,577,529 }, { 300.0f, 450.0f, 100.0f, 100.0f }));

	TEMA::Load("Img/Tiles.png", "tiles");
	m_objects.emplace("level", new TiledLevel(50, 200, 32, 32, "Dat/Tiledata.txt", "Dat/Level1.txt", "tiles"));
}

void GameState::Update()
{


	/*if (m_pPlayer->GetHealth() <= 0)
	{
		LoseState* m_pPlayerHealth = new LoseState;
		STMA::ChangeState(m_pPlayerHealth);
	}*/
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
	{
		i->second->Update();
	}
	SDL_FRect* p = m_objects["player"]->GetDst(); // Copies address of player m_dst.
	PlatformPlayer* pp = static_cast<PlatformPlayer*>(m_objects["player"]);
	for (int i = 0; i < static_cast<TiledLevel*>(m_objects["level"])->GetObstacles().size(); i++)
	{
		SDL_FRect* t = static_cast<TiledLevel*>(m_objects["level"])->GetObstacles()[i]->GetDst();
		if (COMA::AABBCheck(*p, *t)) // Collision check between player rect and tile rect.
		{
			if ((p->y + p->h) - (float)pp->GetVelY() <= t->y)
			{ // Colliding with top side of tile.
				pp->StopY();
				pp->SetY(t->y - p->h);
				pp->SetGrounded(true);
			}
			else if (p->y - (float)pp->GetVelY() >= (t->y + t->h))
			{ // Colliding with bottom side of tile.
				pp->StopY();
				pp->SetY(t->y + t->h);
			}
			else if ((p->x + p->w) - (float)pp->GetVelX() <= t->x)
			{ // Colliding with left side of tile.
				pp->StopX();
				pp->SetX(t->x - p->w);
			}
			else if (p->x - (float)pp->GetVelX() >= (t->x + t->w))
			{ // Colliding with right side of tile.
				pp->StopX();
				pp->SetX(t->x + t->w);
			}
		}

	}

}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
		i->second->Render();
	if (dynamic_cast<GameState*>(STMA::GetStates().back())) // Check to see if current state is of type GameState
		State::Render();
}

void GameState::Exit()
{
	SOMA::StopSound();
	SOMA::StopMusic();
	TEMA::Unload("enemyMelee");
	TEMA::Unload("enemyMeleeBat");
	TEMA::Unload("enemySpider");
	TEMA::Unload("Wood");
	TEMA::Unload("Gate");
	TEMA::Unload("Rock1");
	TEMA::Unload("bg");
	TEMA::Unload("tiles");



	for (map<std::string, GameObject*>::iterator i = m_objects.begin(); i != m_objects.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}
	m_objects.clear();
}

void GameState::Resume() {}
// End GameState

LoseState::LoseState() {}

void LoseState::Enter()
{
	cout << "Entering LoseState..." << endl;

	TEMA::Load("Img/Game Over.png", "gameOver");
	m_objects.emplace(pair<string, GameObject*>("gameOver",
		new LoseStateObjects({ 0, 0, 400,100 }, { 310.0f, 50.0f, 390.0f, 100 })));

	TEMA::Load("Img/RetryButton.png", "retryButton");
	m_objects.emplace(pair<string, GameObject*>("retryButton",
		new GameOverButton({ 0, 0, 451, 150 }, { 410, 450, 200, 50 }, "retryButton")));
}

void LoseState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void LoseState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	State::Render();
}

void LoseState::Exit()
{
	cout << "Exiting LoseState..." << endl;
	TEMA::Unload("gameOver");
	TEMA::Unload("retryButton");
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr; // ;)
	}
}
