#include "BufferManager.h"

glm::mat4 proj;
GLuint projID = 0;


BufferManager::BufferManager()
{

}

void BufferManager::Initialize(GLuint shaderProgID)
{
	vertexAttributeID = glGetAttribLocation(shaderProgID, "vertexIn");
	colourAttributeID = glGetAttribLocation(shaderProgID, "colourIn");
	textureAttributeID = glGetAttribLocation(shaderProgID, "textureIn");//

	counterUniformID = glGetUniformLocation(shaderProgID, "counterIn");
	projID = glGetUniformLocation(shaderProgID, "proj");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colourVBO);
	glGenBuffers(1, &textureVBO);

	glGenBuffers(1, &EBO); // Create EBO



}

void BufferManager::Set_Draw_Type(int type_input)
{
	draw_type_id = type_input;
}

void BufferManager::Clear_Depth_Buffer()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void BufferManager::FillBuffers(GLfloat* vertices_input, int vertices_size_input, GLfloat* colours_input, int colours_size_input, GLuint* indices_input, int indices_size_input, GLfloat* uvs_input, int uvs_size_input)
{

	//
	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices_size_input, vertices_input, GL_STATIC_DRAW);
		glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertexAttributeID);

		glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
		glBufferData(GL_ARRAY_BUFFER, colours_size_input, colours_input, GL_STATIC_DRAW);
		glVertexAttribPointer(colourAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colourAttributeID);

		glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
		glBufferData(GL_ARRAY_BUFFER, uvs_size_input, uvs_input, GL_STATIC_DRAW);
		glVertexAttribPointer(textureAttributeID, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(textureAttributeID);

		//glVertexAttribPointer(draw_type_id, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// EBO

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size_input, indices_input, GL_STATIC_DRAW); // Fill EBO

	glBindVertexArray(0);
}

void BufferManager::Fill_EBO(GLuint* indices_input, int indices_size_input)
{
	glVertexAttribPointer(draw_type_id, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size_input, indices_input, GL_STATIC_DRAW); // Fill EBO
}

void BufferManager::Fill_VBO(GLuint VBO_input, GLuint attribute_id_input, int num_of_values_input, GLfloat* array_input, int array_size_input)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO_input);
	glBufferData(GL_ARRAY_BUFFER, array_size_input, array_input, GL_STATIC_DRAW);
	glVertexAttribPointer(attribute_id_input, num_of_values_input, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribute_id_input);
}

void BufferManager::DestroyBuffers()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &EBO);
	glDeleteBuffers(1, &vertexVBO);
	glDeleteBuffers(1, &colourVBO);
	glDeleteBuffers(1, &textureVBO);

	glDisableVertexAttribArray(colourAttributeID);
	glDisableVertexAttribArray(vertexAttributeID);

}

void BufferManager::RenderBuffers(int num_of_triangles,float counter)
{
	// this sends the projection matrix data to the shaders
	//glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, shader_tex_1->Get_ID());

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, shader_tex_2->Get_ID());

	//glUniform1i(texUniform1, 0);
	//glUniform1i(texUniform2, 1);

	Bind();
		glDrawElements(GL_TRIANGLES, num_of_triangles, GL_UNSIGNED_INT, 0);
	Unbind();

}

void BufferManager::RenderBuffers_Lines(int num_of_verts)
{
	// this sends the projection matrix data to the shaders
	//glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);


	Bind();
		glDrawArrays(GL_LINES,0,num_of_verts);
	Unbind();
}

void BufferManager::Bind()
{
	glBindVertexArray(VAO);
}


void BufferManager::Unbind()
{
	glBindVertexArray(0);
}

void BufferManager::SetPerspective(float angle, float screen_width, float screen_height, float near, float far)
{
	//proj = glm::mat4(1.0f);

	//proj = glm::perspective(glm::radians(angle), screen_width/screen_height, near, far);

	//// this sends the projection matrix data to the shaders
	//glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);
}

void BufferManager::Set_Ortho(float width_input, float height_input)
{
	//proj = glm::mat4(1.0f);

	//proj = glm::ortho(0.0f, width_input,0.0f, height_input);

	//// this sends the projection matrix data to the shaders
	//glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);
}

void BufferManager::Set_Tex_Ptr(Texture * texture_input, int id_input)
{
	if (id_input == 0)
	{
		shader_tex_1 = texture_input;
	}
	else if (id_input == 1)
	{
		shader_tex_2 = texture_input;
	}
}

void BufferManager::UpdateVerts(float x_change, float y_change, float z_change)
{

}

void BufferManager::UpdateColours(float r_change, float g_change, float b_change)
{
	colouroffset[0] = r_change;
	colouroffset[1] = g_change;
	colouroffset[2] = b_change;
}


/*



*/