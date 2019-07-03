#ifndef MATERIAL_H
#define MATERIAL_H

#include <SDL.h>
#include <glm.hpp>
#include <glew.h>

class Material
{
public:
	void Init();

	void Send_Data(bool is_lit_input, bool is_toon_input);
	void Set_Ambient(glm::vec3 ambient_input) { ambient = ambient_input; };
	void Set_Diffuse(glm::vec3 diffuse_input) { diffuse = diffuse_input; };
	void Set_Specular(glm::vec3 specular_input) { specular = specular_input; };

	void Set_Shininess(float shininess_input) { shininess = shininess_input; };

private:

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;


	float shininess;



private:
	GLuint program_id;

	GLuint light_flag_id;
	GLuint toon_flag_id;

	GLuint material_ambient_id;
	GLuint material_diffuse_id;
	GLuint material_specular_id;
	GLuint material_shininess_id;
};

#endif