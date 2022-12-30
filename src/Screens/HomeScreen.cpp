#include "HomeScreen.h"
#include "iostream"

// SDL_Texture* HomeScreen::screentexture = textm.loadTexture("textures/universe.png", renderer);
bool HomeScreen::ismounted = true;
bool HomeScreen::quit = false;
void HomeScreen::render(SDL_Renderer *renderer, int screenW, int screenH)
{
	SDL_RenderClear(renderer);
	// std::cout << "Before gamepad texture" << std::endl;
	// SDL_Texture *play = textm.loadTexture("textures/gamepad.png", renderer);
	while (ismounted)
	{
		// std::cout << "Inside ismounted" << std::endl;

		// Check events
		if (mS.isMtd)
		{
			//
			mS.eventChecker(ismounted, quit);
			mS.render(renderer, screenW, screenH);
		}
		else
		{
			HomeScreen::eventchecker();

			// Render Image to window
			SDL_RenderCopy(renderer, screentexture, NULL, NULL);

			renderMenu(renderer, screenW, screenH);

			SDL_RenderPresent(renderer);
		}
	}
}

void HomeScreen::renderMenu(SDL_Renderer *renderer, int screenW, int screenH)
{
	float mw = 300;
	float mh = screenH / 2;
	float mx = screenW / 2 - mw / 2;
	float my = mh;
	SDL_FRect menuContainer = {mx, my, mw, mh};
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	// SDL_RenderFillRectF(renderer, &menuContainer);

	SDL_FRect startRect;
	SDL_FRect settingsRect;
	SDL_FRect quitRect;

	float bw = 100;
	float bh = 25;
	float bx = (mx + mw / 2) - bw / 2; //- button's width
	float initdist = 50;			   // Initial vertical distance btwn first button and container
	float ydist = 10;				   // vertical distance between buttons

	// start,settings,quit

	if ((*activeMenu).name == mainM.name)
	{
		float startby = my + initdist;
		float settingsby = startby + bh + ydist;
		float quitby = settingsby + bh + ydist;

		if (!(*activeMenu).set)
		{
			SDL_FRect startRect = {bx, startby, bw, bh};
			SDL_FRect settingsRect = {bx, settingsby, bw, bh};
			SDL_FRect quitRect = {bx, quitby, bw, bh};
			std::pair<SDL_Texture *, SDL_Texture *> textPair;
			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "start")
				{
					// std::cout << "In start" << std::endl;

					(*b)->rect = startRect;
					// Create text
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				else if ((*b)->name == "settings")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = settingsRect;
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				else if ((*b)->name == "quit")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = quitRect;
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				++b;
			}
			(*activeMenu).set = true;
			// std::cout << "Now set" << std::endl;
		}
		// Rendering
		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			if ((*b)->name == "start")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(start->rect));
					SDL_RenderCopyF(renderer, start->text, nullptr, &(start->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(start->rect));
					SDL_RenderCopyF(renderer, start->hovertext, nullptr, &(start->rect));
				}
			}
			else if ((*b)->name == "settings")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(settings->rect));
					SDL_RenderCopyF(renderer, settings->text, nullptr, &(settings->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(settings->rect));
					SDL_RenderCopyF(renderer, settings->hovertext, nullptr, &(settings->rect));
				}
			}
			else if ((*b)->name == "quit")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(mquit->rect));
					SDL_RenderCopyF(renderer, mquit->text, nullptr, &(mquit->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(mquit->rect));
					SDL_RenderCopyF(renderer, mquit->hovertext, nullptr, &(mquit->rect));
				}
			}

			b++;
		}
	}

	// position buttons
	// render buttons
	else if ((*activeMenu).name == Start.name)
	{
		if (mS.playerSelected)
		{
			activeMenu = &Play;
			mS.playerSelected = false;
			return;
		}
		// std::cout << "Start menu is active" << std::endl;
		float startbuttonby = my + initdist;
		float newplayerby = startbuttonby + bh + ydist;
		float selectplayerby = newplayerby + bh + ydist;
		float highscoreby = selectplayerby + bh + ydist;
		float backby = highscoreby + bh + ydist;
		// std::cout << "Start Menu" << std::endl;
		if (!(*activeMenu).set)
		{
			// std::cout << "Not set" << std::endl;
			//  start,settings,quit
			SDL_FRect startbuttonRect = {bx, startbuttonby, bw, bh};
			SDL_FRect newplayerRect = {bx, newplayerby, bw, bh};
			SDL_FRect selectplayerRect = {bx, selectplayerby, bw, bh};
			SDL_FRect highscoreRect = {bx, highscoreby, bw, bh};
			SDL_FRect backRect = {bx, backby, bw, bh};
			std::pair<SDL_Texture *, SDL_Texture *> textPair;

			//(*activeMenu).buttons[0].
			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "Arcade")
				{
					// std::cout << "In start" a<< std::endl;

					(*b)->rect = startbuttonRect;
					// Create text
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				else if ((*b)->name == "New Player")
				{
					// std::cout << "In start" a<< std::endl;

					(*b)->rect = newplayerRect;
					// Create text
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				else if ((*b)->name == "Select Player")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = selectplayerRect;
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				else if ((*b)->name == "High Score")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = highscoreRect;
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				else if ((*b)->name == "Back")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = backRect;
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				++b;
			}
			(*activeMenu).set = true;
			// std::cout << "Now set" << std::endl;
		}
		// Rendering
		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			if ((*b)->name == "Arcade")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(newPlayer->rect));
					SDL_RenderCopyF(renderer, startButton->text, nullptr, &(startButton->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(newPlayer->rect));
					SDL_RenderCopyF(renderer, startButton->hovertext, nullptr, &(startButton->rect));
				}
			}
			else if ((*b)->name == "New Player")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(newPlayer->rect));
					SDL_RenderCopyF(renderer, newPlayer->text, nullptr, &(newPlayer->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(newPlayer->rect));
					SDL_RenderCopyF(renderer, newPlayer->hovertext, nullptr, &(newPlayer->rect));
				}
			}
			else if ((*b)->name == "Select Player")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(selectPlayer->rect));
					SDL_RenderCopyF(renderer, selectPlayer->text, nullptr, &(selectPlayer->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(selectPlayer->rect));
					SDL_RenderCopyF(renderer, selectPlayer->hovertext, nullptr, &(selectPlayer->rect));
				}
			}
			else if ((*b)->name == "High Score")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(highScore->rect));
					SDL_RenderCopyF(renderer, highScore->text, nullptr, &(highScore->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(highScore->rect));
					SDL_RenderCopyF(renderer, highScore->hovertext, nullptr, &(highScore->rect));
				}
			}
			else if ((*b)->name == "Back")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(back->rect));
					SDL_RenderCopyF(renderer, back->text, nullptr, &(back->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(back->rect));
					SDL_RenderCopyF(renderer, back->hovertext, nullptr, &(back->rect));
				}
			}

			b++;
		}
	}
	else if ((*activeMenu).name == Play.name)
	{
		// std::cout << "Play menu is active" << std::endl;
		float playby = my + initdist;
		float settingsby = playby + bh + ydist;
		float backby = settingsby + bh + ydist;

		if (!(*activeMenu).set)
		{
			// std::cout << "Not set" << std::endl;
			//  start,settings,quit
			SDL_FRect playRect = {bx, playby, bw, bh};
			SDL_FRect settingsRect = {bx, settingsby, bw, bh};
			SDL_FRect backRect = {bx, backby, bw, bh};
			std::pair<SDL_Texture *, SDL_Texture *> textPair;

			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "Play")
				{
					// std::cout << "In start" << std::endl;

					(*b)->rect = playRect;
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				else if ((*b)->name == "Settings")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = settingsRect;
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				else if ((*b)->name == "Back")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = backRect;
					textPair = getTextPairR(renderer, (*b)->name, (*b)->rect);
					(*b)->rect.x = (mx + mw / 2) - (*b)->rect.w / 2;

					(*b)->text = textPair.first;
					// hover
					(*b)->hovertext = textPair.second;
				}
				++b;
			}
			(*activeMenu).set = true;
			// std::cout << "Now set" << std::endl;
		}
		// Rendering

		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			if ((*b)->name == "Play")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(play->rect));
					SDL_RenderCopyF(renderer, play->text, nullptr, &(play->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(play->rect));
					SDL_RenderCopyF(renderer, play->hovertext, nullptr, &(play->rect));
				}
			}
			else if ((*b)->name == "Settings")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(msettings->rect));
					SDL_RenderCopyF(renderer, msettings->text, nullptr, &(msettings->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(msettings->rect));
					SDL_RenderCopyF(renderer, msettings->hovertext, nullptr, &(msettings->rect));
				}
			}
			else if ((*b)->name == "Back")
			{
				if (!(*b)->isActive)
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(pback->rect));
					SDL_RenderCopyF(renderer, pback->text, nullptr, &(pback->rect));
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
					// SDL_RenderFillRectF(renderer, &(pback->rect));
					SDL_RenderCopyF(renderer, pback->hovertext, nullptr, &(pback->rect));
				}
			}

			b++;
		}
	}
}

