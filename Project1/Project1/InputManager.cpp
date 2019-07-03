#include "InputManager.h"
#include <glew.h>
void InputManager::Init()
{
	
}

void InputManager::Update()
{
	current_keydown = ' ';
	SDL_Event events;

	mouse_wheel.x = 0;
	mouse_wheel.y = 0;
	
	mouse_motion.x = 0;
	mouse_motion.y = 0;

	is_game_ended = 0;

	key_states = SDL_GetKeyboardState(0);

	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
			case SDL_MOUSEWHEEL:
			{
				mouse_wheel.x = (float)events.wheel.x;
				mouse_wheel.y = (float)events.wheel.y;
				break;
			}
			case SDL_MOUSEMOTION:
			{
				mouse_motion.x = (float)events.motion.xrel;
				mouse_motion.y = (float)events.motion.yrel;

				mouse_position.x = (float)events.motion.x;
				mouse_position.y = (float)events.motion.y;
				break;
			}
			case SDL_KEYDOWN: // when the key is down
			{
				switch (events.key.keysym.sym)
				{
					case SDLK_w: // checks the "w" key
					{
						//std::cout << "w" << std::endl;
						current_keydown = 'w';
						key_array[12] = 1;
						break;
					}
					case SDLK_a: // checks the "d" key
					{
						current_keydown = 'a';
						key_array[21] = 1;
						break;
					}
					case SDLK_q: // checks the "q" key
					{
						//std::cout << "q" << std::endl;
						current_keydown = 'q';
						key_array[11] = 1;
						break;
					}
					case SDLK_e: // checks the "e" key
					{
						current_keydown = 'e';
						key_array[13] = 1;
						break;
					}
					case SDLK_s: // checks the "t" key
					{
						//std::cout << "s" << std::endl;
						current_keydown = 's';
						key_array[22] = 1;
						break;
					}
					case SDLK_d: // checks the "d" key
					{
						current_keydown = 'd';
						key_array[23] = 1;
						break;
					}
					case SDLK_RIGHT: // checks the "Right" key
					{
						key_array[50] = 1;
						//current_keydown = 'D';
						break;
					}
					case SDLK_LEFT: // checks the "Left" key
					{
						key_array[51] = 1;
						//current_keydown = 'A';
						break;
					}
					case SDLK_UP: // checks the "Up" key
					{
						key_array[52] = 1;
						//current_keydown = 'W';
						break;
					}
					case SDLK_DOWN: // checks the "Down" key
					{
						key_array[53] = 1;
						//current_keydown = 'S';
						break;
					}
					case SDLK_SPACE: // checks the "Space" key
					{
						key_array[10] = 1;
						break;
					}
					case SDLK_LSHIFT: // checks the "Left Shift" key
					{
						key_array[49] = 1;
						break;
					}
					case SDLK_RETURN: // checks the "Left Shift" key
					{
						key_array[48] = 1;
						break;
					}
					case SDLK_ESCAPE: // checks the "Escape" key
					{
						is_game_ended = 1;
						break;
					}
					default:
					{
						//std::cout << "NULL" << std::endl;
						current_keydown = NULL;
						break;
					}
				}
				break;
			}
			case SDL_KEYUP: // when the key is up
			{
				switch (events.key.keysym.sym)
				{
				case SDLK_w: // checks the "w" key
				{
					key_array[12] = 0;
					break;
				}
				case SDLK_a: // checks the "a" key
				{
					key_array[21] = 0;
					break;
				}
				case SDLK_q: // checks the "q" key
				{
					key_array[11] = 0;
					break;
				}
				case SDLK_e: // checks the "e" key
				{
					key_array[13] = 0;
					break;
				}
				case SDLK_s: // checks the "s" key
				{
					key_array[22] = 0;
					break;
				}
				case SDLK_d: // checks the "d" key
				{
					key_array[23] = 0;
					break;
				}
				case SDLK_SPACE: // checks the "Space" key
				{
					key_array[10] = 0;
					break;
				}
				case SDLK_LSHIFT: // checks the "Left Shift" key
				{
					key_array[49] = 0;
					break;
				}
				case SDLK_RIGHT: // checks the "Right" key
				{
					key_array[50] = 0;
					//current_keydown = 'D';
					break;
				}
				case SDLK_LEFT: // checks the "Left" key
				{
					key_array[51] = 0;
					//current_keydown = 'A';
					break;
				}
				case SDLK_UP: // checks the "Up" key
				{
					key_array[52] = 0;
					//current_keydown = 'W';
					break;
				}
				case SDLK_DOWN: // checks the "Down" key
				{
					key_array[53] = 0;
					//current_keydown = 'S';
					break;
				}
				case SDLK_RETURN: // checks the "Left Shift" key
				{
					key_array[48] = 0;
					break;
				}
				}
				break;
			}
			case SDL_QUIT:
			{
				is_game_ended = 1;
			}
		}
	}
}
bool InputManager::Game_Ended()
{
	if (is_game_ended)
	{
		return true;
	}
	return false;
}

glm::vec2 InputManager::Get_Mouse_Position()
{
	return mouse_position;
}

bool* InputManager::Get_Key_Array()
{
	return key_array;
}

glm::vec2 InputManager::Get_Mouse_Motion()
{
	return mouse_motion;
}