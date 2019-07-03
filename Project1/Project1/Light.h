#ifndef LIGHT_H
#define LIGHT_H

#include <SDL.h>
#include <glm.hpp>
#include <glew.h>

#include "BufferManager.h"
#include "PipelineManager.h"


class Light
{
public:
	void Init();

	void Update();

	void Render();

	glm::vec3 Get_Pos() { return pos; };

	static GLuint total_lights;


public: // Getters and Setters section

	void Set_Specular(glm::vec3 input_specular) { specular = input_specular; };
	void Set_Ambient(glm::vec3 input_ambient) { ambient = input_ambient; };
	void Set_Diffuse(glm::vec3 input_diffuse) { diffuse = input_diffuse; };

	void Set_Const(float input_const) { light_const = input_const; };
	void Set_Lin(float input_lin) { light_linear = input_lin; };
	void Set_Quad(float input_quad) { light_quad = input_quad; };

	void Set_Pos(glm::vec3 input_pos);

private:



	int light_id_num = 0;

	GLuint VAO;
	GLuint vertex_VBO;
	GLuint colour_VBO;

	GLuint light_flag_id;
	GLuint texture_flag_id;
	GLuint model_uniform_id;
	GLuint light_colour_uniform_id;
	GLuint total_lights_id;

	GLuint vertex_attribute_id;
	GLuint colour_attribute_id;

	GLuint light_ambient_id;
	GLuint light_diffuse_id;
	GLuint light_specular_id;
	GLuint light_position_id;

	GLuint light_const_id;
	GLuint light_quad_id;
	GLuint light_linear_id;
	//GLuint VAO;
	//GLuint VAO;

	glm::mat4 model;
	glm::vec3 color;
	glm::vec3 pos;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float light_const = 0.1f;
	float light_quad = 0.1f;
	float light_linear = 0.1f;

	float speed = 0.05f;
};



#endif