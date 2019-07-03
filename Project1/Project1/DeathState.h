#ifndef DEATHSTATE_H
#define DEATHSTATE_H

#include "GameState.h"
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"

//
#include <vector>

#include "GameObject.h"
//#include "cube_object.h"
#include "Ship.h"
#include "Grid.h"
#include "Quad.h"
#include "SkyBox.h"
#include "Text.h"
#include "Light.h"
#include "Model.h"
#include "Asteroid.h"
//

class DeathState : public GameState
{
public:
	DeathState(GameState* input_prev_state, int input_final_score);

	~DeathState();

	void Load_Scores();

	virtual void Update();
	virtual void Render();
	virtual void Init();

	static const int NUM_OF_OPTIONS = 2;

private:

	Camera MyCamera;

	Texture New_Highscore_Texture;
	Sprite Highscore_Alert;

	Texture Text_Texture[NUM_OF_OPTIONS];
	Sprite Option[NUM_OF_OPTIONS];

	bool is_higher_score = 0;
	int final_score = 0;
	int high_scores[5];

	const std::string SCORES_DIR = "Assets/Data/Scores.txt";


};


#endif