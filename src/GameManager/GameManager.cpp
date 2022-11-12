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

	// Rocket object
	Rocket rocket = Rocket();
	TextureManager txman = TextureManager();
	SDL_Texture *texture = txman.loadTexture("textures/rockblue.png", nGraphics->getrenderer());
	SDL_Texture *screen_texture = txman.loadTexture("textures/bgArtboard.png", nGraphics->getrenderer());

	// Enemy ship
	SDL_Texture *e_text = txman.loadTexture("textures/rockblue.png", nGraphics->getrenderer());
	SDL_Texture *laser_text = txman.loadTexture("textures/laser.png", nGraphics->getrenderer());
	// Enemy ship = Enemy();
	/*
	Spawn enemy ships to attack player rocket. Enemy ships number should be able to be updated
	by ROcket depending on the level.

	Add bullet shooting mechanism for rocket when 'b' is pressed. Bullets should be small and indefinite for now
	*/
	BulletManager *bm = BulletManager::getBMInstance();
	EnemyManager em = EnemyManager();

	//em.spawn(80,120); // test spawn
	//em.spawn(150,280);
	/*rwbgd1ed*/
	/*bgdraft1*/
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

			// keyboard input
			kb_handler->keyboard_input(state, &rocket, dt);

			// single hit keys
			//
			// SDL Poll Event logs every event in some sort of ds .

			// Check event queue to exeute events
			kb_handler->keyboard_events(nevents, isDone, &rocket, bm);

			SDL_RenderClear(nGraphics->getrenderer());
			// Renderscreen
			nGraphics->render(screen_texture);

			// Render rocket

			rocket.render(nGraphics->getrenderer(), texture, dt);
			em.render(nGraphics->getrenderer(), e_text, rocket, dt, nGraphics->window_width, nGraphics->window_height);
			// ship.render(nGraphics->getrenderer(), e_text, rocket, dt);
			bm->render(nGraphics->getrenderer(), laser_text, dt, nGraphics->window_width, nGraphics->window_height);

			// Updating screen
			SDL_RenderPresent(nGraphics->getrenderer());
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