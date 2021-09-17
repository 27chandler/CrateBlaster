#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>

#include "Camera.h"
#include "GameObject.h"
#include "CubeObject.h"
#include "Ship.h"
#include "Grid.h"
#include "Quad.h"
#include "Texture.h"
#include "Skybox.h"
#include "Sprite.h"
#include "Text.h"
#include "Model.h"
#include "Asteroid.h"
#include "Light.h"
#include "Audio.h"

#include "GameState.h"
class PlayState : public GameState
{
public:
	PlayState(GameState* input_prev_state);

	~PlayState();

	virtual void Update();
	virtual void Render();
	virtual void Init();

	void InitDying();

	void InitPowerups();

	void InitScore();

	void SpawnShip();

	//void Save_Score();
	void Set_Powerup_Display(Texture* input_texture);

	static const int NUM_OF_SCORE_DISPLAYS = 4;
	static const int RAND_POWERUP_CHANCE = 20;
	static const int POWERUP_SCORE_AMOUNT = 600;

private:

	float movespeed = 0.05f;

private:
	void InitLights();
	void InitTextures();
	void InitAudio();
	void SpawnObstacles();
	void InitBorder();
	void InitSkybox();

	enum POWERUPS { NONE = 0, BOOST = 1 , SCORE = 2};

	Camera MyCamera;
	Skybox The_Sky;
	Skybox Arena_Border;

	Light Star_Light;

	Texture Crate_Texture;
	Texture Skybox_Texture;
	Texture Arena_Border_Texture;
	Texture Number_Texture;
	Texture Boost_Texture;
	Texture Score_Powerup_Texture;

	Audio Death_Sound;

	//quad Quad1;
	Sprite Score_Display[NUM_OF_SCORE_DISPLAYS];
	Sprite Powerup_Display;

	Text My_Text;

	//grid Main_Grid;
	std::vector <GameObject*> Objects;

	int score = 0;
	int score_timer = 0;

	const float ARENA_SIZE = 50.0f;
	const int RAND_NEW_ASTEROID_SPAWN = 7000;

	int powerup_type = 0;

	Ship* ship_ptr = nullptr;

};

#endif