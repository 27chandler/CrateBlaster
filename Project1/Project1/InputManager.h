#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include <glm.hpp>
#include <iostream>
#include "Singleton.h"
#include <string.h>

class InputManager
{

public:

	friend Singleton<InputManager>;

	void Init();

	void Update();
	bool Game_Ended();

	bool* Get_Key_Array();

	glm::vec2 Get_Mouse_Motion();


	const Uint8* key_states;
	glm::vec2 Get_Mouse_Position();

	enum Keys {KEY_W = 12, KEY_Q = 11, KEY_E = 13, KEY_A = 21, KEY_S = 22,KEY_D = 23,KEY_RIGHT = 50,KEY_LEFT = 51,KEY_UP = 52,KEY_DOWN = 53,KEY_LSHIFT = 49,KEY_SPACE = 10, KEY_RETURN = 48};
	



private:

	glm::vec2 mouse_position;
	glm::vec2 mouse_motion;
	glm::vec2 mouse_wheel;

	bool key_array[60];

	bool is_key_pressed;
	bool is_game_ended;
	InputManager() {}
	InputManager(const InputManager&);
	InputManager& operator=(InputManager&);

	bool game_ended = false;

	char current_keydown;
};

typedef Singleton<InputManager> Input;

#endif