void HomeScreen::eventchecker()
{
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
		case SDL_QUIT:
			ismounted = false;
			quit = true;
			// SDL_Quit();
			break;

		case SDL_MOUSEMOTION:
			mouse_x = events.motion.x;
			mouse_y = events.motion.y;
			inButton(false);

		case SDL_MOUSEBUTTONDOWN:
			if (events.button.button == SDL_BUTTON_LEFT)
			{
				inButton(true);
			}
		}
	}
}

void HomeScreen::inButton(bool isClicked)
{
	// Check if mouse coords is in active menus buttons
	// check if theres a mounted sub screen
	// if no run below if checks, if yes, run if checks for current sub screen
	if ((*activeMenu).name == mainM.name)
	{
		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			(*b)->isActive = false;
			// toggle isactive to false
			if (mouse_in_play(mouse_x, mouse_y, (*b)->rect))
			{
				// toggle isactive to true
				// std::cout << "In button: " << (*b)->name << std::endl;
				// if isclicked is true
				(*b)->isActive = true;

				if (isClicked)
				{
					// std::cout << (*b)->name << " -- Clicked" << std::endl;
					Mix_PlayChannel(2, SoundManager::menu_change, 0);

					if ((*b)->name == "start")
					{
						// std::cout << "In start" << std::endl
						// SoundManager::menu_change
						activeMenu = &Start;
						// std::cout << "To start screen" << std::endl;
						break;
					}
					else if ((*b)->name == "settings")
					{
						std::cout << "To settings" << std::endl;

						mS.setName("Settings");
						mS.isMtd = true;
						break;
					}
					else if ((*b)->name == "quit")
					{
						// std::cout << "In quit" << std::endl;
						ismounted = false;
						quit = true;
						break;
					}
				}
				// check button name and trigger next menu accordingly
			}
			++b;
		}
	}
	else if ((*activeMenu).name == Start.name)
	{

		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			(*b)->isActive = false;

			if (mouse_in_play(mouse_x, mouse_y, (*b)->rect))
			{
				// std::cout << "In button: " << (*b)->name << std::endl;
				(*b)->isActive = true;

				if (isClicked)
				{
					// std::cout << (*b)->name << " -- Clicked" << std::endl;
					Mix_PlayChannel(2, SoundManager::menu_change, 0);

					if ((*b)->name == "Arcade")
					{

						activeMenu = &Play;
						// std::cout << "To play screen" << std::endl;
						break;
					}
					else if ((*b)->name == "New Player")
					{

						mS.setName("New Player");
						mS.isMtd = true;
						// SDL_StartTextInput();
						break;
					}
					else if ((*b)->name == "Select Player")
					{

						mS.setName("Select Player");
						mS.isMtd = true;
						mS.matchPlayers();
						break;
					}
					else if ((*b)->name == "High Score")
					{
						// std::cout << "In quit" << std::endl;
						// std::cout << "Before mS setname" << std::endl;
						mS.name = "High Score";
						// std::cout << "After mS setname" << std::endl;

						mS.isMtd = true;

						break;
					}
					else if ((*b)->name == "Back")
					{
						// std::cout << "In quit" << std::endl;
						activeMenu = &mainM;
						// std::cout << "Back to Main Menu" << std::endl;
						break;
					}
				}
			}
			++b;
		}
	}
	else if ((*activeMenu).name == Play.name)
	{
		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			(*b)->isActive = false;

			if (mouse_in_play(mouse_x, mouse_y, (*b)->rect))
			{
				(*b)->isActive = true;

				if (isClicked)
				{
					// std::cout << (*b)->name << " -- Clicked" << std::endl;
					Mix_PlayChannel(2, SoundManager::menu_change, 0);

					if ((*b)->name == "Play")
					{
						// std::cout << "In start" << std::endl;
						if (Mix_PlayingMusic())
						{
							Mix_FadeOutMusic(2000);
							//Mix_PauseMusic();
						}
						ismounted = false;
						activeMenu = &Start;
						FileManager::playerScore = 0;
						// std::cout << FileManager::currentPlayer << " " << FileManager::currentScore << std::endl;
						break;
					}
					else if ((*b)->name == "Settings")
					{
						// std::cout << "In settings" << std::endl;
						mS.setName("Settings");
						mS.isMtd = true;
						break;
					}
					else if ((*b)->name == "Back")
					{
						// std::cout << "In quit" << std::endl;
						activeMenu = &Start;
						break;
					}
				}
			}
			++b;
		}
	}
}

