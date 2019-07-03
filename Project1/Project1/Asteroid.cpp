#include "Asteroid.h"



Asteroid::Asteroid(float input_arena_size)
{
	ARENA_SIZE = input_arena_size;

	float yaw = float((2 -(rand() % 5)) / 100.0f);
	float pitch = float((2 -(rand() % 5)) / 100.0f);
	float roll = float((2 -(rand() % 5)) / 100.0f);

	random_rot = glm::vec3(yaw, pitch, roll);

	is_lit = 1;
	is_textured = 1;
	is_toon = 0;

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

void Asteroid::Update()
{

	float x_momentum = (((rand() % 3) - 1) / 200.0f);
	float y_momentum = (((rand() % 3) - 1) / 200.0f);
	float z_momentum = (((rand() % 3) - 1) / 200.0f);

	// Checks to see if the asteroid has left the play area, if it has, then reverse it's direction
	if ((pos_vec.x > ARENA_SIZE) && (momentum_vec.x > 0))
	{
		momentum_vec = glm::vec3((-momentum_vec.x) + x_momentum, momentum_vec.y + y_momentum, momentum_vec.z + z_momentum);
	}
	else if ((pos_vec.x < -ARENA_SIZE) && (momentum_vec.x < 0))
	{
		momentum_vec = glm::vec3((-momentum_vec.x) + x_momentum, momentum_vec.y + y_momentum, momentum_vec.z + z_momentum);
	}

	if ((pos_vec.y > ARENA_SIZE) && (momentum_vec.y > 0))
	{
		momentum_vec = glm::vec3(momentum_vec.x + x_momentum, (-momentum_vec.y) + y_momentum, momentum_vec.z + z_momentum);
	}
	else if ((pos_vec.y < -ARENA_SIZE) && (momentum_vec.y < 0))
	{
		momentum_vec = glm::vec3(momentum_vec.x + x_momentum, (-momentum_vec.y) + y_momentum, momentum_vec.z + z_momentum);
	}

	if ((pos_vec.z > ARENA_SIZE) && (momentum_vec.z > 0))
	{
		momentum_vec = glm::vec3(momentum_vec.x + x_momentum, momentum_vec.y + y_momentum, (-momentum_vec.z) + z_momentum);
	}
	if ((pos_vec.z < -ARENA_SIZE) && (momentum_vec.z < 0))
	{
		momentum_vec = glm::vec3(momentum_vec.x + x_momentum, momentum_vec.y + y_momentum, (-momentum_vec.z) + z_momentum);
	}
	//

	pos_vec += momentum_vec;

	// Lets it continously rotate each frame
	Set_Rotation(glm::vec3(0.0f, 1.0f, 0.0f), random_rot.x);
	Set_Rotation(glm::vec3(1.0f, 0.0f, 0.0f), random_rot.y);
	Set_Rotation(glm::vec3(0.0f, 0.0f, 1.0f), random_rot.z);
	//

	scale_mat = glm::mat4(1.0f);
	scale_mat = glm::scale(scale_mat, scale_vec);

	translation = glm::mat4(1.0f);
	translation = glm::translate(translation, pos_vec);

	Update_Matrix();
}

bool Asteroid::Check_If_Shot(Missile * input_missile_array, int input_max_missiles) // Returns true if the asteroid has been shot by a missile
{
	for (int i = 0; i < input_max_missiles; i++)
	{
		if (length(pos_vec - input_missile_array[i].Get_Pos()) < collision_distance)
		{
			Shrink_And_Spin();
			return true;
		}
	}
	
	return false;
}

void Asteroid::Shrink_And_Spin()
{
	float yaw = float((2 - (rand() % 5)) / 100.0f);
	float pitch = float((2 - (rand() % 5)) / 100.0f);
	float roll = float((2 - (rand() % 5)) / 100.0f);

	random_rot = glm::vec3(yaw, pitch, roll);

	Set_Scale(glm::vec3(-(scale_vec.x / SHRINK_AMOUNT), -(scale_vec.y / SHRINK_AMOUNT), -(scale_vec.z / SHRINK_AMOUNT)));
	collision_distance = scale_vec.x;
}
