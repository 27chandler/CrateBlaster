#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <map>
#include <string>
#include <glew.h>
#include <SDL_image.h>

class Texture
{
public:

	GLuint Get_ID() { return tex_id; };
	void Set_ID(GLuint input_tex_id) { tex_id = input_tex_id; };
	bool Load(const std::string filename, const std::string map_index);
	void Unload();
	void Unload_All();
	bool Set_Texture(const std::string & ID);



private:

	GLuint tex_id;

	static std::map<std::string, GLuint>* m_texture_map;


};




#endif