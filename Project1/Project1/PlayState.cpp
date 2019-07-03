#include "PlayState.h"
#include "DeathState.h"

#include <fstream>

#include "ScreenManager.h"
#include "GameManager.h"
#include "AudioManager.h"

#include "Missile.h"
#include <time.h>

#include "Light.h"




PlayState::PlayState(GameState* input_prev_state) : GameState(input_prev_state)
{
}

PlayState::~PlayState()
{
	int counter = 0;
	for (auto it = Objects.begin(); it != Objects.end(); it++) // Destroy all objects
	{
		delete (*it);
	}

	Objects.clear();
	Crate_Texture.Unload_All();
	TheAudio::Instance()->Unload_from_File(AudioManager::SFX, "SHOOT");
	TheAudio::Instance()->Unload_from_File(AudioManager::SFX, "POWERUP");
}


void PlayState::Init()
{
	// Sets up the directional light to keep all the objects lit up
	Light::total_lights = 0;

	Star_Light.Init();
	Star_Light.Set_Pos(glm::vec3((ARENA_SIZE * 2), 0.0f, 0.0f));
	Star_Light.Set_Ambient(glm::vec3(0.4f, 0.4f, 0.4f));
	Star_Light.Set_Diffuse(glm::vec3(0.9f, 0.9f, 0.9f));
	Star_Light.Set_Specular(glm::vec3(0.8f, 0.8f, 0.8f));

	Star_Light.Set_Const(0.01f);
	Star_Light.Set_Lin(0.0001f);
	Star_Light.Set_Quad(0.0001f);
	//

	// Load textures and audio
	Crate_Texture.Load("Assets/Textures/Crate.jpg", "Crate");
	Skybox_Texture.Load("Assets/Textures/Space.png", "Skybox");
	Arena_Border_Texture.Load("Assets/Textures/Box_Grid.png","GRID");
	Number_Texture.Load("Assets/Textures/Calibri.png", "Numbers");
	Boost_Texture.Load("Assets/Textures/Boost.png", "Boost");
	Score_Powerup_Texture.Load("Assets/Textures/Score.png", "Score_Up");
	TheAudio::Instance()->Load_From_File("Assets/Audio/Shoot.wav", AudioManager::SFX, "SHOOT");
	TheAudio::Instance()->Load_From_File("Assets/Audio/Powerup.wav", AudioManager::SFX, "POWERUP");
	TheAudio::Instance()->Load_From_File("Assets/Audio/Explode.wav", AudioManager::SFX, "EXPLOSION");
	//

	// Load skybox
	The_Sky.Init(ThePipeline::Instance()->GetProgramID());
	The_Sky.Load_Texture(&Skybox_Texture);
	The_Sky.Set_Scale(glm::vec3(3000.0f));
	//

	// Load arena border skybox
	Arena_Border.Init(ThePipeline::Instance()->GetProgramID());
	Arena_Border.Load_Texture(&Arena_Border_Texture);
	Arena_Border.Set_Scale(glm::vec3(ARENA_SIZE*2));
	//

	for (int i = 0; i < 8; i++) // Create all the starting asteroids
	{
		Objects.push_back(new Asteroid(ARENA_SIZE));

		Objects.back()->Set_Id("Asteroid");
		Asteroid* asteroid_ptr = dynamic_cast<Asteroid*>(Objects.back());
		asteroid_ptr->Set_Collision_Distance(1.3f);

		float x_momentum = (((rand() % 3) + 1) / 100.0f);
		float y_momentum = (((rand() % 3) + 1) / 100.0f);
		float z_momentum = (((rand() % 3) + 1) / 100.0f);

		asteroid_ptr->Init(ThePipeline::Instance()->GetProgramID());
		asteroid_ptr->Load_Texture(&Crate_Texture);
		asteroid_ptr->Set_Scale(glm::vec3(1.0f));
		asteroid_ptr->Set_Pos(glm::vec3((2.0f * i), (2.0f * (i + 2)), -1.0f));
		asteroid_ptr->Set_Momentum(glm::vec3(x_momentum, y_momentum, z_momentum));
		asteroid_ptr->Update();
	}

	for (int i = 0; i < 1; i++) // Create the player's ship
	{
		Objects.push_back(new Ship(ARENA_SIZE));

		Objects.back()->Set_Id("Ship");

		Ship* ship_ptr = nullptr;
		ship_ptr = dynamic_cast<Ship*>(Objects.back());

		if (ship_ptr == nullptr)
		{
			std::cout << Objects.back()->Get_Id() << " did not bind to pointer!" << std::endl;
		}

		ship_ptr->Set_Controls(
			int(InputManager::KEY_W),
			int(InputManager::KEY_S),
			int(InputManager::KEY_LEFT),
			int(InputManager::KEY_RIGHT),
			int(InputManager::KEY_UP),
			int(InputManager::KEY_DOWN),
			int(InputManager::KEY_Q),
			int(InputManager::KEY_E),
			int(InputManager::KEY_SPACE)
		);

		ship_ptr->Init(ThePipeline::Instance()->GetProgramID());
		ship_ptr->Load_Texture(&Crate_Texture);
		ship_ptr->Set_Scale(glm::vec3(0.2f));
		ship_ptr->Set_Pos(glm::vec3(0.0f, 0.0f, 0.0f));
		ship_ptr->Set_Momentum(glm::vec3(0.0f, 0.0f, 0.0001f));
		ship_ptr->Update();
	}


	for (int i = 0; i < NUM_OF_SCORE_DISPLAYS; i++) // Creates the sprite images to display the score in the corner
	{
		Score_Display[i].Init(ThePipeline::Instance()->GetProgramID());

		Score_Display[i].Load_Texture(&Number_Texture);
		Score_Display[i].Set_Dimension(50, 50);
		Score_Display[i].Set_Texture_Dimension(16, 16);
		Score_Display[i].Set_Texture_Cell(1, 1);
		Score_Display[i].Set_Pos(glm::vec3(TheScreen::Instance()->Get_Screen_Width() - (50.0f * (i + 1)),0.0f, 0.0f));

		Score_Display[i].Is_Animated() = 0;
	}

	Powerup_Display.Init(ThePipeline::Instance()->GetProgramID());

	Powerup_Display.Load_Texture(&Boost_Texture);
	Powerup_Display.Set_Dimension(250, 75);
	Powerup_Display.Set_Texture_Dimension(1, 1);
	Powerup_Display.Set_Texture_Cell(0, 0);
	Powerup_Display.Set_Pos(glm::vec3(10.0f, 10.0f, 0.0f));

	Powerup_Display.Is_Animated() = 0;

	Death_Sound.Set_Audio_Data("EXPLOSION", AudioManager::SFX);
	Death_Sound.Set_Volume(1);

	MyCamera.Init(ThePipeline::Instance()->GetProgramID()); // Initialises the camera
}

