#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <SDL.h>
#include <glm.hpp>
#include <iostream>
#include "Singleton.h"
#include "BufferManager.h"

class ScreenManager
{

public:

	friend Singleton<ScreenManager>;
public:

	bool Init(int major, int minor, const char* window_name, int width, int height, bool core, bool show_extensions, bool show_profile);
	void Send_Program_ID(GLuint program_id_input);
	void Render();
	void ClearScreen();
	void EnableZBuffer();
	void View(int x, int y, int width, int height);

	int Get_Screen_Width() { return screen_width; };
	int Get_Screen_Height() { return screen_height; };

	void Set_FullScreen_Mode(bool input_flag) { SDL_SetWindowFullscreen(window, input_flag); };

	void SwapBuffer();
	void Shutdown();

	void ErrorCheck();

	void Set_2D_Screen();

	void Set_3D_Screen();

private:
	void DisplayExtensions(bool is_displayed);
	void DisplayProfile(bool is_displayed);


	ScreenManager() {}
	ScreenManager(const ScreenManager&);
	ScreenManager& operator=(ScreenManager&);

	glm::mat4 proj;
	GLuint projID = 0;

	int screen_width = 0;
	int screen_height = 0;

	glm::vec2 myVec;

	SDL_Window* window;
	SDL_GLContext context;




};

typedef Singleton<ScreenManager> TheScreen;

#endif