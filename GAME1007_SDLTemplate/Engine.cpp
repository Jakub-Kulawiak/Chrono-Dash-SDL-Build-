#include "Engine.h"
#include "SDL_image.h"
#include "EndGoal.h"



//testing
int Engine::Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
	cout << "Initializing engine..." << endl;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) // If initialization is okay...
	{
		// Create the SDL window...
		
		m_pWindow = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (m_pWindow != nullptr)
		{
			// Create the SDL renderer...(back buffer)
			
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, NULL);
			if (m_pRenderer != nullptr)
			{
				// Initialize subsystems later...
				if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
				{
					m_testBackground = IMG_LoadTexture(m_pRenderer, "Textures/Test_ground.png");
					m_testPlayer = IMG_LoadTexture(m_pRenderer, "Textures/Idle.png");
					m_endGoalTexture = IMG_LoadTexture(m_pRenderer, "Textures/PortalTest.png");
					
				}
				else return false; // Image initialization failed
				if (Mix_Init(MIX_INIT_MP3) != 0)
				{
					//configured mixer
					Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 2048);
					Mix_AllocateChannels(16);
					//Loads sounds

				}
				else return false;
				
			}
			else return false; // Renderer creation failed.
		}
		else return false; // Window creation failed.
	}
	else return false; // initalization failed.
	m_fps = (Uint32)round(1.0 / (double)FPS * 1000); // Converts FPS into milliseconds, e.g. 16.67
	m_keystates = SDL_GetKeyboardState(nullptr);
	m_ground.SetRekts({ 0,0,600, 385 }, { 0, 500, 1024, 102 });
	m_ground2.SetRekts({ 0,0,600, 385 }, { WIDTH, 500, 1024, 102 });
	m_player.SetRekts({ 0,0,43,53 }, { 250,250, 43,53 });
	m_endGoal.SetRekts({ 0,0,64,122 }, { 2040,380, 64,122 });

	
	cout << "Initialization successful!" << endl;
	m_running = true;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
}

void Engine::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYUP:
				if (event.key.keysym.sym == ' ')
				{
					//spawn bullet

					m_bullets.push_back(new Bullet({ m_player.GetRectDst()->x, m_player.GetRectDst()->y }));
					m_bullets.shrink_to_fit();
					cout << "New bullet vector capacity: " << m_bullets.capacity() << endl;
				}

				if (event.key.keysym.sym == 'w')
				{
					m_player.GetRectDst()->y -= m_jumpForce;
				}

			
		}
	}
}

bool Engine::KeyDown(SDL_Scancode c)
{
	if (m_keystates != nullptr)
	{
		if (m_keystates[c] == 1)
			return true;
	}
	return false;
}

void Engine::Update()
{

	if ((!SDL_HasIntersection(m_player.GetRectDst(), m_ground.GetRectDst())) && (!SDL_HasIntersection(m_player.GetRectDst(), m_ground2.GetRectDst())))
	{
		m_player.GetRectDst()->y += m_gravity;
	}
	
	

	// Hit Detection
	if (SDL_HasIntersection(m_endGoal.GetRectDst(), m_player.GetRectDst()))
	{

		cout << "Level Complete... (or something like that)" << endl;
		m_running = false;
	}


	if (m_ground.GetRectDst()->x <= -m_ground.GetRectDst()->w) // when bg1 is completely off screen
	{
		// teleport back to the start of bg1
		m_ground.GetRectDst()->x = 0;
		m_ground2.GetRectDst()->x = WIDTH;
	}

	//player movement
	
	if (KeyDown(SDL_SCANCODE_A) && m_player.GetRectDst()->x > 400)
	{
		m_player.GetRectDst()->x -= m_speed;

	}
	else if (KeyDown(SDL_SCANCODE_D) && m_player.GetRectDst()->x < 600)
	{
		m_player.GetRectDst()->x += m_speed;

	}
	if (m_player.GetRectDst()->x > 600 && (KeyDown(SDL_SCANCODE_D)))
	{
		m_endGoal.EndGoal::Update();
		m_ground.GetRectDst()->x -= m_speed / 2;
		m_ground2.GetRectDst()->x -= m_speed / 2;
	}
	if (m_player.GetRectDst()->x < 400 && (KeyDown(SDL_SCANCODE_A)))
	{
		m_ground.GetRectDst()->x += m_speed / 2;
		m_ground2.GetRectDst()->x += m_speed / 2;
	}

	for (unsigned i = 0; i < m_bullets.size(); i++)  // size is filled num of elements
	{
		m_bullets[i]->Update();  // long way: (*bill).Update() 
	}
	// check bullets are onscreen
	for (unsigned i = 0; i < m_bullets.size(); i++)
	{
		if (m_bullets[i]->GetRekt()->x >= 1032)
		{
			delete m_bullets[i]; // flag for relocation
			m_bullets[i] = nullptr; // rangle your dangle
			m_bullets.erase(m_bullets.begin() + i);
			m_bullets.shrink_to_fit();
			break;
		}
	}

}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 20, 200, 255, 255);
	SDL_RenderClear(m_pRenderer);
	
	SDL_RenderCopy(m_pRenderer, m_testBackground , m_ground.GetRectSrc(), m_ground.GetRectDst());
	SDL_RenderCopy(m_pRenderer, m_testBackground, m_ground2.GetRectSrc(), m_ground2.GetRectDst());
	SDL_RenderCopy(m_pRenderer, m_endGoalTexture, m_endGoal.GetRectSrc(), m_endGoal.GetRectDst());
	SDL_RenderCopy(m_pRenderer, m_testPlayer, m_player.GetRectSrc(), m_player.GetRectDst());
	
	for (unsigned i = 0; i < m_bullets.size(); i++)  // size is filled num of elements
	{
		m_bullets[i]->Render(m_pRenderer);
	}

	SDL_RenderPresent(m_pRenderer); // Flip buffers - send data to window.
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start; // 1055 - 1050 = 5ms
	if (m_delta < m_fps)
		SDL_Delay(m_fps - m_delta);

}

int Engine::Run()
{
	if (m_running == true)
	{
		return 1;
	}
	// Start and run the "engine"
	if (Init("Chrono Dash Build -1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL) == false)
	{
		return 2;
	}
	// We passed our initial checks, start the loop!
	while (m_running == true)
	{

		Wake();
		HandleEvents(); // Input
		Update();       // Processing
		Render();       // Output
		if (m_running == true)
			Sleep();
	}
	Clean();
	return 0;
}


void Engine::Clean()
{
	cout << "Cleaning engine..." << endl;

	for (unsigned i = 0; i < m_bullets.size(); i++)
	{
		delete m_bullets[i]; // flag for relocation
		m_bullets[i] = nullptr; // rangle your dangle
	}
	m_bullets.clear(); // wipe out
	m_bullets.shrink_to_fit(); // reduces capacity to size
	
	SDL_DestroyTexture(m_testBackground);
	SDL_DestroyTexture(m_testPlayer);
	SDL_DestroyTexture(m_endGoalTexture);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}


