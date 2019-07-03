#ifndef ASTEROID_H
#define ASTEROID_H

#include "GameObject.h"

#include "Missile.h"

class Asteroid : public GameObject
{
public:
	Asteroid(float input_arena_size);

public:

	void Update();
	bool Check_If_Shot(Missile* input_missile_array, int input_max_missiles);

	void Set_Collision_Distance(float input_distance) { collision_distance = input_distance; };
	float Get_Collision_Distance() { return collision_distance; };

	void Shrink_And_Spin();

	

private:
	float ARENA_SIZE = 0.0f;
	const float SHRINK_AMOUNT = 4.0f;
	float collision_distance = 1.0f;
	glm::vec3 random_rot;
	
};

#endif