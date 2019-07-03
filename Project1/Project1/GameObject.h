#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL.h>
#include <glm.hpp>
#include <glew.h>

#include <deque>
#include <vector>

#include "BufferManager.h"
#include "Texture.h"
#include "Buffer.h"
#include "Material.h"
#include "Model.h"

class GameObject
{
public:
	~GameObject();
	void Init(GLuint shaderProgID);
	void Load_Texture(Texture * texture_input);
	void Set_Pos(glm::vec3 input_pos);
	glm::vec3 Get_Pos() { return pos_vec; };
	void Set_Momentum(glm::vec3 momentum_input) { momentum_vec = momentum_input; };
	glm::vec3 Get_Momentum() { return momentum_vec; };
	void Set_Scale(glm::vec3 input_scale);
	glm::vec3 Get_Scale() { return scale_vec; };
	void Set_Rotation(glm::vec3 axis_input, float angle);
	void Set_Model_Ptr(Model* input_model) { model_ptr = input_model; };

	void Render();

	void Set_Id(std::string input_id) { id = input_id; };
	std::string Get_Id() { return id; };

	glm::mat4 Get_Rotation_Matrix() { return rotation_mat; };

	void Set_Is_Lit(bool input_flag) { is_lit = input_flag; };
	void Set_Is_Textured(bool input_flag) { is_textured = input_flag; };
	void Set_Is_Toon(bool input_flag) { is_toon = input_flag; };
	bool Get_Is_Toon() { return is_toon; };
	void Set_Is_Alive(bool input_flag) { is_alive = input_flag; };
	bool Get_Is_Alive() { return is_alive; };


	virtual void Update();


protected:

	Model* model_ptr;

	void Update_Matrix();

	int num_of_triangles = 0;

	float scale = 1.0f;

	bool is_lit;
	bool is_textured;
	bool is_toon = 0;
	bool is_alive = 1;

	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colours;
	std::vector<GLuint> indices;
	std::vector<GLfloat> uvs;
	std::vector<GLfloat> normals;

	std::string id = "";

	//-----------------------------------------

	//float shininess;

	//glm::vec3 ambient;
	//glm::vec3 diffuse;
	//glm::vec3 specular;

	//GLuint texture_VBO;
	//GLuint vertex_VBO;
	//GLuint colour_VBO;
	//GLuint normal_VBO;

	//GLuint vertex_attribute_id;
	//GLuint colour_attribute_id;
	//GLuint texture_attribute_id;
	//GLuint normal_attribute_id;

	//GLuint material_ambient_id;
	//GLuint material_diffuse_id;
	//GLuint material_specular_id;
	//GLuint material_shininess_id;

	glm::mat4 model;

	glm::mat4 translation;
	glm::mat4 scale_mat;
	glm::mat4 rotation_mat;

	glm::vec3 pos_vec;
	glm::vec3 momentum_vec;
	glm::vec3 scale_vec;
	glm::vec3 rot;
	//glm::mat3 normal_mat;
	//GLuint modelID;
	//GLuint normal_mat_id;

	//GLuint VAO;
	//GLuint EBO;

	//GLuint light_flag_id;
	//GLuint texture_flag_id;


	Texture* m_texture;
	Buffer obj_buffer;
	Material obj_material;


private:



};




#endif
