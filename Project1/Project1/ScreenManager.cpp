#include "ScreenManager.h"
#include <glew.h>

bool ScreenManager::Init(int major,int minor,const char* window_name,int width, int height,bool core,bool show_extensions,bool show_profile)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SLD didn't initialize" << std::endl;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//set double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	if (core == 1) // Sets core or compatibility mode on or off
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	}
	

	//set ogl context version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, major);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minor);

	//creates window (Name,X location,Y location,Width,Height,Thing)
	window = SDL_CreateWindow(window_name, 80, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);


	if (!window)
	{
		std::cout << "OOPS" << std::endl;
	}

	//create opengl context
	context = SDL_GL_CreateContext(window);

	if (!context)
	{
		std::cout << "Context wasn't created" << std::endl;
	}

	DisplayProfile(show_profile);
	DisplayExtensions(show_extensions);

	//projID = glGetUniformLocation(shaderProgID, "proj");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return false;
}

void ScreenManager::Send_Program_ID(GLuint program_id_input)
{
	projID = glGetUniformLocation(program_id_input, "proj");
}

void ScreenManager::Render()
{
	// this sends the projection matrix data to the shaders
	glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);
}

void ScreenManager::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ScreenManager::EnableZBuffer()
{
	glEnable(GL_DEPTH_TEST);
}

void ScreenManager::View(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
	screen_width = width;
	screen_height = height;
}

void ScreenManager::SwapBuffer()
{
	SDL_GL_SwapWindow(window);
}

void ScreenManager::Shutdown()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void ScreenManager::DisplayExtensions(bool is_displayed)
{
	if (is_displayed)
	{
		glewExperimental = GL_TRUE;

		if (glewInit() != GLEW_OK) // Initiates GLEW
		{
			std::cout << "GLEW DID NOT INITIATE PROPERLY" << std::endl;
		}

		GLint totalExtensions;
		glGetIntegerv(GL_NUM_EXTENSIONS, &totalExtensions);

		for (GLint i = 0; i < totalExtensions; i++) // Lists all extensions compatible with current graphics card
		{
			std::cout << "Extension #" << i + 1 << " : " << (const char*)glGetStringi(GL_EXTENSIONS, i) << std::endl;
		}
	}
}

void ScreenManager::DisplayProfile(bool is_displayed)
{
	if (is_displayed)
	{
		//displays the graphics card manufacturer
		std::cout << "GRAPHICS CARD MANUFACTURER: " << (const char*)(glGetString(GL_VENDOR)) << std::endl;

		//displays the make and model of the graphics card
		std::cout << "GRAPHICS CARD MAKE + MODEL: " << (const char*)(glGetString(GL_RENDERER)) << std::endl;

		//displays the current OpenGL version number and mode set
		std::cout << "OPENGL VERSION NUMBER + MODE: " << (const char*)(glGetString(GL_VERSION)) << std::endl;

		//displays which GLSL version is supported by the graphics card
		std::cout << "GLSL VERSION SUPPORT: " << (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION)) << std::endl;
	}
}

void ScreenManager::ErrorCheck()
{
	GLenum error_value = glGetError();

	if (error_value == GL_NO_ERROR)
	{
		std::cout << "NO ERRORS" << std::endl;
	}
	else if (error_value == GL_INVALID_OPERATION)
	{
		std::cout << "INVALID OPERATION" << std::endl;
	}
}

void ScreenManager::Set_2D_Screen()
{
	glDisable(GL_DEPTH_TEST);
	//TheBuffer::Instance()->Set_Ortho(1024, 768);

	proj = glm::mat4(1.0f);

	proj = glm::ortho(0.0f, 1024.0f, 0.0f, 768.0f);

	// this sends the projection matrix data to the shaders
	glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);
}

void ScreenManager::Set_3D_Screen()
{
	glEnable(GL_DEPTH_TEST);
	//TheBuffer::Instance()->SetPerspective(90.0f, 1024.0f, 768.0f, 0.1f, 10000.0f);

	proj = glm::mat4(1.0f);

	proj = glm::perspective(glm::radians(90.0f), 1024.0f / 768.0f, 0.1f, 10000.0f);

	// this sends the projection matrix data to the shaders
	glUniformMatrix4fv(projID, 1, GL_FALSE, &proj[0][0]);
}
