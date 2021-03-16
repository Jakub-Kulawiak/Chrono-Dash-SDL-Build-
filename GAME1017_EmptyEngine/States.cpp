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
	m_level = new TiledLevel(50, 200, 32, 32, "Dat/Tiledata.txt", "Dat/Level1.txt", "tiles");
	TEMA::Load("Img/Tiles.png", "tiles");
	TEMA::Load("Img/Mini Golem Sprite Sheet.png", "enemyMelee");
	m_objects.push_back(pair<string, GameObject*>("enemyMelee",
		new EnemyMelee({ 0, 0, 35,35}, { 630.0f, 460.0f, 90.0f, 90.0f })));

	TEMA::Load("Img/Player.png", "Player");
	TEMA::Load("Img/Bullet.png", "Bullet");
	m_objects.push_back(pair<string, GameObject*>("Player",
		new PlatformPlayer({ 0, 0, 577, 529 }, { 300.0f, 450.0f, 100.0f, 100.0f })));
}

void GameState::Update()
{
	for (auto const& i : m_objects)
	{
		m_level->Update();
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
	for (auto const& i : m_objects)
	{
		i.second->Update();
		if (STMA::StateChanging()) return;
	}
}

void GameState::Render()
{

	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	m_level->Render();
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
