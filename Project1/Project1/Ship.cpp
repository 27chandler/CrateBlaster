#include "Ship.h"
#include "InputManager.h"
#include "PipelineManager.h"

#include <math.h>



Ship::Ship(float input_arena_size)
{
	ARENA_SIZE = input_arena_size;

	for (int i = 0; i < NUM_OF_MISSILES; i++) // Initialises all the missiles
	{
		missile_array[i].Init(ThePipeline::Instance()->GetProgramID());
		missile_array[i].Set_Scale(glm::vec3(0.1f));
		missile_array[i].Set_Null_Pos();
	}

	// Init for the audio data
	Shoot_Sound.Set_Audio_Data("SHOOT", AudioManager::SFX);
	Shoot_Sound.Set_Volume(1);

	Powerup_Sound.Set_Audio_Data("POWERUP", AudioManager::SFX);
	Powerup_Sound.Set_Volume(1);
	//

	rot = glm::vec3(0.0f, 0.0f, 0.0f); // yaw, pitch, roll
	is_lit = 1;
	is_textured = 1;

	id = "Ship";

	obj_material.Set_Ambient(glm::vec3(1.0f, 1.0f, 1.0f));
	obj_material.Set_Diffuse(glm::vec3(1.0f, 1.0f, 1.0f));
	obj_material.Set_Specular(glm::vec3(1.0f, 1.0f, 1.0f));
	obj_material.Set_Shininess(32.0f);

	//-----------------------------------------

	//------------------------
	vertices.push_back(-0.5f); //x
	vertices.push_back(0.5f); //y
	vertices.push_back(0.5f); //z
	vertices.push_back(0.5f); //x2
	vertices.push_back(0.5f); //y2
	vertices.push_back(0.5f); //z2
							  //------------------------
							  //------------------------
	vertices.push_back(0.5f); // Back
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(0.5f);
	//------------------------
	//------------------------
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	//------------------------
	//------------------------
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(-0.5f);
	vertices.push_back(0.5f);
	//------------------------

	for (int i = 0; i < 4; i++) //
	{
		normals.push_back(0.0f);
		normals.push_back(0.0f);
		normals.push_back(1.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(0.0f);
		normals.push_back(0.0f);
		normals.push_back(-1.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(-1.0f);
		normals.push_back(0.0f);
		normals.push_back(0.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(1.0f);
		normals.push_back(0.0f);
		normals.push_back(0.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(0.0f);
		normals.push_back(1.0f);
		normals.push_back(0.0f);
	}

	for (int i = 0; i < 4; i++)
	{
		normals.push_back(0.0f);
		normals.push_back(-1.0f);
		normals.push_back(0.0f);
	}

	for (int i = 0; i < 24; i++)
	{
		colours.push_back(1.0f);
		colours.push_back(0.0f);
		colours.push_back(0.0f);
	}

	for (int i = 0; i < 6; i++)
	{
		uvs.push_back(0.0f);
		uvs.push_back(0.0f);
		uvs.push_back(1.0f);
		uvs.push_back(0.0f);
		uvs.push_back(1.0f);
		uvs.push_back(1.0f);
		uvs.push_back(0.0f);
		uvs.push_back(1.0f);
	}

	for (int i = 0; i < 6; i++)
	{
		indices.push_back(0 + (i * 4));
		indices.push_back(1 + (i * 4));
		indices.push_back(3 + (i * 4));
		indices.push_back(3 + (i * 4));
		indices.push_back(1 + (i * 4));
		indices.push_back(2 + (i * 4));
	}
}


Ship::~Ship()
{

}

void Ship::Update()
{
	Check_If_Out_Of_Bounds();
	float rotation_angle_yaw = 0.0f;
	float rotation_angle_tilt = 0.0f;
	float rotation_angle_roll = 0.0f;
	float forward_change = 0.0f;
	glm::mat4 rot_mat_per_frame = glm::mat4(1.0f);

	// Manages the inputted controls and the intended direction of travel
	if (Input::Instance()->Get_Key_Array()[controls_array[R_YAW]] == 1) // Right
	{
		rotation_angle_yaw = -SHIP_TURN_SPEED;
	}
	if (Input::Instance()->Get_Key_Array()[controls_array[L_YAW]] == 1) // Left
	{
		rotation_angle_yaw = SHIP_TURN_SPEED;
	}
	if (Input::Instance()->Get_Key_Array()[controls_array[ACCEL]] == 1) // Up
	{
		forward_change = SHIP_ACCELERATION;
		speed += forward_change;
	}
	if ((Input::Instance()->Get_Key_Array()[controls_array[DECEL]] == 1) && (speed > MIN_SPEED))  // Down
	{
		forward_change = -SHIP_ACCELERATION;
		speed += forward_change;
	}
	if (Input::Instance()->Get_Key_Array()[controls_array[U_TILT]] == 1) // W
	{
		rotation_angle_tilt = -SHIP_TURN_SPEED;
	}
	if (Input::Instance()->Get_Key_Array()[controls_array[D_TILT]] == 1) // S
	{
		rotation_angle_tilt = SHIP_TURN_SPEED;
	}
	if (Input::Instance()->Get_Key_Array()[controls_array[L_ROLL]] == 1) // Q
	{
		rotation_angle_roll = -SHIP_TURN_SPEED;
	}
	if (Input::Instance()->Get_Key_Array()[controls_array[R_ROLL]] == 1) // E
	{
		rotation_angle_roll = SHIP_TURN_SPEED;
	}
	if (Input::Instance()->Get_Key_Array()[controls_array[SHOOT]] == 1) // Shoot
	{
 		if (shoot_timer > SHOOT_DELAY)
		{
			// Runs when the player intends to shoot
			Shoot_Sound.Stop();
			Shoot_Sound.Play();
 			missile_array[missile_rotation_num].Shoot(pos_vec - up_vec, momentum_vec);
			shoot_timer = 0;

			// Rotates the missile number so the next missile is fired
			missile_rotation_num += 1;
			if (missile_rotation_num >= NUM_OF_MISSILES)
			{
				missile_rotation_num = 0;
			}
		}
	}
	shoot_timer += 1;

	if ((boost_timer < BOOST_TIME) && (is_boost_enabled))
	{
		boost_timer += 1;
		forward_change = BOOST_SPEED;
		speed += forward_change;
	}
	else if ((boost_timer >= BOOST_TIME) && (is_boost_enabled))
	{
		is_boost_enabled = 0;
	}



	for (int i = 0; i < NUM_OF_MISSILES; i++) // Updates all missiles
	{
		missile_array[i].Update();
	}

	// Sets a rotation matrix for the yaw, pitch and roll for that frame
	rot_mat_per_frame = glm::rotate(rot_mat_per_frame, glm::radians(rotation_angle_yaw), up_vec);
	rot_mat_per_frame = glm::rotate(rot_mat_per_frame, glm::radians(rotation_angle_tilt), right_vec);
	rot_mat_per_frame = glm::rotate(rot_mat_per_frame, glm::radians(rotation_angle_roll), forward_vec);

	// Rotates the momentum, forward, right and up vectors to be the correct directions
	momentum_vec = glm::vec3(rot_mat_per_frame * glm::vec4(momentum_vec, 1.0f));
	forward_vec = glm::vec3(rot_mat_per_frame * glm::vec4(forward_vec, 1.0f));
	right_vec = glm::vec3(rot_mat_per_frame * glm::vec4(right_vec, 1.0f));
	up_vec = glm::vec3(rot_mat_per_frame * glm::vec4(up_vec, 1.0f));

	momentum_vec = (momentum_vec + (forward_vec * forward_change));
	pos_vec += (glm::vec3(momentum_vec.x, momentum_vec.y, momentum_vec.z));
}

void Ship::Render_Missiles()
{
	for (int i = 0; i < NUM_OF_MISSILES; i++)
	{
		missile_array[i].Render();
	}
}

void Ship::Check_If_Out_Of_Bounds() // Checks if the player's ship has left the play area
{
	if ((pos_vec.x > ARENA_SIZE) || (pos_vec.x < -ARENA_SIZE))
	{
		is_out_of_bounds = 1;
	}

	if ((pos_vec.y > ARENA_SIZE) || (pos_vec.y < -ARENA_SIZE))
	{
		is_out_of_bounds = 1;
	}

	if ((pos_vec.z > ARENA_SIZE) || (pos_vec.z < -ARENA_SIZE))
	{
		is_out_of_bounds = 1;
	}
}

void Ship::Enable_Powerup(int input_powerup)
{
	switch (input_powerup)
	{
		case NONE:
		{
			is_boost_enabled = 0;
			break;
		}
		case BOOST:
		{
			is_boost_enabled = 1;
			boost_timer = 0;
			Powerup_Sound.Stop();
			Powerup_Sound.Play();
			break;
		}
	}

}

void Ship::Set_Controls(int input_accelerate, int i_decellerate, int input_yaw_left, 
	int input_yaw_right, int input_tilt_up, int input_tilt_down, int input_roll_left, 
	int input_roll_right, int input_shoot) // Sets the controls so that they can be changed from ingame if needed
{
	controls_array[ACCEL] = input_accelerate;
	controls_array[DECEL] = i_decellerate;
	controls_array[L_YAW] = input_yaw_left;
	controls_array[R_YAW] = input_yaw_right;
	controls_array[U_TILT] = input_tilt_up;
	controls_array[D_TILT] = input_tilt_down;
	controls_array[L_ROLL] = input_roll_left;
	controls_array[R_ROLL] = input_roll_right;
	controls_array[SHOOT] = input_shoot;

}