std::pair<SDL_Texture *, SDL_Texture *> HomeScreen::getTexturePair(SDL_Renderer *r, std::string nm)
{
	SDL_Surface *surf;
	SDL_Texture *texture;
	SDL_Texture *htexture;
	surf = TTF_RenderText_Blended(selffont, nm.c_str(), {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(r, surf);
	SDL_FreeSurface(surf);

	// hover
	SDL_Surface *surfh = TTF_RenderText_Blended(selffont, nm.c_str(), {255, 0, 0});
	htexture = SDL_CreateTextureFromSurface(r, surfh);
	SDL_FreeSurface(surfh);

	std::pair<SDL_Texture *, SDL_Texture *> res = std::pair<SDL_Texture *, SDL_Texture *>(texture, htexture);
	return res;
}

std::pair<SDL_Texture *, SDL_Texture *> HomeScreen::getTextPairR(SDL_Renderer *r, std::string nm, SDL_FRect &dest)
{
	SDL_Surface *surf;
	SDL_Texture *texture;
	SDL_Texture *hovtexture;
	std::pair<SDL_Texture *, SDL_Texture *> res;

	surf = TTF_RenderText_Blended(TextureManager::font, nm.c_str(), {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(r, surf);
	dest.w = surf->w - 20;
	dest.h = surf->h - 20;
	SDL_FreeSurface(surf);

	// hover
	surf = TTF_RenderText_Blended(TextureManager::font, nm.c_str(), {255, 0, 0});
	hovtexture = SDL_CreateTextureFromSurface(r, surf);
	SDL_FreeSurface(surf);
	res = std::pair<SDL_Texture *, SDL_Texture *>(texture, hovtexture);
	return res;
}

// Check if mouse is on play button
bool HomeScreen::mouse_in_play(int &x, int &y, SDL_FRect &rect)
{
	return (x >= rect.x) && (y >= rect.y) &&
		   (x < rect.x + rect.w) && (y < rect.y + rect.h);
}

bool HomeScreen::getismounted()
{
	return ismounted;
}

bool HomeScreen::getisquit()
{
	return quit;
}

void HomeScreen::setismounted(bool is)
{
	ismounted = is;
}

void HomeScreen::release()
{
	// main menu
	delete start;
	delete settings;
	delete mquit;
	start = nullptr;
	settings = nullptr;
	mquit = nullptr;

	// start menu
	delete startButton;
	delete newPlayer;
	delete selectPlayer;
	delete highScore;
	delete back;
	startButton = nullptr;
	newPlayer = nullptr;
	selectPlayer = nullptr;
	highScore = nullptr;
	back = nullptr;
	// play menu
	delete play;
	delete msettings;
	delete pback;
	play = nullptr;
	msettings = nullptr;
	pback = nullptr;
}

HomeScreen::HomeScreen(SDL_Renderer *renderer, TTF_Font *font)
{
	screentexture = textm.loadTexture("textures/amongus2.png", renderer);
	SDL_Texture *play = textm.loadTexture("textures/gamepad.png", renderer);

	selffont = font;
	MinScreen ms = MinScreen();
	mS = ms;
	mS.setfont(font);
	activeMenu = &mainM;
	// std::cout << "After active menu" << std::endl;
}

HomeScreen::HomeScreen()
{
	// assigning main Menu to active menu
	// activeMenu = &Start;
}

// Destructor releasing pointers
HomeScreen::~HomeScreen()
{
	// delete screentexture;
	// delete events;

	screentexture = NULL;
}

/*
	Add player records which is saved in a file database
	Database is secure and hidden to prevent altering
	When game is started, player can select player from list of registered players
	or player can create a new player
	When new player is created, player then moves to game screen with theplayer
	created as the current player in use. High SCore is accumulated as game goes on
	When player stops game or dies or quits, game score is cross checked with player High
	Score. If game score is greater, that becomes the player's high score and is saved.
 */