#ifndef CAMERA_H
#define CAMERA_H
#include <SDL.h>
#include <glm.hpp>
#include <glew.h>
#include <iostream>
#include "InputManager.h"

#include <gtc/matrix_transform.hpp>

class Camera
{
public:

	void Init(GLuint shaderProgID);

	void UpdateCameraPos(float x_change, float y_change, float z_change);

	void Set_2D_Mode();

	void Set_3D_Mode();

	void RotateCameraX(float rotation_angle, glm::vec3 axis_input);
	void RotateCameraY(float rotation_angle, glm::vec3 axis_input);

	void SetPos(glm::vec3 input_pos);

	void SetDir(glm::vec3 input_dir);

	void SetUp(glm::vec3 input_up);

	void SendCamera();

	glm::vec3 GetPos();
	glm::vec3 GetDir();
	glm::vec3 GetUp();

	float Get_Angle_Y() { return angle_y; };

	void Move_In_Direction(float speed_input, bool is_movement_absolute, glm::vec3 direction, glm::vec3 axis);

	void Movement_Control(float movespeed_input);

	void Update();

	Camera() {};

private:
	bool do_update_camera = 0;

	float angle_x = 0;
	float angle_y = 0;

	glm::mat4 rotation_input_x;
	glm::mat4 rotation_input_y;

	glm::vec3 Pos_Change;


	glm::vec2 myVec;
	glm::vec2 mouse_motion;

	SDL_Window* window;
	SDL_GLContext context;

	glm::vec3 CamPos;
	glm::vec3 CamDir;
	glm::vec3 CamUp;

	glm::mat4 view;
	glm::mat4 view_temp;
	GLuint viewID = 0;
	GLuint position_id = 0;

};

//typedef Singleton<camera> TheCamera;


#endif
