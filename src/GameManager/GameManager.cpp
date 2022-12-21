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
#include "SDL_ttf.h"
#include "..\Screens\PauseScreen.h"
#include "..\Entities\StatDrawer.h"
#include "..\Entities\PowerUpManager.h"
#include "string"
// #include "LevelManager.h"

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
	/* std::string fp = "ab";
	char tb = 'a';
	fp += tb;
	std::cout << fp << std::endl; */
	// --- TEXTURES ---
	// Rocket object
	Rocket rocket = Rocket();
	std::string fontPath = "textures/fonts/Starjedi.ttf";

	TextureManager txman = TextureManager(fontPath);
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

	// StatDrawer
	SDL_Texture *sD = txman.loadTexture("textures/R3B.png", nGraphics->getrenderer());
	SDL_Texture *health = txman.loadTexture("textures/healthlogo.png", nGraphics->getrenderer());
	SDL_Texture *heart = txman.loadTexture("textures/redheart.png", nGraphics->getrenderer());

	SDL_Texture *lbolt = txman.loadTexture("textures/lbolt12.png", nGraphics->getrenderer());
	SDL_Texture *sun = txman.loadTexture("textures/sun12.png", nGraphics->getrenderer());
	SDL_Texture *hbgt = txman.loadTexture("textures/healthbg.png", nGraphics->getrenderer());
	SDL_Texture *hfgt = txman.loadTexture("textures/healthfg.png", nGraphics->getrenderer());
	SDL_Texture *shield = txman.loadTexture("textures/shield12.png", nGraphics->getrenderer());
	SDL_Texture *prect = txman.loadTexture("textures/rect8.png", nGraphics->getrenderer());

	/*
	Spawn enemy ships to attack player rocket. Enemy ships number should be able to be updated
	by ROcket depending on the level.

	Add bullet shooting mechanism for rocket when 'b' is pressed. Bullets should be small and indefinite for now
	*/
	BulletManager *bm = BulletManager::getBMInstance();
	EnemyManager em = EnemyManager(e_text, sb_text, wv_text);
	PowerUpManager pum = PowerUpManager();
	// LevelManager lm = LevelManager();

	// powerup
	pum.setReference(rocket);
	pum.addTextures(shield, lbolt, sun, heart);

	em.setReference(pum);

	// Enemy attributes
	bm->setTextures(laser_text, sniper_text, kb_text);
	bm->setEnemyList(em.enemyships);
	bm->setRocket(rocket);

	HomeScreen homescreen = HomeScreen(nGraphics->getrenderer(), TextureManager::font);
	PauseScreen pausescreen = PauseScreen();
	StatDrawer statDrawer = StatDrawer(hbgt, hfgt);
	statDrawer.setRocket(rocket);
	statDrawer.setTextures(health, lbolt, sun, shield, prect);
	// HomeScreen homescreen = HomeScreen(nGraphics->getrenderer());

	KeyboardHandler *kb_handler = KeyboardHandler::instance();

	// TimeSetting
	TimeSetting tset = TimeSetting();

	float dt; // deltaTime
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	while (!isDone)
	{

		// Deltatime
		// std::cout << "Started Loop" << std::endl;
		dt = tset.getDeltaTime();

		if (homescreen.getismounted())
		{
			// std::cout << "In home screen render" << std::endl;
			// clear bullet and enemy manager
			rocket.reset();
			bm->clearBullets();
			em.clearEShips();
			homescreen.render(nGraphics->getrenderer(), nGraphics->window_width, nGraphics->window_height);
			// std::cout << "After home screen render" << std::endl;
		}
		// else if(homescreen.getisquit()){}

		else if (!homescreen.getismounted() && homescreen.getisquit())
		{
			// std::cout << "Unmounted and Quit" << std::endl;
			FileManager::writeHS();
			isDone = true;
			homescreen.release();
		}

		else
		{
			// std::cout<<"Starting Loop"<<std::endl;
			SDL_RenderClear(nGraphics->getrenderer());

			// keyboard input
			kb_handler->keyboard_input(state, &rocket, dt);
			// std::cout<<"After keyboard input"<<std::endl;
			pausescreen.render(nGraphics->getrenderer(), nGraphics->window_width, nGraphics->window_height, rocket.gameOver());

			// single hit keys
			//
			// SDL Poll Event logs every event in some sort of ds .

			// Check event queue to exeute events
			kb_handler->keyboard_events(nevents, isDone, &rocket, bm);
			// std::cout<<"Keyboard events"<<std::endl;

			// std::cout<<"Clearing Renderer"<<std::endl;
			//   Renderscreen
			nGraphics->render(screen_texture);
			// std::cout<<"Rendering Screen"<<std::endl;

			// Render rocket

			rocket.render(nGraphics->getrenderer(), texture, dt);
			// std::cout<<"Rendering rocket"<<std::endl;
			em.render(nGraphics->getrenderer(), bm, rocket, dt, nGraphics->window_width, nGraphics->window_height);
			// std::cout<<"Enemy Manager render"<<std::endl;

			// Power up renderer
			pum.render(nGraphics->getrenderer());
			// ship.render(nGraphics->getrenderer(), e_text, rocket, dt);
			bm->render(nGraphics->getrenderer(), dt, nGraphics->window_width, nGraphics->window_height);
			// std::cout<<"Bullet Manager render"<<std::endl;
			statDrawer.render(nGraphics->getrenderer(), nGraphics->window_width, nGraphics->window_height, sD);

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
	FileManager::createInstance();
	// FileManager::readHS();

	if (!GameGraphics::getInitialized())
		isDone = true;
}

/*
	TODO:: Adjust menu buttons positioning Done
	Add player life deduction and game over
 */