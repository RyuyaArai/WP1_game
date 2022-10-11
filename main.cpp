#include "GameSceneBase.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Framework* myGame = new GameSceneBase();
	
	myGame->Run();

	return 0;
}