#include "camera.h"

void Camera::Init(GLuint shaderProgID)
{
	viewID = glGetUniformLocation(shaderProgID, "view");
	CamPos = glm::vec3(0.0f, 0.0f, 0.0f);
	CamDir = glm::vec3(0.0f, 0.0f,1.0f);
	CamUp = glm::vec3(0.0f, 1.0f, 0.0f);
	position_id = glGetUniformLocation(shaderProgID, "cam_pos");
}

void Camera::UpdateCameraPos(float x_change, float y_change, float z_change)
{
	Pos_Change += glm::vec3(x_change, y_change, z_change);
}

void Camera::Set_2D_Mode()
{
	view_temp = view;
	view = glm::mat4(1.0f);
}

void Camera::Set_3D_Mode()
{
	view = view_temp;
}

void Camera::RotateCameraX(float rotation_angle, glm::vec3 axis_input)
{

	rotation_input_x = glm::rotate(rotation_input_x, glm::radians(rotation_angle), axis_input);

	angle_x += rotation_angle;

	do_update_camera = 1;

}

void Camera::RotateCameraY(float rotation_angle, glm::vec3 axis_input)
{

	rotation_input_y = glm::rotate(rotation_input_y, glm::radians(rotation_angle), glm::vec3(1.0f,0.0f,0.0f));

	angle_y += rotation_angle;

	do_update_camera = 1;

}

void Camera::SetPos(glm::vec3 input_pos)
{
	CamPos = input_pos;
}

void Camera::SetDir(glm::vec3 input_pos)
{
	CamDir = input_pos;
}

void Camera::SetUp(glm::vec3 input_up)
{
	CamUp = input_up;
}

void Camera::SendCamera()
{
	// this sends the view matrix data to the shaders
	glUniformMatrix4fv(viewID, 1, GL_FALSE, &view[0][0]);

	// this sends the camera position to the shaders
	glUniform3fv(position_id, 1, &CamPos.x);
}

glm::vec3 Camera::GetPos()
{
	return CamPos;
}

glm::vec3 Camera::GetDir()
{
	return CamDir;
}

glm::vec3 Camera::GetUp()
{
	return CamUp;
}

void Camera::Move_In_Direction(float speed_input,bool is_movement_absolute,glm::vec3 direction,glm::vec3 axis)
{
		
	glm::vec3 move_direction = direction * speed_input; // Sets move_direction to the inputted direction multiplied by the inputted speed

	glm::mat4 rotation; // Creates the rotation matrix

	if (is_movement_absolute == 0) // Checks if movement is relative to the player or not
	{
		rotation = glm::rotate(rotation, glm::radians(angle_x), axis);

		move_direction = rotation * glm::vec4(move_direction, 1.0f);

		//std::cout << move_direction.x << ":" << move_direction.y << ":" << move_direction.z << std::endl;
	}
	else
	{
		// Nothing
	}



	CamPos += move_direction;
}

void Camera::Movement_Control(float movespeed_input) // Controls camera movement
{
	mouse_motion = Input::Instance()->Get_Mouse_Motion();

	//RotateCameraX(-mouse_motion.x, glm::vec3(0.0f, 1.0f, 0.0f));

	//if (mouse_motion.x < 0)
	//{
	//	std::cout << "-" << std::endl;
	//	//
	//}
	//else if (mouse_motion.x > 0)
	//{
	//	std::cout << "+" << std::endl;
	//}

	RotateCameraX(-mouse_motion.x, glm::vec3(0.0f, 1.0f, 0.0f));

	if (mouse_motion.y + angle_y >= 80)
	{
		mouse_motion.y = 80 - angle_y;
	}
	else if (mouse_motion.y + angle_y <= -80)
	{
		mouse_motion.y = -80 - angle_y;
	}

	if ((mouse_motion.y > 0) && (angle_y <= 80))
	{
		RotateCameraY(mouse_motion.y, glm::vec3(0.0f, 0.0f, 1.0f));
	}
	else if ((mouse_motion.y < 0) && (angle_y >= -80))
	{
		RotateCameraY(mouse_motion.y, glm::vec3(0.0f, 0.0f, 1.0f));
	}

	//std::cout << "M_y: " << angle_y << std::endl;
	//std::cout << "M_x: " << angle_x << std::endl;
	//std::cout << "X: " << Input::Instance()->Get_Mouse_Position().x << "Y: " << Input::Instance()->Get_Mouse_Position().y << std::endl;

	if (Input::Instance()->Get_Key_Array()[23] == 1)
	{
		//std::cout << "d" << std::endl;
		Move_In_Direction(movespeed_input, 0, glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (Input::Instance()->Get_Key_Array()[21] == 1)
	{
		//std::cout << "a" << std::endl;
		Move_In_Direction(movespeed_input, 0, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (Input::Instance()->Get_Key_Array()[12] == 1)
	{
		//std::cout << "w" << std::endl;
		Move_In_Direction(movespeed_input, 0, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (Input::Instance()->Get_Key_Array()[22] == 1)
	{
		//std::cout << "s" << std::endl;
		Move_In_Direction(movespeed_input, 0, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	if (Input::Instance()->Get_Key_Array()[49] == 1)
	{
		//std::cout << "left shift" << std::endl;
		Move_In_Direction(movespeed_input, 1, glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}
	if (Input::Instance()->Get_Key_Array()[10] == 1)
	{
		//std::cout << "space" << std::endl;
		Move_In_Direction(movespeed_input, 1, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	}
	//std::cout << "X:" << CamPos.x << "Y:" << CamPos.y << "Z:" << CamPos.z << std::endl;
}

void Camera::Update()
{

	if (do_update_camera == 1)
	{

		//CamDir = glm::vec3(0, 0, 1);
		//CamDir = rotation_input_x * rotation_input_y * glm::vec4(CamDir, 1.0f);
		do_update_camera = 0;

	}


	view = glm::lookAt(CamPos, CamPos + CamDir, CamUp); // location, direction, orientation of camera
}