#include "GameObject.h"

#include <gtc/matrix_transform.hpp>

GameObject::~GameObject()
{

}

void GameObject::Init(GLuint shaderProgID)
{
	momentum_vec = glm::vec3(0.0f, 0.0f, 0.0f);

	obj_buffer.Init_Arrays();
	obj_material.Init();


	obj_buffer.Set_Colour_Array(&colours);
	obj_buffer.Set_Indices_Array(&indices);
	obj_buffer.Set_Normal_Array(&normals);
	obj_buffer.Set_Uv_Array(&uvs);
	obj_buffer.Set_Vert_Array(&vertices);

	obj_buffer.Set_Model_Ptr(&model);

	obj_buffer.Fill_Buffers();
}

void GameObject::Load_Texture(Texture * texture_input)
{
	m_texture = texture_input;
}


void GameObject::Set_Pos(glm::vec3 input_pos)
{
	pos_vec += input_pos;
}

void GameObject::Set_Scale(glm::vec3 input_scale)
{
	scale_vec += input_scale;
}

void GameObject::Set_Rotation(glm::vec3 axis_input, float angle)
{
	rotation_mat = glm::rotate(rotation_mat,angle, axis_input);
	rot += (axis_input * angle);
}

void GameObject::Render()
{
	// If a model has been set, render that, otherwise, render the default object
	if (model_ptr == nullptr)
	{
		obj_material.Send_Data(is_lit,is_toon);
		obj_buffer.Send_Data(m_texture,is_textured);
		obj_buffer.Render();
	}
	else
	{
		model_ptr->SetPosition(pos_vec.x, pos_vec.y, pos_vec.z);
		model_ptr->SetRotation(rot.x, rot.y, rot.z);
		model_ptr->SetScale(scale_vec.x, scale_vec.y, scale_vec.z);
		
		model_ptr->Update();

		model_ptr->Draw();
	}

}

void GameObject::Update()
{
	//scale_mat = glm::mat4(1.0f);
	//scale_mat = glm::scale(scale_mat, scale_vec);

	translation = glm::mat4(1.0f);
	translation = glm::translate(translation, pos_vec);


	Update_Matrix();
}

void GameObject::Update_Matrix()
{
	model = glm::mat4(1.0f);
	model = model * translation;
	model = model * rotation_mat;
	model = glm::scale(model, scale_vec);
}
