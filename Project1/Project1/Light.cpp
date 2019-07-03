#include "Light.h"

GLuint Light::total_lights = 0;

void Light::Init()
{
	GLuint shaderProgID = ThePipeline::Instance()->GetProgramID();

	//ambient = glm::vec3(0.6f, 0.6f, 0.6f);
	//diffuse = glm::vec3(0.6f, 0.6f, 0.6f);
	//specular = glm::vec3(1.0f, 1.0f, 1.0f);

	//color = glm::vec3(1.0f, 1.0f, 1.0f);
	//pos = glm::vec3(0.0f, 0.0f, 0.0f);

	light_id_num = total_lights++;

	light_ambient_id = glGetUniformLocation(shaderProgID, ("the_light[" + std::to_string(light_id_num) + "].ambient").c_str());
	light_diffuse_id = glGetUniformLocation(shaderProgID, ("the_light[" + std::to_string(light_id_num) + "].diffuse").c_str());
	light_specular_id = glGetUniformLocation(shaderProgID, ("the_light[" + std::to_string(light_id_num) + "].specular").c_str());
	light_position_id = glGetUniformLocation(shaderProgID, ("the_light[" + std::to_string(light_id_num) + "].position").c_str());
	light_const_id = glGetUniformLocation(shaderProgID, ("the_light[" + std::to_string(light_id_num) + "].constant").c_str());
	light_linear_id = glGetUniformLocation(shaderProgID, ("the_light[" + std::to_string(light_id_num) + "].linear").c_str());
	light_quad_id = glGetUniformLocation(shaderProgID, ("the_light[" + std::to_string(light_id_num) + "].quadratic").c_str());

	total_lights_id = glGetUniformLocation(shaderProgID, "total_lights");

	texture_flag_id = glGetUniformLocation(shaderProgID, "is_textured");
	light_flag_id = glGetUniformLocation(shaderProgID, "is_lit");
	model_uniform_id = glGetUniformLocation(shaderProgID, "model");

	vertex_attribute_id = glGetAttribLocation(shaderProgID, "vertexIn");
	colour_attribute_id = glGetAttribLocation(shaderProgID, "colourIn");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertex_VBO);
	glGenBuffers(1, &colour_VBO);

	GLfloat vertex[3] = { pos.x,pos.y,pos.z };
	GLfloat colour[3] = { ambient.r,ambient.g,ambient.b };

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);
		glVertexAttribPointer(vertex_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertex_attribute_id);

		glBindBuffer(GL_ARRAY_BUFFER, colour_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colour), &colour[0], GL_STATIC_DRAW);
		glVertexAttribPointer(colour_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colour_attribute_id);
	glBindVertexArray(0);
}

void Light::Update()
{
	bool has_moved = 0;
	//if (Input::Instance()->Get_Key_Array()[50] == 1)
	//{
	//	has_moved = 1;
	//	pos.x -= speed;
	//}
	//if (Input::Instance()->Get_Key_Array()[51] == 1)
	//{
	//	has_moved = 1;
	//	pos.x += speed;
	//}

	//if (Input::Instance()->Get_Key_Array()[52] == 1)
	//{
	//	has_moved = 1;
	//	pos.z -= speed;
	//}
	//if (Input::Instance()->Get_Key_Array()[53] == 1)
	//{
	//	has_moved = 1;
	//	pos.z += speed;
	//}
	//if (Input::Instance()->Get_Key_Array()[10] == 1)
	//{
	//	has_moved = 1;
	//	pos.y += speed;
	//}
	//if (Input::Instance()->Get_Key_Array()[49] == 1)
	//{
	//	has_moved = 1;
	//	pos.y -= speed;
	//}

	if (has_moved)
	{
		GLfloat vertex[3] = { pos.x,pos.y,pos.z };

		glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

}

void Light::Render()
{
	glUniformMatrix4fv(model_uniform_id, 1, GL_FALSE, &model[0][0]);

	glUniform3fv(light_position_id, 1, &pos.x);
	glUniform3fv(light_ambient_id, 1, &ambient.r);
	glUniform3fv(light_diffuse_id, 1, &diffuse.r);
	glUniform3fv(light_specular_id, 1, &specular.r);

	glUniform1i(light_flag_id, false);

	glUniform1i(total_lights_id, total_lights);

	glUniform1i(texture_flag_id, false);

	glUniform1f(light_const_id, light_const);
	glUniform1f(light_quad_id, light_quad);
	glUniform1f(light_linear_id, light_linear);

	//glUniform3fv(light_colour_uniform_id, 1, &color.r);

	//glPointSize(25.0f);

	//glBindVertexArray(VAO);
	//TheBuffer::Instance()->Bind();
		//glDrawArrays(GL_POINTS,0,1);
	//TheBuffer::Instance()->Unbind();
	//glBindVertexArray(0);
}

void Light::Set_Pos(glm::vec3 input_pos)
{
	pos = input_pos;


	GLfloat vertex[3] = { pos.x,pos.y,pos.z };
	GLfloat colour[3] = { ambient.r,ambient.g,ambient.b };

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), &vertex[0], GL_STATIC_DRAW);
		glVertexAttribPointer(vertex_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertex_attribute_id);

		glBindBuffer(GL_ARRAY_BUFFER, colour_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colour), &colour[0], GL_STATIC_DRAW);
		glVertexAttribPointer(colour_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colour_attribute_id);
	glBindVertexArray(0);
}