void PlayState::Set_Powerup_Display(Texture * input_texture)
{
	Powerup_Display.Load_Texture(input_texture);
}


void PlayState::Update()
{
	Ship* ship_ptr = nullptr;

	for (auto it = Objects.begin(); it != Objects.end(); it++) // Runs through all the objects to update the spaceship
	{
		if ((*it)->Get_Id() == "Ship")
		{
			ship_ptr = dynamic_cast<Ship*>(*it);
			if (ship_ptr->Get_Is_Out_Of_Bounds()) // Checks to see if the spaceship has left the play area
			{
				Death_Sound.Stop();
				Death_Sound.Play();
				is_active = 0;
				is_alive = 0;
				TheGame::Instance()->Change_State(new DeathState(this,score));
			}
		}
	}

	MyCamera.Update();

	if (ship_ptr->Get_Is_Boost_Enabled())
	{
		powerup_type = BOOST;
		Set_Powerup_Display(&Boost_Texture);
	}
	else if (powerup_type == SCORE)
	{

	}
	else
	{
		powerup_type = NONE;
	}

	// Handles creating new asteroids at the edge of the map
	if (rand() % RAND_NEW_ASTEROID_SPAWN == 0)
	{
		Objects.push_back(new Asteroid(ARENA_SIZE));

		Objects.back()->Set_Id("Asteroid");
		Asteroid* asteroid_ptr = dynamic_cast<Asteroid*>(Objects.back());
		asteroid_ptr->Set_Collision_Distance(1.3f);

		float x_momentum = -0.005f;
		float y_momentum = 0.0f;
		float z_momentum = 0.0f;

		asteroid_ptr->Init(ThePipeline::Instance()->GetProgramID());
		asteroid_ptr->Load_Texture(&Crate_Texture);
		asteroid_ptr->Set_Scale(glm::vec3(40.0f));
		asteroid_ptr->Shrink_And_Spin();
		asteroid_ptr->Set_Pos(glm::vec3((- float(ARENA_SIZE + 20.0f)), 0.0f,0.0f));
		asteroid_ptr->Set_Momentum(glm::vec3(x_momentum, y_momentum, z_momentum));
		asteroid_ptr->Update();
	}
	//
	// Updates score display
	for (int i = 0; i < NUM_OF_SCORE_DISPLAYS; i++)
	{
		Score_Display[i].Update();
	}

	Powerup_Display.Update();

	int num_of_missiles = ship_ptr->Get_Num_Of_Missiles();
	bool is_new_asteroid = 0;
	Asteroid* asteroid_to_be_cloned = nullptr;
	// Updates the asteroids, must be done seperately and after the ship loop
	// to ensure the ship_ptr pointer has been set
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		bool is_destroyed = 0;
		if ((*it)->Get_Id() == "Asteroid")
		{
			Asteroid* asteroid_ptr = dynamic_cast<Asteroid*>(*it);
			if (length((*it)->Get_Pos() - ship_ptr->Get_Pos_Front(0.0f, 0.0f, -1.2f)) < asteroid_ptr->Get_Collision_Distance()) // Check if ship collides with asteroid
			{
				if ((*it)->Get_Is_Toon())
				{
					int rand_powerup = (rand() % 2) + 1;
					switch (rand_powerup)
					{
						case BOOST:
						{
							ship_ptr->Enable_Powerup(BOOST);
							(*it)->Set_Is_Alive(0);
							powerup_type = BOOST;
							break;
						}
						case SCORE:
						{
							(*it)->Set_Is_Alive(0);
							score_timer = 0;
							powerup_type = SCORE;
							Powerup_Display.Load_Texture(&Score_Powerup_Texture);
							break;
						}

					}

				}
				else
				{
					Death_Sound.Stop();
					Death_Sound.Play();
					is_active = 0;
					is_alive = 0;
					TheGame::Instance()->Change_State(new DeathState(this,score));
				}

			}

			

			if (asteroid_ptr->Check_If_Shot(ship_ptr->Get_Missile_Array(), ship_ptr->Get_Num_Of_Missiles())) // Checks an asteroid to see if it got shot this frame
			{
				is_new_asteroid = 1;
				asteroid_to_be_cloned = asteroid_ptr;
			}
		}

		(*it)->Update(); // Regular update call
	}

	if ((powerup_type == SCORE) && (score_timer <= POWERUP_SCORE_AMOUNT))
	{
		score_timer++;
		score += 1;
		if (score_timer == POWERUP_SCORE_AMOUNT)
		{
			powerup_type = NONE;
		}
	}

	if (is_new_asteroid) // Is called when a new asteroid is created
	{
		// Calculates how much to score the player by using their speed
		float speed_score_multiplier = 0.0f;
		// These if statements are there to ensure speed_score_multiplier isn't turned into a negative
		if (ship_ptr->Get_Momentum().x > 0)
		{
			speed_score_multiplier += (ship_ptr->Get_Momentum().x * 10);
		}
		else
		{
			speed_score_multiplier -= (ship_ptr->Get_Momentum().x * 10);
		}

		if (ship_ptr->Get_Momentum().y > 0)
		{
			speed_score_multiplier += (ship_ptr->Get_Momentum().y * 10);
		}
		else
		{
			speed_score_multiplier -= (ship_ptr->Get_Momentum().y * 10);
		}

		if (ship_ptr->Get_Momentum().z > 0)
		{
			speed_score_multiplier += (ship_ptr->Get_Momentum().z * 10);
		}
		else
		{
			speed_score_multiplier -= (ship_ptr->Get_Momentum().z * 10);
		}
		//
		score += int(10 * speed_score_multiplier);

		srand(int(time(time_t(NULL))));

		float x_momentum = (((rand() % 3) + 1) / 100.0f);
		float y_momentum = (((rand() % 3) + 1) / 100.0f);
		float z_momentum = (((rand() % 3) + 1) / 100.0f);



		// Standard initialisation of asteroids
		Objects.push_back(new Asteroid(ARENA_SIZE));

		Asteroid* new_asteroid = dynamic_cast<Asteroid*>(Objects.back());

		new_asteroid->Set_Id("Asteroid");

		// This changes the direction the asteroid is moving in, and also it's speed
		asteroid_to_be_cloned->Set_Momentum(glm::vec3(
			new_asteroid->Get_Momentum().x - x_momentum,
			new_asteroid->Get_Momentum().y - y_momentum,
			new_asteroid->Get_Momentum().z - z_momentum));

		x_momentum = (((rand() % 3) + 1) / 100.0f);
		y_momentum = (((rand() % 3) + 1) / 100.0f);
		z_momentum = (((rand() % 3) + 1) / 100.0f);

		new_asteroid->Init(ThePipeline::Instance()->GetProgramID());
		new_asteroid->Load_Texture(&Crate_Texture);
		new_asteroid->Set_Scale(asteroid_to_be_cloned->Get_Scale());
		new_asteroid->Shrink_And_Spin();
		new_asteroid->Set_Pos(asteroid_to_be_cloned->Get_Pos());
		new_asteroid->Set_Momentum(glm::vec3(
			asteroid_to_be_cloned->Get_Momentum().x + x_momentum,
			asteroid_to_be_cloned->Get_Momentum().y + y_momentum,
			asteroid_to_be_cloned->Get_Momentum().z + z_momentum));
		new_asteroid->Update();

		asteroid_to_be_cloned->Shrink_And_Spin();

		// Gets the missile id and sets its position to a location away from the game
		int missile_id = ship_ptr->Get_Missile_Rot_Number() - 1;
		if (missile_id < 0)
		{
			missile_id = ship_ptr->Get_Num_Of_Missiles() - 1;
		}
		ship_ptr->Get_Missile_Array()[missile_id].Set_Null_Pos();

		if (rand() % RAND_POWERUP_CHANCE == 0) // Does a random check to see if an asteroid has been set to contain a powerup
		{
			new_asteroid->Set_Is_Toon(1);
		}
	}

	The_Sky.Update();
	Arena_Border.Update();
	Star_Light.Update();

	for (int i = 0; i < NUM_OF_SCORE_DISPLAYS; i++) // Runs through the updates and places the correct score value into the sprites
	{
		std::string score_string = std::to_string(score);
		int count_back = 1 + i;
		if (count_back > int(score_string.length()))
		{
			Score_Display[i].Set_Texture_Cell(0, 3);
		}
		else
		{
			int single_num = score_string[score_string.length() - (1 + i)] - 48;
			Score_Display[i].Set_Texture_Cell(GLfloat(single_num), GLfloat(3));
		}
	}

	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		if ((*it)->Get_Is_Alive() == 0)
		{
			Objects.erase(it);
			it = Objects.begin();
		}
	}

	// Sets the camera to be in sync with the ship's position and direction
	MyCamera.SetPos(ship_ptr->Get_Pos_Front(0.0f, 0.0f, -1.2f));
	MyCamera.SetDir(ship_ptr->Get_Forward_Vec());
	MyCamera.SetUp(ship_ptr->Get_Up_Vec());
}

