#ifndef MENUSTATE_H
#define MENUSTATE_H

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

class MenuState : public GameState
{
public:
	MenuState(GameState* input_prev_state);

	~MenuState();

	void Load_Scores();

	virtual void Update();
	virtual void Render();
	virtual void Init();

	static const int NUM_OF_OPTIONS = 2;
	static const int NUM_OF_SCORE_DISPLAYS = 4;
	static const int NUM_OF_HIGHSCORES = 5;

private:

	const std::string SCORES_DIR = "Assets/Data/Scores.txt";

	enum MENU_OPTIONS { START = 1, QUIT = 0 };

	Camera MyCamera;

	int high_scores[5];

	Texture Text_Texture[NUM_OF_OPTIONS];
	Sprite Option[NUM_OF_OPTIONS];

	Texture Highscore_Texture;
	Sprite Highscore_Indicator;

	Texture Arrow_Texture;
	Sprite Arrow;

	Texture Number_Texture;
	Sprite Score_Display[NUM_OF_HIGHSCORES][NUM_OF_SCORE_DISPLAYS];


	glm::vec3 arrow_pos;

	int selection = 0;

	bool iskeydown = false;



};

#endif