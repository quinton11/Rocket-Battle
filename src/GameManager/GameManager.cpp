#include "gamemanager.h"
#include "iostream"
#include "..\Entities\Rocket.h"
#include "TextureManager.h"
#include "..\Screens\HomeScreen.h"
#include "..\Utils\TimeSetting.h"
#include "..\Controllers\KeyBoardHandler.h"
#include "..\Entities\Enemy.h"
#include "..\Entities\BulletManager.h"
#include "..\Entities\EnemyManager.h"

GameManager *GameManager::gmInstance = NULL;

GameManager *GameManager::instance()
{
	if (gmInstance == NULL)
		gmInstance = new GameManager();

	return gmInstance;
}

void GameManager::release()
{
	delete gmInstance;
	gmInstance = NULL;
}

GameManager::~GameManager()
{
	GameGraphics::release();
	KeyboardHandler::release();
	nGraphics = NULL;
}

void GameManager::Run()
{
	// --- TEXTURES ---
	// Rocket object
	Rocket rocket = Rocket();
	TextureManager txman = TextureManager();
	SDL_Texture *texture = txman.loadTexture("textures/rockblue.png", nGraphics->getrenderer());
	SDL_Texture *screen_texture = txman.loadTexture("textures/bgArtboard.png", nGraphics->getrenderer());

	// Enemy ships
	SDL_Texture *e_text = txman.loadTexture("textures/rock3-up.png", nGraphics->getrenderer());
	SDL_Texture *sb_text = txman.loadTexture("textures/rock2-up.png", nGraphics->getrenderer());
	SDL_Texture *wv_text = txman.loadTexture("textures/Asset1.png", nGraphics->getrenderer());

	// Bullets
	SDL_Texture *laser_text = txman.loadTexture("textures/laser.png", nGraphics->getrenderer());
	SDL_Texture *sniper_text = txman.loadTexture("textures/laser24.png", nGraphics->getrenderer());
	SDL_Texture *kb_text = txman.loadTexture("textures/laser64.png", nGraphics->getrenderer());


	/*
	Spawn enemy ships to attack player rocket. Enemy ships number should be able to be updated
	by ROcket depending on the level.

	Add bullet shooting mechanism for rocket when 'b' is pressed. Bullets should be small and indefinite for now
	*/
	BulletManager *bm = BulletManager::getBMInstance();
	EnemyManager em = EnemyManager(e_text, sb_text, wv_text);

	//Enemy attributes
	bm->setTextures(laser_text,sniper_text,kb_text);
	bm->setEnemyList(em.enemyships);

	HomeScreen homescreen = HomeScreen(nGraphics->getrenderer());
	KeyboardHandler *kb_handler = KeyboardHandler::instance();

	// TimeSetting
	TimeSetting tset = TimeSetting();

	float dt; // deltaTime
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	while (!isDone)
	{

		// Deltatime
		dt = tset.getDeltaTime();

		if (homescreen.getismounted())
		{
			homescreen.render(nGraphics->getrenderer());
		}

		else if (!homescreen.getismounted() && homescreen.getisquit())
		{
			isDone = true;
		}

		else
		{
			// std::cout<<"Starting Loop"<<std::endl;

			// keyboard input
			kb_handler->keyboard_input(state, &rocket, dt);
			// std::cout<<"After keyboard input"<<std::endl;

			// single hit keys
			//
			// SDL Poll Event logs every event in some sort of ds .

			// Check event queue to exeute events
			kb_handler->keyboard_events(nevents, isDone, &rocket, bm);
			// std::cout<<"Keyboard events"<<std::endl;

			SDL_RenderClear(nGraphics->getrenderer());
			// std::cout<<"Clearing Renderer"<<std::endl;
			//  Renderscreen
			nGraphics->render(screen_texture);
			// std::cout<<"Rendering Screen"<<std::endl;

			// Render rocket

			rocket.render(nGraphics->getrenderer(), texture, dt);
			// std::cout<<"Rendering rocket"<<std::endl;
			em.render(nGraphics->getrenderer(), rocket, dt, nGraphics->window_width, nGraphics->window_height);
			// std::cout<<"Enemy Manager render"<<std::endl;

			// ship.render(nGraphics->getrenderer(), e_text, rocket, dt);
			bm->render(nGraphics->getrenderer(), dt, nGraphics->window_width, nGraphics->window_height);
			// std::cout<<"Bullet Manager render"<<std::endl;

			// Updating screen
			SDL_RenderPresent(nGraphics->getrenderer());
			// std::cout<<"Render Present"<<std::endl;
		}
	}
}

GameManager::GameManager()
{

	isDone = false;

	nGraphics = GameGraphics::getInstance();

	if (!GameGraphics::getInitialized())
		isDone = true;
}