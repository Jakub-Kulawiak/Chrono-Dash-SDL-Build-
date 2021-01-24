#include "Engine.h"
#include "SDL_image.h"


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
					m_testBackground = IMG_LoadTexture(m_pRenderer, "Test_ground.png");
				
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
	m_ground.SetRekts({ 0,0,600, 385 }, { 0, 0, 1024, 600 });
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
	
}

void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 20, 200, 255, 255);
	SDL_RenderClear(m_pRenderer);
	
	SDL_RenderCopy(m_pRenderer, m_testBackground , m_ground.GetRectSrc(), m_ground.GetRectDst());



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
	SDL_DestroyTexture(m_testBackground);
	Mix_CloseAudio();
	Mix_Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	IMG_Quit();
	SDL_Quit();
}