void PlayState::Render()
{

	MyCamera.SendCamera();
	MyCamera.Set_3D_Mode();
	TheScreen::Instance()->Set_3D_Screen();
	TheBuffer::Instance()->Set_Draw_Type(0);

	// Skybox
	The_Sky.Render();
	Star_Light.Render();

	// Renders all gameobjects apart from the ship
	// (The ship's model isn't needed to be seen)
	for (auto it = Objects.begin(); it != Objects.end(); it++)
	{
		if ((*it)->Get_Id() == "Ship")
		{

		}
		else
		{
			(*it)->Render();
		}
	}

	Ship* ship_ptr = nullptr;

	for (auto it = Objects.begin(); it != Objects.end(); it++) // Set up the ship pointer
	{
		if ((*it)->Get_Id() == "Ship")
		{
			ship_ptr = dynamic_cast<Ship*>(*it);
		}
	}

	Arena_Border.Render();

	ship_ptr->Render_Missiles(); // Renders the missiles fired from the ship

	// Sets the screen to render in 2D mode for the HUD
	MyCamera.Set_2D_Mode();
	MyCamera.SendCamera();
	TheScreen::Instance()->Set_2D_Screen();
	//
	for (int i = 0; i < NUM_OF_SCORE_DISPLAYS; i++)
	{
		Score_Display[i].Render();
	}

	if (powerup_type != NONE)
	{
		Powerup_Display.Render();
	}


	MyCamera.Set_3D_Mode();
}
