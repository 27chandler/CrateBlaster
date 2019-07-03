#include "MenuState.h"
#include "PlayState.h"
#include "PipelineManager.h"
#include "ScreenManager.h"
#include "GameManager.h"

#include <fstream>

MenuState::MenuState(GameState * input_prev_state) : GameState(input_prev_state)
{
}

MenuState::~MenuState()
{
	Text_Texture[0].Unload_All();
}

void MenuState::Load_Scores()
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
				if (line_counter < NUM_OF_HIGHSCORES)
				{
					high_scores[line_counter] = final_num;
				}
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
}

void MenuState::Init()
{
	Text_Texture[1].Load("Assets/Textures/Start.png", "Start");
	Text_Texture[0].Load("Assets/Textures/Quit.png", "Quit");

	Arrow_Texture.Load("Assets/Textures/Arrow.png", "Arrow");
	Highscore_Texture.Load("Assets/Textures/Highscores.png", "Highscores");
	Number_Texture.Load("Assets/Textures/Calibri.png", "Digits");

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

	Load_Scores();

	for (int j = 0; j < NUM_OF_HIGHSCORES; j++)
	{
		for (int i = 0; i < NUM_OF_SCORE_DISPLAYS; i++) // Creates the sprite images to display the high scores
		{
			Score_Display[j][i].Init(ThePipeline::Instance()->GetProgramID());

			Score_Display[j][i].Load_Texture(&Number_Texture);
			Score_Display[j][i].Set_Dimension(50, 50);
			Score_Display[j][i].Set_Texture_Dimension(16, 16);
			Score_Display[j][i].Set_Texture_Cell(1, 1);
			Score_Display[j][i].Set_Pos(glm::vec3(900.0f - (50.0f * (i + 1)), 250.0f - (60.0f * j), 0.0f));

			Score_Display[j][i].Is_Animated() = 0;

			std::string score_string = std::to_string(high_scores[j]);
			int count_back = 1 + i;
			if (count_back > int(score_string.length()))
			{
				Score_Display[j][i].Set_Texture_Cell(0, 3);
			}
			else
			{
				int single_num = score_string[score_string.length() - (1 + i)] - 48;
				Score_Display[j][i].Set_Texture_Cell(GLfloat(single_num), GLfloat(3));
			}
		}
	}


	arrow_pos = glm::vec3(20.0f, 100.0f, 0.0f);

	Arrow.Init(ThePipeline::Instance()->GetProgramID());
	Arrow.Load_Texture(&Arrow_Texture);
	Arrow.Set_Dimension(75, 75);
	Arrow.Set_Texture_Dimension(1, 1);
	Arrow.Set_Texture_Cell(0, 0);
	Arrow.Set_Pos(arrow_pos);

	Arrow.Is_Animated() = 0;

	Highscore_Indicator.Init(ThePipeline::Instance()->GetProgramID());
	Highscore_Indicator.Load_Texture(&Highscore_Texture);
	Highscore_Indicator.Set_Dimension(250, 300);
	Highscore_Indicator.Set_Texture_Dimension(1, 1);
	Highscore_Indicator.Set_Texture_Cell(0, 0);
	Highscore_Indicator.Set_Pos(glm::vec3(880.0f - (50.0f * (NUM_OF_SCORE_DISPLAYS)), 300.0f, 0.0f));

	Highscore_Indicator.Is_Animated() = 0;



	MyCamera.Init(ThePipeline::Instance()->GetProgramID());
	TheBuffer::Instance()->Initialize(ThePipeline::Instance()->GetProgramID());
}

void MenuState::Update()
{
	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		Option[i].Update();
	}

	for (int j = 0; j < NUM_OF_HIGHSCORES; j++)
	{
		for (int i = 0; i < NUM_OF_SCORE_DISPLAYS; i++)
		{
			Score_Display[j][i].Update();
		}
	}


	Arrow.Update();
	Highscore_Indicator.Update();

	bool is_selected = 0;

	if ((Input::Instance()->Get_Key_Array()[InputManager::KEY_W]) && (!iskeydown))
	{
		selection += 1;
		iskeydown = true;
	}

	if ((Input::Instance()->Get_Key_Array()[InputManager::KEY_S]) && (!iskeydown))
	{

		selection -= 1;
		iskeydown = true;
	}

	if ((Input::Instance()->Get_Key_Array()[InputManager::KEY_RETURN]) && (!iskeydown))
	{
		is_selected = 1;
		iskeydown = true;
	}

	iskeydown = ((Input::Instance()->Get_Key_Array()[InputManager::KEY_W]) || (Input::Instance()->Get_Key_Array()[InputManager::KEY_S]));

	if (selection < 0)
	{
		selection = NUM_OF_OPTIONS - 1;
	}
	else if (selection > NUM_OF_OPTIONS - 1)
	{
		selection = 0;
	}

	Arrow.Set_Pos(glm::vec3(20.0f, 100.0f + (selection * 100.0f), 0.0f));

	if (is_selected)
	{
		switch (selection)
		{
			case START:
			{
				is_active = 0;
				is_alive = 0;
				TheGame::Instance()->Change_State(new PlayState(this));
				break;
			}
			case QUIT:
			{
				is_active = 0;
				is_alive = 0;
				break;
			}
		}
	}

}

void MenuState::Render()
{
	MyCamera.SendCamera();
	TheBuffer::Instance()->Set_Draw_Type(0);

	MyCamera.Set_2D_Mode();
	TheScreen::Instance()->Set_2D_Screen();

	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		Option[i].Render();
	}

	for (int j = 0; j < NUM_OF_HIGHSCORES; j++)
	{
		for (int i = 0; i < NUM_OF_SCORE_DISPLAYS; i++)
		{
			Score_Display[j][i].Render();
		}
	}

	Arrow.Render();
	Highscore_Indicator.Render();
}


