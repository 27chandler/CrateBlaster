#ifndef MISSILE_H
#define MISSILE_H

#include "GameObject.h"
#include "Light.h"
class Missile :	public GameObject
{
public:
	Missile();
	~Missile();

	void Update();
	void Set_Null_Pos();
	void Shoot(glm::vec3 input_pos,glm::vec3 input_momentum);


private:

	float speed_multiplier = 0.6f;
	Light missile_light;

};

#endif