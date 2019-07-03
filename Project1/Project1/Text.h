#ifndef TEXT_H
#define TEXT_H
#include <SDL.h>
#include <glm.hpp>
#include <glew.h>
#include <string>

#include "BufferManager.h"
#include "Texture.h"

class Text
{
public:

	void Init(GLuint shaderProgID);
	void Set_Dimension(GLfloat width_input, GLfloat height_input);
	void Load_Texture(Texture * texture_input);
	void Render();
	void Move_Object(float x_change, float y_change, float z_change);

private:

	bool is_textured = 1;

	GLuint VAO;
	GLuint EBO;

	GLuint texture_VBO = 0;
	GLuint vertex_VBO = 0;
	GLuint colour_VBO = 0;

	GLuint vertex_attribute_id;
	GLuint colour_attribute_id;
	GLuint texture_attribute_id;

	GLfloat vertices[12];

	GLfloat colours[12] = {
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
	};		// Bottom left

	GLuint indices[6];

	GLfloat uvs[8];

	glm::mat4 model;
	GLuint modelID = 0;

	glm::vec3 QuadPos;

	Texture* m_texture;

	std::string display_text;

	glm::vec3 dimension;
};




#endif