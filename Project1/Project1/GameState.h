#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
	GameState(GameState* i_prev_state) { prev_state = i_prev_state; };
	virtual ~GameState() = 0 {};

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Init() = 0;

	bool Get_Is_Active() { return is_active; };
	bool Get_Is_Alive() { return is_alive; };
	bool Get_Is_Inited() { return is_inited; };

	void Set_Is_Alive(bool i_is_alive) { is_alive = i_is_alive; };
	void Set_Is_Active(bool i_is_active) { is_active = i_is_active; };
	void Set_Is_Inited(bool i_is_inited) { is_inited = i_is_inited; };

protected:

	bool is_active = 1;
	bool is_alive = 1;
	bool is_inited = 0;
	GameState* prev_state;


};


#endif