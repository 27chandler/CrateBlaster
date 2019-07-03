#ifndef GRID_H
#define GRID_H

#include <SDL.h>
#include <glm.hpp>
#include <glew.h>
#include "BufferManager.h"
#include "PipelineManager.h"

#include <gtc/matrix_transform.hpp>

class Grid
{
public:

	void Init(GLuint shaderProgID, int Grid_size_input, glm::vec3 initial_pos_input = glm::vec3(0.0f,0.0f,0.0f));
	void Render();
	void Move_Grid(float x_change, float y_change, float z_change);

	void Set_Grid_Pos(glm::vec3 pos_input);

	Grid();
	~Grid();

private:

	GLuint VAO = 0;

	GLuint vertexVBO = 0;
	GLuint colourVBO = 0;

	GLuint vertexAttributeID;
	GLuint colourAttributeID;
	GLuint light_flag_id;
	GLuint texture_flag_id;

	glm::vec3 GridPos;

	glm::mat4 model;
	GLuint modelID = 0;

	int Grid_size;


};





#endif