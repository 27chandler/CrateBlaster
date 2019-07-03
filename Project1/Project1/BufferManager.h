#pragma once
#include <SDL.h>
#include <glm.hpp>
#include <glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Singleton.h"
#include "Texture.h"

#include <gtc/matrix_transform.hpp>

class BufferManager
{

public:

	friend class Singleton<BufferManager>;

	void Initialize(GLuint shaderProgID);
	void Set_Draw_Type(int type_input);
	void Clear_Depth_Buffer();
	void FillBuffers(GLfloat* vertices_input, int vertices_size_input, GLfloat* colours_input, int colours_size_input, GLuint* indices_input, int indices_size_input, GLfloat* uvs_input, int uvs_size_input);
	void Fill_EBO(GLuint* indices_input, int indices_size_input);
	void Fill_VBO(GLuint VBO_input,GLuint attribute_id_input, int num_of_values_input, GLfloat * array_input, int array_size_input);
	/*void FillBuffers_Lines(GLfloat* vertices_line_input, int vertices_line_size_input, GLfloat* colours_line_input, int colours_line_size_input, GLuint* indices_line_input, int indices_line_size_input);*/
	void DestroyBuffers();

	void UpdateVerts(float x_change,float y_change, float z_change);
	//void UpdateCamera(float x_change, float y_change, float z_change);

	void UpdateColours(float r_change, float g_change, float b_change);

	void RenderBuffers(int num_of_triangles,float counter);
	void RenderBuffers_Lines(int num_of_verts);

	void SetPerspective(float angle, float screen_width, float screen_height, float near, float far);

	void Set_Ortho(float width_input, float height_input);

	void Set_Tex_Ptr(Texture* texture_input,int id_input);


	void Bind();
	void Unbind();

	BufferManager();
	BufferManager(const BufferManager&);
	BufferManager& operator=(BufferManager&);


private:



	float offset[3] = { 0.0f,0.0f,0.0f };
	float colouroffset[3] = { 0.0f,0.0f,0.0f };


	GLuint m_shaderProgramID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;
	GLuint m_textureShaderID;

	GLuint VAO = 0;
	GLuint EBO = 0;

	GLuint vertexVBO = 0;
	GLuint colourVBO = 0;
	GLuint textureVBO = 0;

	GLuint vertexAttributeID;
	GLuint colourAttributeID;
	GLuint textureAttributeID;
	GLuint counterAttributeID;
	GLuint draw_type_attribute_id;

	GLuint counterUniformID = 0;
	GLuint draw_type_id = 0;

	GLuint texUniform1;
	GLuint texUniform2;

	Texture* shader_tex_1;
	Texture* shader_tex_2;




};


typedef Singleton<BufferManager> TheBuffer;