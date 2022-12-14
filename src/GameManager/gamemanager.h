#pragma once
#include "GGraphics.h"
#include "FileManager.h"

class GameManager
{

private:
	static GameManager *gmInstance;
	GameGraphics *nGraphics;

	bool isDone;
	SDL_Event nevents;

public:
	static GameManager *instance();
	static void release();

	void Run();
	void resetEntities();

private:
	GameManager();
	~GameManager();
};