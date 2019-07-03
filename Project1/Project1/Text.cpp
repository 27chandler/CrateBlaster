#include "Text.h"


void Text::Init(GLuint shaderProgID)
{
	vertex_attribute_id = glGetAttribLocation(shaderProgID, "vertexIn");
	colour_attribute_id = glGetAttribLocation(shaderProgID, "colourIn");
	texture_attribute_id = glGetAttribLocation(shaderProgID, "textureIn");

	//projID = glGetUniformLocation(shaderProgID, "proj");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertex_VBO);
	glGenBuffers(1, &colour_VBO);
	glGenBuffers(1, &texture_VBO);

	glGenBuffers(1, &EBO); // Create EBO

	//----------------------------------------------------------------
	modelID = glGetUniformLocation(shaderProgID, "model");

	QuadPos = glm::vec3(0.0f, 0.0f, 0.0f);

	display_text = "Hello";
	//----------------------------------------------------------------

	m_texture = new Texture;
	m_texture->Load("Calibri.png","Font");

	GLuint offset_vert = 0;
	GLuint offset_colour = 0;
	GLuint offset_text = 0;
	GLuint offset_index = 0;

	glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
		glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
		glVertexAttribPointer(vertex_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vertex_attribute_id);

		glBindBuffer(GL_ARRAY_BUFFER, colour_VBO);
		glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
		glVertexAttribPointer(colour_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(colour_attribute_id);

		glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
		glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
		glVertexAttribPointer(texture_attribute_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(texture_attribute_id);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind EBO
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW); // Fill EBO

	glBindVertexArray(0);

	glm::vec2 texture_cell;

	for (int i = 0; i < int(display_text.size()); i++)
	{
		//GLuint vertices[] = {
		//	0 + i, 1, 0,
		//	1 + i, 1, 0,
		//	1 + i, 0, 0,
		//	0 + i, 0, 0
		//};

		vertices[0] = GLfloat(0 + i);
		vertices[1] = GLfloat(1);
		vertices[2] = GLfloat(0);
		vertices[3] = GLfloat(1 + i);
		vertices[4] = GLfloat(1);
		vertices[5] = GLfloat(0);
		vertices[6] = GLfloat(1 + i);
		vertices[7] = GLfloat(0);
		vertices[8] = GLfloat(0);
		vertices[9] = GLfloat(0 + i);
		vertices[10] = GLfloat(0);
		vertices[11] = GLfloat(0);

		glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset_vert, sizeof(vertices), vertices);
		offset_vert += sizeof(vertices);

		//GLfloat colours[12] = {
		//	1.0f,1.0f,1.0f,
		//	1.0f,1.0f,1.0f,
		//	1.0f,1.0f,1.0f,
		//	1.0f,1.0f,1.0f,
		//};		// Bottom left

		glBindBuffer(GL_ARRAY_BUFFER, colour_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset_colour, sizeof(colours), colours);
		offset_colour += sizeof(colours);

		// Uvs
		int texture_index = display_text[i];

		texture_cell.x = float(texture_index % 16);
		texture_cell.y = float(texture_index / 16);

		glm::vec2 cell_dimension(0.0625f, 0.0625f);
		glm::vec2 tex_coord_origin = texture_cell * cell_dimension;

		uvs[0] = tex_coord_origin.x;
		uvs[1] = tex_coord_origin.y;
		uvs[2] = tex_coord_origin.x + cell_dimension.x;
		uvs[3] = tex_coord_origin.y;
		uvs[4] = tex_coord_origin.x + cell_dimension.x;
		uvs[5] = tex_coord_origin.y + cell_dimension.y;
		uvs[6] = tex_coord_origin.x;
		uvs[7] = tex_coord_origin.y + cell_dimension.y;

		glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset_index, sizeof(uvs), uvs);
		offset_text += sizeof(uvs);

		//GLuint indices[6] = {
		//0 + 4 * i,
		//1 + 4 * i,
		//3 + 4 * i,
		//3 + 4 * i,
		//1 + 4 * i,
		//2 + 4 * i
		//};

		indices[0] = (0 + 4 * i);
		indices[1] = (1 + 4 * i);
		indices[2] = (3 + 4 * i);
		indices[3] = (3 + 4 * i);
		indices[4] = (1 + 4 * i);
		indices[5] = (2 + 4 * i);

		glBindBuffer(GL_ARRAY_BUFFER, EBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset_index, sizeof(indices), indices);
		offset_index += sizeof(indices);

	}
}

void Text::Set_Dimension(GLfloat width_input, GLfloat height_input)
{
	dimension = glm::vec3(width_input, height_input, 1.0f);
}

void Text::Load_Texture(Texture * texture_input)
{
	m_texture = texture_input;
}

void Text::Move_Object(float x_change, float y_change, float z_change)
{

	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(x_change, y_change, z_change));

}

void Text::Render()
{
	GLuint ID = m_texture->Get_ID();

	//TheBuffer::Instance()->FillBuffers(&vertices[0], sizeof(vertices), &colours[0], sizeof(colours), &indices[0], sizeof(indices), &uvs[0], sizeof(uvs));

	//glBindVertexArray(VAO);

	//	glBindBuffer(GL_ARRAY_BUFFER, vertex_VBO);
	//	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	//	glVertexAttribPointer(vertex_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//	glEnableVertexAttribArray(vertex_attribute_id);

	//	glBindBuffer(GL_ARRAY_BUFFER, colour_VBO);
	//	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	//	glVertexAttribPointer(colour_attribute_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//	glEnableVertexAttribArray(colour_attribute_id);

	//	glBindBuffer(GL_ARRAY_BUFFER, texture_VBO);
	//	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	//	glVertexAttribPointer(texture_attribute_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//	glEnableVertexAttribArray(texture_attribute_id);

	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind EBO
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW); // Fill EBO

	//glBindVertexArray(0);

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

	glBindTexture(GL_TEXTURE_2D, ID);

	glBindVertexArray(VAO);
	//TheBuffer::Instance()->RenderBuffers(10000, 0);
	glDrawElements(GL_TRIANGLES, 10000, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
