#include "Missile.h"



Missile::Missile()
{
	missile_light.Init();

	// Sets up a random colour for the missile
	float rand_r = float(rand() % 2);
	float rand_g = float(rand() % 2);
	float rand_b = float(rand() % 2);

	missile_light.Set_Ambient(glm::vec3(0.0f, 0.0f, 0.0f));
	missile_light.Set_Diffuse(glm::vec3(0.0f, 0.0f, 0.0f));
	missile_light.Set_Specular(glm::vec3(0.0f, 0.0f, 0.0f));
	//

	is_lit = 0;
	is_textured = 0;

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
		colours.push_back(rand_r);
		colours.push_back(rand_g);
		colours.push_back(rand_b);
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


Missile::~Missile()
{
}

void Missile::Update()
{
	pos_vec += momentum_vec;

	scale_mat = glm::mat4(1.0f);
	scale_mat = glm::scale(scale_mat, scale_vec);

	translation = glm::mat4(1.0f);
	translation = glm::translate(translation, pos_vec);

	missile_light.Set_Pos(pos_vec);
	missile_light.Update();
	missile_light.Render();

	Update_Matrix();
}

void Missile::Set_Null_Pos()
{
	pos_vec = glm::vec3(9999.0f, 9999.0f, 9999.0f);
}

void Missile::Shoot(glm::vec3 input_pos, glm::vec3 input_momentum)
{
	// Sends the missile flying in the inputted direction
	// and randomizes the colour of the object and the
	// light it emits
	float rand_r = float(rand() % 2);
	float rand_g = float(rand() % 2);
	float rand_b = float(rand() % 2);

	colours.clear();

	for (int i = 0; i < 24; i++)
	{
		colours.push_back(rand_r);
		colours.push_back(rand_g);
		colours.push_back(rand_b);
	}

	obj_buffer.Set_Colour_Array(&colours);
	obj_buffer.Fill_Buffers();

	missile_light.Set_Diffuse(glm::vec3(rand_r, rand_g, rand_b));
	missile_light.Set_Specular(glm::vec3(rand_r, rand_g, rand_b));


	glm::vec3 shoot_direction = glm::normalize(input_momentum);

	momentum_vec = input_momentum;

	momentum_vec += (shoot_direction * speed_multiplier);
	pos_vec = input_pos;
}
