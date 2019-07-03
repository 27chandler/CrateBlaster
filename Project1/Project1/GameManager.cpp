#include "GameManager.h"
#include "AudioManager.h"
#include "ScreenManager.h"
#include "PipelineManager.h"
#include "InputManager.h"

#include "MenuState.h"

#include <time.h>
#include <SDL.h>
#include <glew.h>
#include <glm.hpp>

void GameManager::Init()
{
	srand(int(time(time_t(NULL))));

	TheAudio::Instance()->Init();

	TheScreen::Instance()->Init(4, 0, "The Game", window_width, window_height, true, true, true);
	TheScreen::Instance()->ErrorCheck();
	TheScreen::Instance()->EnableZBuffer();

	// init the shaders
	ThePipeline::Instance()->CreateShaders();
	ThePipeline::Instance()->CreateProgram();
	ThePipeline::Instance()->CompileShader("Main.frag", ThePipeline::Instance()->GetFragID());
	ThePipeline::Instance()->CompileShader("Main.vert", ThePipeline::Instance()->GetVertID());
	ThePipeline::Instance()->AttachShaders();
	ThePipeline::Instance()->LinkProgram();

	TheScreen::Instance()->Send_Program_ID(ThePipeline::Instance()->GetProgramID());
	TheScreen::Instance()->Set_3D_Screen();

	TheScreen::Instance()->Set_FullScreen_Mode(true);

	SDL_SetRelativeMouseMode(SDL_TRUE);

	Add_State(new MenuState(nullptr));
}

void GameManager::Shutdown()
{


	//Destroy the window and stuff (shutting down)
	TheBuffer::Instance()->DestroyBuffers();

	TheScreen::Instance()->Shutdown();

	ThePipeline::Instance()->DetachShaders();
	ThePipeline::Instance()->DestroyProgram();
	ThePipeline::Instance()->DestroyShaders();

	TheAudio::Instance()->Shutdown();
}

void GameManager::Update()
{
	float start_time = float(SDL_GetTicks());
	float current_time = float(SDL_GetTicks());
	float target_milliseonds = (1 / target_fps)*1000.0f;

	while ((!Input::Instance()->Game_Ended()) && (!is_game_ended )) // Main game loop
	{
		while (current_time - start_time > target_milliseonds)
		{
			// Start millisecond timer
			start_time = float(SDL_GetTicks());

			Input::Instance()->Update();
			TheAudio::Instance()->Update();
			TheScreen::Instance()->ClearScreen();
			TheScreen::Instance()->View(0, 0, 1024, 768);

			if (Input::Instance()->Game_Ended())
			{
				is_game_ended = 1;
			}

			if (!is_game_ended)
			{
				if (state_machine_deque.front()->Get_Is_Inited() == 0)
				{
					// Init state
					state_machine_deque.front()->Init();
					state_machine_deque.front()->Set_Is_Inited(1);
				}

				if (state_machine_deque.front()->Get_Is_Active() == 1)
				{
					state_machine_deque.front()->Update();
					state_machine_deque.front()->Render();
				}

				if (state_machine_deque.front()->Get_Is_Alive() == 0)
				{
					Remove_State();
				}
			}



			if (state_machine_deque.empty())
			{
				is_game_ended = 1;
			}

			TheBuffer::Instance()->Clear_Depth_Buffer(); // Clear depth buffer

			TheScreen::Instance()->SwapBuffer(); //swap buffers
			current_time = float(SDL_GetTicks());
		}
		current_time = float(SDL_GetTicks());
	}

	if (!state_machine_deque.empty())
	{
		Remove_State();
	}
}

void GameManager::Add_State(GameState * i_state)
{
	state_machine_deque.push_front(i_state);
}

void GameManager::Change_State(GameState * i_state)
{
	state_machine_deque.push_back(i_state);
}

void GameManager::Remove_State()
{
	delete state_machine_deque.front();
	state_machine_deque.pop_front();
}
