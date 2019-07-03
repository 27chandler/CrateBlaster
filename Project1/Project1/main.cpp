#include "GameManager.h"

#include <SDL.h>


int main(int argc, char* args[])
{
	TheGame::Instance()->Init();
	TheGame::Instance()->Update();
	TheGame::Instance()->Shutdown();

	return 0;
}