#ifndef BUFFER_H
#define BUFFER_H

#include <SDL.h>
#include <glm.hpp>
#include <glew.h>
#include <vector>

#include "PipelineManager.h"
#include "Texture.h"

class Buffer
{
public:
	Buffer();
	~Buffer();

	void Init_Arrays();
	void Fill_Buffers();
	void Render(int size_input = 36);

	void Send_Data(Texture* texture_input,bool is_textured_input);

	void Set_Vert_Array(std::vector<GLfloat>* vertices_ptr_input) { vertices_ptr = vertices_ptr_input; };
	void Set_Colour_Array(std::vector<GLfloat>* colours_ptr_input) { colours_ptr = colours_ptr_input; };
	void Set_Uv_Array(std::vector<GLfloat>* uvs_ptr_input) { uvs_ptr = uvs_ptr_input; };
	void Set_Normal_Array(std::vector<GLfloat>* normals_ptr_input) { normals_ptr = normals_ptr_input; };
	void Set_Indices_Array(std::vector<GLuint>* indices_ptr_input) { indices_ptr = indices_ptr_input; };

	void Set_Model_Ptr(glm::mat4* model_input) { model_ptr = model_input; };

private:
	std::vector<GLfloat>* vertices_ptr;
	std::vector<GLfloat>* colours_ptr;
	std::vector<GLuint>* indices_ptr;
	std::vector<GLfloat>* uvs_ptr;
	std::vector<GLfloat>* normals_ptr;

private:

	GLuint program_id;

	GLuint texture_flag_id;

	glm::mat4* model_ptr;

	GLuint modelID;
	GLuint normal_mat_id;

	GLuint VAO;
	GLuint EBO;

	GLuint texture_VBO;
	GLuint vertex_VBO;
	GLuint colour_VBO;
	GLuint normal_VBO;

	GLuint vertex_attribute_id;
	GLuint colour_attribute_id;
	GLuint texture_attribute_id;
	GLuint normal_attribute_id;


};


#endif