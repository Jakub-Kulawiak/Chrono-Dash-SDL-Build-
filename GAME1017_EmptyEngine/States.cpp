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
<<<<<<< HEAD
#include "EnemyMeleeBat.h"
<<<<<<< Updated upstream
=======
>>>>>>> parent of 985c092 (Added a bat sprite w/golem)


<<<<<<< HEAD
=======
#include "LoseStateObjects.h"
#include <iostream>


>>>>>>> Stashed changes
=======
#include <iostream>
>>>>>>> parent of 985c092 (Added a bat sprite w/golem)
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
	TEMA::Load("Img/Title.png", "title");
	TEMA::Load("Img/button.png", "play");
	TEMA::Load("Img/TitleBack.jpg", "bg");
	SOMA::Load("Aud/Title.mp3", "title", SOUND_MUSIC);
	m_objects.push_back(pair<string, GameObject*>("bg",
		new Image({ 0, 0, 1920, 1200 }, { 0, 0, 1024, 768 }, "bg")));
	m_objects.push_back(pair<string, GameObject*>("title",
		new Image({ 0, 0, 800, 156 }, { 112, 100, 800, 156 }, "title")));
	m_objects.push_back(pair<string, GameObject*>("play",
		new PlayButton({ 0, 0, 400, 100 }, { 412, 384, 200, 50 }, "play")));
	SOMA::AllocateChannels(16);
	SOMA::SetMusicVolume(32);
	SOMA::PlayMusic("title", -1, 2000);
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
	SOMA::Unload("title", SOUND_MUSIC);
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
	TEMA::Load("Img/GolemTesting.png", "enemyMelee");
	m_objects.push_back(pair<string, GameObject*>("enemyMelee",
<<<<<<< Updated upstream
		new EnemyMelee({ 0, 0, 1500, 1500}, { 462.0f, 334.0f, 50.0f, 50.0f })));
<<<<<<< HEAD
	TEMA::Load("Img/BatTesting.png", "enemyMeleeBat");
	m_objects.push_back(pair<string, GameObject*>("enemyMeleeBat",
		new EnemyMeleeBat({ 0, 0, 80, 72 }, { 100.0f, 300.0f, 40.0f, 40.0f })));
=======
		new EnemyMelee({ 0, 0, 35,35}, { 630.0f, 460.0f, 90.0f, 90.0f })));
	TEMA::Load("Img/Bat.png", "enemyMeleeBat");
	m_objects.push_back(pair<string, GameObject*>("enemyMeleeBat",
		new EnemyMeleeBat({ 0, 0, 16,16 }, { 400.0f, 460.0f, 200.0f, 200.0f })));

	TEMA::Load("Img/Player.png", "Player");
	TEMA::Load("Img/Bullet.png", "Bullet");
	m_objects.push_back(pair<string, GameObject*>("Player",
		new PlatformPlayer({ 0, 0, 577, 529 }, { 300.0f, 450.0f, 100.0f, 100.0f })));
>>>>>>> Stashed changes
=======
>>>>>>> parent of 985c092 (Added a bat sprite w/golem)
}

void GameState::Update()
{
	
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
	TEMA::Unload("bg");
	TEMA::Unload("sprites");
	SOMA::StopSound();
	SOMA::StopMusic();
	SOMA::Unload("engines", SOUND_SFX);
	SOMA::Unload("fire", SOUND_SFX);
	SOMA::Unload("explode", SOUND_SFX);
	SOMA::Unload("wings", SOUND_MUSIC);
	TEMA::Unload("enemyMelee");
<<<<<<< HEAD
<<<<<<< Updated upstream
	TEMA::Unload("enemyMelee2");
=======
	TEMA::Unload("enemyMeleeBat");
>>>>>>> Stashed changes
=======
>>>>>>> parent of 985c092 (Added a bat sprite w/golem)
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr; // ;)
	}
}

void GameState::Resume(){}
// End GameState