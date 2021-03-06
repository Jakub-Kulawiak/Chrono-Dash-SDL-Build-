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

void State::Resume(){}

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
TitleState::TitleState(){}

void TitleState::Enter()
{
	TEMA::Load("Img/PholderButton.png", "play");
	TEMA::Load("Img/Thing.png", "bg");
	TEMA::Load("Img/PholderTitle.png", "title");
	m_objects.push_back(pair<string, GameObject*>("bg",
		new Image({ 0, 0, 1015, 768 }, { 0, 0, 1024, 768 }, "bg")));
	m_objects.push_back(pair<string, GameObject*>("play",
		new PlayButton({ 0, 0, 410, 100 }, { 412, 700, 200, 50 }, "play")));

	m_objects.push_back(pair<string, GameObject*>("title",
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
GameState::GameState(){}

void GameState::Enter() // Used for initialization.
{
	// Cave Music
	SOMA::Load("Aud/Cave.wav", "Cave", SOUND_MUSIC);
	SOMA::PlayMusic("Cave");

	// Sound Effects
	SOMA::Load("Aud/Jump.wav", "Jump", SOUND_SFX);
	SOMA::Load("Aud/Shoot.wav", "Shoot", SOUND_SFX);
	SOMA::Load("Aud/Hit.wav", "Hit", SOUND_SFX);
	SOMA::Load("Aud/PlayerDead.wav", "PlayerDead", SOUND_SFX);

	//Backgrounds
	TEMA::Load("Img/background1.png", "bg");
	m_objects.push_back(pair<string, GameObject*>("bg",
		new Image({ 0, 0, 960, 480 }, { 0, 0, 1024, 768 }, "bg")));
	m_objects.push_back(pair<string, GameObject*>("bg",
		new Image({ 0, 0, 960, 480 }, { 1024, 0, 1024, 768 }, "bg")));

	// Health Bar
	TEMA::Load("Img/HealthBar.png", "HealthBar");
	m_objects.push_back(pair<string, GameObject*>("HealthBar",
		m_healthBar = new HealthBar({ 0, 0, 32, 32 }, { 0, 0, 120, 120 })));

	//Rock Platforms
	TEMA::Load("Img/props1.png", "Rock1");
	m_objects.push_back(pair<string, GameObject*>("Rock1",
		new Image({ 0, 0, 158, 53 }, { 0, 720, 200, 50 }, "Rock1")));
	m_objects.push_back(pair<string, GameObject*>("Rock1",
		new Image({ 0, 0, 158, 53 }, { 280, 720, 200, 50 }, "Rock1")));
	m_objects.push_back(pair<string, GameObject*>("Rock1",
		new Image({ 0, 0, 158, 53 }, { 580, 720, 200, 50 }, "Rock1")));

	//Wood Platforms
	TEMA::Load("Img/Wood.png", "Wood");
	m_objects.push_back(pair<string, GameObject*>("Wood",
		new Image({ 0, 0, 168, 25 }, { 0, 450, 200, 30 }, "Wood")));
	m_objects.push_back(pair<string, GameObject*>("Wood",
		new Image({ 0, 0, 168, 25 }, { 820, 625, 200, 30 }, "Wood")));
	m_objects.push_back(pair<string, GameObject*>("Wood",
		new Image({ 0, 0, 168, 25 }, { 220, 600, 80, 30 }, "Wood")));
	m_objects.push_back(pair<string, GameObject*>("Wood",
		new Image({ 0, 0, 168, 25 }, { 480, 600, 80, 30 }, "Wood")));
	m_objects.push_back(pair<string, GameObject*>("Wood",
		new Image({ 0, 0, 168, 25 }, { 820, 350, 200, 30 }, "Wood")));
	m_objects.push_back(pair<string, GameObject*>("Wood",
		new Image({ 0, 0, 168, 25 }, { 620, 500, 200, 30 }, "Wood")));

	//Gate object
	TEMA::Load("Img/Gate.png", "Gate");
	m_objects.push_back(pair<string, GameObject*>("Gate",
		new Image({ 0, 0, 48, 65 }, { 940, 280, 70, 70 }, "Gate")));

	//Enemy Objects
	//Golem
	TEMA::Load("Img/Mini Golem Sprite Sheet.png", "enemyMelee");
	m_objects.push_back(pair<string, GameObject*>("enemyMelee",
		new EnemyMelee({ 0, 0, 35,35}, { 630.0f, 460.0f, 90.0f, 90.0f })));
	//Bat
	TEMA::Load("Img/Bat.png", "enemyMeleeBat");
	m_objects.push_back(pair<string, GameObject*>("enemyMeleeBat",
		new EnemyMeleeBat({ 0, 0, 16,16 }, { 120.0f, 370.0f, 80.0f, 80.0f })));
	//Spider
	TEMA::Load("Img/Spider Sprite Sheet.png", "enemySpider");
	m_objects.push_back(pair<string, GameObject*>("enemySpider",
		new EnemySpider({ 0, 0, 33,41 }, { 245.0f, 630.0f, 120.0f, 120.0f })));

	//Player Object
	TEMA::Load("Img/Player.png", "Player");
	TEMA::Load("Img/Bullet.png", "Bullet");
	m_objects.push_back(pair<string, GameObject*>("Player",
		m_pPlayer = new PlatformPlayer({ 0, 0, 577, 529 }, { 300.0f, 450.0f, 100.0f, 100.0f })));
}

void GameState::Update()
{
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}

	if (COMA::AABBCheck(m_pPlayer->GetRect(), GetGo("enemyMelee")->GetRect()) || COMA::AABBCheck(m_pPlayer->GetRect(), GetGo("enemyMeleeBat")->GetRect())
		|| COMA::AABBCheck(m_pPlayer->GetRect(), GetGo("enemySpider")->GetRect()))
	{
		SOMA::PlaySound("Hit");
		m_pPlayer->LoseHealth();
		m_healthBar->LoseHealth();

			if (m_pPlayer->IsFacingLeft())
			{
				m_pPlayer->GetDst()->x += 300;
			}
			else
			{
				m_pPlayer->GetDst()->x -= 300;
			}
	}
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	for (auto const& i : m_objects)
		i.second->Render();
	if ( dynamic_cast<GameState*>(STMA::GetStates().back()) ) // Check to see if current state is of type GameState
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
	TEMA::Unload("HealthBar");
	
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr; // ;)
	}
}

void GameState::Resume(){}
// End GameState

LoseState::LoseState(){}

void LoseState::Enter()
{
	cout << "Entering LoseState..." << endl;

	TEMA::Load("Img/Game Over.png", "gameOver");
	m_objects.push_back(pair<string, GameObject*>("gameOver",
		new LoseStateObjects({ 0, 0, 400,100 }, { 310.0f, 50.0f, 390.0f, 100 })));
	
	TEMA::Load("Img/RetryButton.png", "retryButton");
	m_objects.push_back(pair<string, GameObject*>("retryButton",
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
