#ifndef SHIP_H
#define SHIP_H

#include "GameObject.h"
#include "Audio.h"
#include "Missile.h"

class Ship : public GameObject
{
public:
	Ship(float input_arena_size);
	~Ship();

	void Update() override;
	void Render_Missiles();
	void Check_If_Out_Of_Bounds();

	void Enable_Powerup(int input_powerup);
	bool Get_Is_Boost_Enabled() { return is_boost_enabled; };

	glm::vec3 Get_Pos_Front(float input_offset_forward, float input_offset_right, float input_offset_up) { return pos_vec + (forward_vec * input_offset_forward) + (right_vec * input_offset_right) + (up_vec * input_offset_up); };
	glm::vec3 Get_Forward_Vec() { return forward_vec; };
	glm::vec3 Get_Right_Vec() { return right_vec; };
	glm::vec3 Get_Up_Vec() { return up_vec; };
	bool Get_Is_Out_Of_Bounds() { return is_out_of_bounds; };

	Missile* Get_Missile_Array() { return &missile_array[0]; };
	int Get_Num_Of_Missiles() { return NUM_OF_MISSILES; };
	int Get_Missile_Rot_Number() { return missile_rotation_num; };

	void Set_Controls(int input_accelerate, int i_decellerate, int input_yaw_left,
		int input_yaw_right, int input_tilt_up, int input_tilt_down,
		int input_roll_left, int input_roll_right, int input_shoot);

	static const int NUM_OF_MISSILES = 40;

private:

	enum Controls { ACCEL, DECEL, L_YAW, R_YAW, U_TILT, D_TILT, L_ROLL, R_ROLL, SHOOT };
	enum POWERUPS { NONE = 0, BOOST = 1 };

	const float SHIP_ACCELERATION = 0.001f;
	const float SHIP_TURN_SPEED = 0.5f;
	const int SHOOT_DELAY = 60;
	const int BOOST_TIME = 200;
	const float MIN_SPEED = 0.05f;
	const float BOOST_SPEED = 0.002f;
	float ARENA_SIZE = 0.0f;

	bool is_out_of_bounds = 0;
	bool is_boost_enabled = 0;
	int shoot_timer = 0;
	int boost_timer = 0;

	glm::vec3 forward_vec = { 0.0f,0.0f,1.0f };
	glm::vec3 right_vec = { 1.0f,0.0f,0.0f };
	glm::vec3 up_vec = { 0.0f,1.0f,0.0f };

	int controls_array[9] = { 0 };

	Missile missile_array[NUM_OF_MISSILES];
	int missile_rotation_num = 0;

	float speed = 0;

	Audio Shoot_Sound;
	Audio Powerup_Sound;
};

#endif