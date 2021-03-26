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
GameState::GameState() {}

void GameState::Enter() // Used for initialization.
{
	m_level = new TiledLevel(50, 200, 32, 32, "Dat/Tiledata.txt", "Dat/Level1.txt", "tiles");
	TEMA::Load("Img/Tiles.png", "tiles");
	TEMA::Load("Img/GolemTesting.png", "enemyMelee");
	m_objects.push_back(pair<string, GameObject*>("enemyMelee",
		new EnemyMelee({ 0, 0, 1500, 1500 }, { 462.0f, 334.0f, 50.0f, 50.0f })));


}

void GameState::Update()
{
	for (auto const& i : m_objects)
	{
		m_level->Update();
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
	if (dynamic_cast<GameState*>(STMA::GetStates().back())) // Check to see if current state is of type GameState
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
	for (auto& i : m_objects)
	{
		delete i.second;
		i.second = nullptr; // ;)
	}
}

void GameState::Resume() {}
// End GameState