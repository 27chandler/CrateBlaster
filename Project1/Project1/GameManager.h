#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include "Singleton.h"
#include "GameState.h"
#include <deque>


class GameManager
{
public:

	friend Singleton<GameManager>;

public:


	void Init();
	void Shutdown();

	void Update();

	void Add_State(GameState * i_state);
	void Change_State(GameState * i_state);
	void Remove_State();


private:

	const int window_width = 1024;
	const int window_height = 600;

	const float target_fps = 60.0f;

	bool is_game_ended = 0;

	std::deque<GameState*> state_machine_deque;
};

typedef Singleton<GameManager> TheGame;


#endif
