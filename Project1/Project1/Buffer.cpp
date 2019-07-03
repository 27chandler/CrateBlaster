#include "Buffer.h"

Buffer::Buffer()
{
}

Buffer::~Buffer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &texture_VBO);
	glDeleteBuffers(1, &vertex_VBO);
	glDeleteBuffers(1, &colour_VBO);
	glDeleteVertexArrays(1, &EBO);


	glDisableVertexAttribArray(colour_attribute_id);
	glDisableVertexAttribArray(vertex_attribute_id);
	glDisableVertexAttribArray(texture_attribute_id);
	glDisableVertexAttribArray(normal_attribute_id);
}

void Buffer::Init_Arrays()
{
	program_id = ThePipeline::Instance()->GetProgramID();

	texture_flag_id = glGetUniformLocation(program_id, "is_textured");

	vertex_attribute_id = glGetAttribLocation(program_id, "vertexIn");
	colour_attribute_id = glGetAttribLocation(program_id, "colourIn");
	texture_attribute_id = glGetAttribLocation(program_id, "textureIn");
	normal_attribute_id = glGetAttribLocation(program_id, "normalIn");

	modelID = glGetUniformLocation(program_id, "model");
	normal_mat_id = glGetUniformLocation(program_id, "normal_mat");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertex_VBO);
	glGenBuffers(1, &colour_VBO);
	glGenBuffers(1, &texture_VBO);
	glGenBuffers(1, &normal_VBO);

	glGenBuffers(1, &EBO);
}

void Buffer::Fill_Buffers()
{
	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
		glBufferData(GL_ARRAY_BUFFER, (*vertices_ptr).size() * sizeof(GLfloat), &(*vertices_ptr)[0], GL_STATIC_DRAW);
		glVertexAttribPointer(vertex_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertex_attribute_id);

		glBindBuffer(GL_ARRAY_BUFFER, colour_VBO);
		glBufferData(GL_ARRAY_BUFFER, (*colours_ptr).size() * sizeof(GLfloat), &(*colours_ptr)[0], GL_STATIC_DRAW);
		glVertexAttribPointer(colour_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colour_attribute_id);

		glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
		glBufferData(GL_ARRAY_BUFFER, (*uvs_ptr).size() * sizeof(GLfloat), &(*uvs_ptr)[0], GL_STATIC_DRAW);
		glVertexAttribPointer(texture_attribute_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(texture_attribute_id);

		glBindBuffer(GL_ARRAY_BUFFER, normal_VBO);
		glBufferData(GL_ARRAY_BUFFER, (*normals_ptr).size() * sizeof(GLfloat), &(*normals_ptr)[0], GL_STATIC_DRAW);
		glVertexAttribPointer(normal_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(normal_attribute_id);

		// EBO

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*indices_ptr).size() * sizeof(GLuint), &(*indices_ptr)[0], GL_STATIC_DRAW); // Fill EBO

		glBindVertexArray(0);
	


}

void Buffer::Render(int size_input)
{
	glm::mat3 normal_mat = glm::inverse(glm::mat3(*model_ptr));

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &(*(model_ptr))[0][0]);
	glUniformMatrix3fv(normal_mat_id, 1, GL_TRUE, &normal_mat[0][0]);

	glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, size_input, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Buffer::Send_Data(Texture* texture_input,bool is_textured_input)
{
	if (is_textured_input == 1)
	{
		GLuint ID = texture_input->Get_ID();
		glUniform1i(texture_flag_id, true);
		glBindTexture(GL_TEXTURE_2D, ID);
	}
	else
	{
		glUniform1i(texture_flag_id, false);
	}
}
