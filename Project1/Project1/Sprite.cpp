#include "Sprite.h"

void Sprite::Set_Dimension(int width_input, int height_input)
{
	dimension = glm::vec3(width_input, height_input, 1.0f);
}

void Sprite::Set_Texture_Dimension(GLfloat column_input, GLfloat row_input)
{
	texture_dimension = glm::vec2(column_input, row_input);
}

void Sprite::Set_Texture_Cell(GLfloat column_input, GLfloat row_input)
{
	texture_cell = glm::vec2(column_input, row_input);
}

void Sprite::Init(GLuint shaderProgID)
{
	is_lit = 0;
	is_textured = 1;

	modelID = glGetUniformLocation(shaderProgID, "model");
	texture_flag_id = glGetUniformLocation(shaderProgID, "is_textured");
	light_flag_id = glGetUniformLocation(shaderProgID, "is_lit");

}

void Sprite::Load_Texture(Texture * texture_input)
{
	texture_ptr = texture_input;
}

void Sprite::Update()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);

	model = glm::scale(model, dimension);
	//

	if (is_animated == 1)
	{
		static int time = 0;
		time++;

		int texture_index = (int)(time * 0.05f) % (int)(texture_dimension.x * texture_dimension.y);

		texture_cell.x = (float)(texture_index % (int)texture_dimension.x);
		texture_cell.y = (float)(texture_index / (int)texture_dimension.x);
	}


	//
	glm::vec2 cell_dimension(1.0f / texture_dimension.x, 1.0f / texture_dimension.y);
	glm::vec2 tex_coord_origin = texture_cell * cell_dimension;

	uvs[0] = tex_coord_origin.x;
	uvs[1] = tex_coord_origin.y;
	uvs[2] = tex_coord_origin.x + cell_dimension.x;
	uvs[3] = tex_coord_origin.y;
	uvs[4] = tex_coord_origin.x + cell_dimension.x;
	uvs[5] = tex_coord_origin.y + cell_dimension.y;
	uvs[6] = tex_coord_origin.x;
	uvs[7] = tex_coord_origin.y + cell_dimension.y;

}

void Sprite::Render()
{
	if (is_lit == 1)
	{
		glUniform1i(light_flag_id, 1);
	}
	else
	{
		glUniform1i(light_flag_id, 0);
	}
	if (is_textured == 1)
	{
		GLuint ID = texture_ptr->Get_ID();
		glUniform1i(texture_flag_id, 1);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	else
	{
		glUniform1i(texture_flag_id, 0);
	}

	TheBuffer::Instance()->FillBuffers(&vertices[0], sizeof(vertices), &colours[0], sizeof(colours), &indices[0], sizeof(indices), &uvs[0], sizeof(uvs));

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

	TheBuffer::Instance()->RenderBuffers(6, 0);
}