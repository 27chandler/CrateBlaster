#include "Grid.h"

void Grid::Init(GLuint shaderProgID, int Grid_size_input, glm::vec3 initial_pos_input)
{
	modelID = glGetUniformLocation(shaderProgID, "model");

	GridPos = glm::vec3(initial_pos_input.x, initial_pos_input.y, initial_pos_input.z);

	Grid_size = Grid_size_input;

	GLuint offset = 0;

	GLuint shaderProgram = ThePipeline::Instance()->GetProgramID();

	vertexAttributeID = glGetAttribLocation(shaderProgram, "vertexIn");
	colourAttributeID = glGetAttribLocation(shaderProgram, "colourIn");
	modelID = glGetAttribLocation(shaderProgram, "model");

	texture_flag_id = glGetAttribLocation(shaderProgID, "is_textured");
	light_flag_id = glGetAttribLocation(shaderProgID, "is_lit");


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &vertexVBO);
	glGenBuffers(1, &colourVBO);

	glBindVertexArray(VAO);




	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(vertexAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vertexAttributeID);

	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferData(GL_ARRAY_BUFFER, 10000, nullptr, GL_STATIC_DRAW);
	glVertexAttribPointer(colourAttributeID, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colourAttributeID);


	for (int i = 0; i < Grid_size_input; i++) // One way lines
	{
		float length_addition = 0.0f;
		float colour_changer_value = 0.0f;

		if (((-Grid_size_input / 2) + i) == 0)
		{
			length_addition = 10.0f;
			colour_changer_value = 1.0f;
		}
		else
		{
			length_addition = 0.0f;
			colour_changer_value = 0.0f;
		}

		GLfloat vertices[] = { GLfloat(GridPos.x) + GLfloat(((-Grid_size_input / 2)) + i),GLfloat(GridPos.y) + 0.0f,GLfloat(GridPos.z) + (Grid_size_input / 2) + length_addition,GLfloat(GridPos.x) + GLfloat((-Grid_size_input / 2) + i),GLfloat(GridPos.y) + 0.0f,GLfloat(GridPos.z) + -(Grid_size_input / 2) - length_addition, };

		GLfloat colours[] = { 1.0f, 1.0f - colour_changer_value, 1.0f - colour_changer_value, 1.0f, 1.0f - colour_changer_value, 1.0f - colour_changer_value };

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colours), colours);


		offset += 24;
	}

	for (int i = 0; i < Grid_size_input; i++) // Other way lines
	{
		float length_addition = 0.0f;
		float colour_changer_value = 0.0f;

		if (((-Grid_size_input / 2) + i) == 0)
		{
			length_addition = 10.0f;
			colour_changer_value = 1.0f;
		}
		else
		{
			length_addition = 0.0f;
			colour_changer_value = 0.0f;
		}


		GLfloat vertices[] = { GLfloat(GridPos.x) + (Grid_size_input / 2) + length_addition,GLfloat(GridPos.y) + 0.0f,GLfloat(GridPos.z) + GLfloat((-Grid_size_input / 2) + i),GLfloat(GridPos.x) + -(Grid_size_input / 2) - length_addition,GLfloat(GridPos.y) + 0.0f,GLfloat(GridPos.z) + GLfloat((-Grid_size_input / 2) + i) };

		GLfloat colours[] = { 1.0f - colour_changer_value, 1.0f - colour_changer_value, 1.0f, 1.0f - colour_changer_value, 1.0f - colour_changer_value, 1.0f };

		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colours), colours);


		offset += 24;
	}

	GLfloat vertices_y[] = { 0.0f, 20.0f, 0.0f, 0.0f, -20.0f, 0.0f, };

	GLfloat colours_y[] = { 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f };

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(vertices_y), vertices_y);

	glBindBuffer(GL_ARRAY_BUFFER, colourVBO);
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(colours_y), colours_y);

	offset += 24;




	glBindVertexArray(VAO);

}

void Grid::Move_Grid(float x_change, float y_change, float z_change)
{
	model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(x_change, y_change, z_change));

}

void Grid::Set_Grid_Pos(glm::vec3 pos_input)
{
	
}

Grid::~Grid()
{

}

Grid::Grid()
{

}

void Grid::Render()
{
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);

	glUniform1i(light_flag_id, false);

	glUniform1i(texture_flag_id, false);

	glLineWidth(1.0f);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, (Grid_size*4)+2);
	glBindVertexArray(0);
}
