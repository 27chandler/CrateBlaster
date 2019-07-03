#include "DeathState.h"
#include "MenuState.h"
#include "PipelineManager.h"
#include "ScreenManager.h"
#include "GameManager.h"

#include <fstream>



DeathState::DeathState(GameState * input_prev_state , int input_final_score) : GameState(input_prev_state)
{
	final_score = input_final_score;
}


DeathState::~DeathState()
{
	Text_Texture[0].Unload_All();
}

void DeathState::Init()
{

	Text_Texture[1].Load("Assets/Textures/Instructions.png", "Instruct");
	Text_Texture[0].Load("Assets/Textures/Died.png", "Death");

	New_Highscore_Texture.Load("Assets/Textures/NewHS.png", "HS_Alert");

	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		Option[i].Init(ThePipeline::Instance()->GetProgramID());
		Option[i].Load_Texture(&Text_Texture[i]);
		Option[i].Set_Dimension(250, 75);
		Option[i].Set_Texture_Dimension(1, 1);
		Option[i].Set_Texture_Cell(0, 0);
		Option[i].Set_Pos(glm::vec3(100.0f, 100.0f + (i * 100.0f), 0.0f));

		Option[i].Is_Animated() = 0;
	}



	Highscore_Alert.Init(ThePipeline::Instance()->GetProgramID());
	Highscore_Alert.Load_Texture(&New_Highscore_Texture);
	Highscore_Alert.Set_Dimension(250, 75);
	Highscore_Alert.Set_Texture_Dimension(1, 1);
	Highscore_Alert.Set_Texture_Cell(0, 0);
	Highscore_Alert.Set_Pos(glm::vec3(TheScreen::Instance()->Get_Screen_Width() - 260.0f, 50.0f, 0.0f));

	Highscore_Alert.Is_Animated() = 0;

	MyCamera.Init(ThePipeline::Instance()->GetProgramID());

	Load_Scores();
}

void DeathState::Load_Scores()
{
	std::fstream file;

	file.open(SCORES_DIR);

	if (!file)
	{
		std::cout << SCORES_DIR << ": File could not be opened!" << std::endl;
	}
	else
	{
		int final_num = 0;
		int line_counter = 0;
		int digit_counter = 0;

		while (!file.eof())
		{
			char input_char = file.get();
			if ((input_char == '\n') || (input_char == -1))
			{
				high_scores[line_counter] = final_num;
				final_num = 0;
				line_counter++;
				digit_counter = 0;
			}
			else
			{
				if (final_num != 0)
				{
					final_num *= 10;
				}
				int retrieved_num = int(input_char - 48);
				final_num += retrieved_num;
			}
		}
	}

	file.close();

	// Sorting section
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (high_scores[i] < high_scores[i + 1])
			{
				int temp_score_var = high_scores[i];
				high_scores[i] = high_scores[i + 1];
				high_scores[i + 1] = temp_score_var;
			}
		}
	}
	//
	
	if (final_score > high_scores[4])
	{
		high_scores[4] = final_score;
		is_higher_score = 1;
	}

	if (is_higher_score)
	{
		std::fstream file;

		file.open(SCORES_DIR, std::fstream::out);

		for (int i = 0; i < 5; i++)
		{
			file << high_scores[i] << std::endl;
		}

		file.close();
	}
}

void DeathState::Update()
{
	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		Option[i].Update();
	}

	Highscore_Alert.Update();

	if (Input::Instance()->Get_Key_Array()[InputManager::KEY_SPACE])
	{
		is_active = 0;
		is_alive = 0;
		TheGame::Instance()->Change_State(new MenuState(this));
	}
}

void DeathState::Render()
{
	MyCamera.SendCamera();
	TheBuffer::Instance()->Set_Draw_Type(0);

	MyCamera.Set_2D_Mode();
	TheScreen::Instance()->Set_2D_Screen();

	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		Option[i].Render();
	}

	if (is_higher_score)
	{
		Highscore_Alert.Render();
	}
}


