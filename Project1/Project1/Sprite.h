#ifndef SPRITE_H
#define SPRITE_H

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "BufferManager.h"

#include "Texture.h"

class Sprite
{
public:
	void Set_Dimension(int width_input, int height_input);
	void Set_Texture_Dimension(GLfloat column_input, GLfloat row_input);
	void Set_Texture_Cell(GLfloat column_input, GLfloat row_input);
	void Init(GLuint shaderProgID);
	void Load_Texture(Texture * texture_input);

	void Set_Pos(glm::vec3 input_pos) { pos = input_pos; };

	void Update();

	void Render();

	bool &Is_Animated() { return is_animated; };


private:
	bool is_animated;
	bool is_textured;
	bool is_lit;

	GLuint VAO;
	GLuint EBO;
	GLuint vertex_VBO;
	GLuint colour_VBO;
	GLuint texture_VBO;

	GLuint texture_flag_id;
	GLuint light_flag_id;
	GLuint model_uniform_id;
	GLuint vertex_atribute_id;
	GLuint colour_attribute_id;
	GLuint texture_attribute_id;

	glm::mat4 model;
	GLuint modelID = 0;

	GLuint ID = 0;

	glm::vec3 dimension;

	glm::vec2 texture_dimension;
	glm::vec2 texture_cell;



	GLfloat vertices[12] =
	{ 
	0,1,0,
	1,1,0,
	1,0,0,
	0,0,0 
	};

	GLfloat colours[12] =
	{
	1,1,1,
	1,1,1,
	1,1,1,
	1,1,1
	};

	GLuint indices[6] = { 0,1,3,3,1,2,
	};

	GLfloat uvs[8] =
	{ 0.0f,0.0f,
		1.0f,0.0f,
		1.0f,1.0f,
		0.0f,1.0f };

	glm::vec3 pos = { 0.0f,0.0f,0.0f };

	Texture* texture_ptr;
};



#endif