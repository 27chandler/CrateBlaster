#include "Texture.h"

std::map<std::string, GLuint>* Texture::m_texture_map = new std::map<std::string, GLuint>;

bool Texture::Load(const std::string filename, const std::string map_index)
{

	unsigned char* pixels = nullptr;
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int depth = 0;
	unsigned int format = 0;

	SDL_Surface* texture_data;

	texture_data = IMG_Load(filename.c_str());

	if (!texture_data)
	{
		std::cout << "Error loading texture: " << filename << std::endl;
		return false;
	}


	// Assign raw data to handles for later use
	pixels = (unsigned char*)texture_data->pixels;
	width = texture_data->w;
	height = texture_data->h;
	depth = texture_data->format->BytesPerPixel;
	if (depth == 4)
	{
		format = GL_RGBA;
	}
	else
	{
		format = GL_RGB;
	}

	// Generate an OpenGL image ID
	glGenTextures(1, &tex_id);

	// Bind ID and associate all settings below with that ID
	glBindTexture(GL_TEXTURE_2D, tex_id);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping around the s axis for the texture
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping around the t axis for the texture

		// Generate the ogl texture on the graphics card based on raw image data
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

		// Unloads the raw image from the memory of texture_data
		SDL_FreeSurface(texture_data);

		glGenerateMipmap(GL_TEXTURE_2D);

	// End binding
	glBindTexture(GL_TEXTURE_2D, 0);

	// Adds the texture to the map
	(*m_texture_map)[map_index] = tex_id;



	return true;
}

void Texture::Unload()
{
	// Deletes the texture
	glDeleteTextures(1, &tex_id);
}

void Texture::Unload_All()
{
	for (auto it = m_texture_map->begin(); it != m_texture_map->end(); it++)
	{
		glDeleteTextures(1, &(it->second));
	}
	m_texture_map->clear();
}

bool Texture::Set_Texture(const std::string & id_input)
{
	auto it = m_texture_map->find(id_input);

	if (it == m_texture_map->end())
	{
		std::cout << "Could not find texture!" << std::endl;
	}
	else
	{
		tex_id = it->second;
	}
	return false;
}
