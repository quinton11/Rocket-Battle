#include "HomeScreen.h"
#include "iostream"

// SDL_Texture* HomeScreen::screentexture = textm.loadTexture("textures/universe.png", renderer);
void HomeScreen::render(SDL_Renderer *renderer, int screenW, int screenH)
{

	SDL_Texture *play = textm.loadTexture("textures/gamepad.png", renderer);
	while (ismounted)
	{
		// Check events
		HomeScreen::eventchecker();
		// Render Image to window
		SDL_RenderCopy(renderer, screentexture, NULL, NULL);
		// SDL_RenderCopy(renderer, play, NULL, &play_rect);
		renderMenu(renderer, screenW, screenH);
		SDL_RenderPresent(renderer);

		/*
		TODO:
			- Render main menu with play, settings and quit buttons
			- sub menu in play menu which renders when play is clicked
			- under play menu, have a new player button, select player button if players exist
			- and back button.
			- under new player button have a text entry field for entering new player's name
			- when new player is added move to select a player menu
			- under select a player's menu we display the existing players and their high score
			- user can toggle through and select a player
			- after selecting, user presses enter and menu changes to start
			- start menu has start game button and back
			- when start game is clicked, user moves into game
		 */
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
	SDL_RenderFillRectF(renderer, &menuContainer);

	SDL_FRect startRect;
	SDL_FRect settingsRect;
	SDL_FRect quitRect;

	float bw = 120;
	float bh = 30;
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
			//(*activeMenu).buttons[0].
			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "start")
				{
					// std::cout << "In start" << std::endl;

					(*b)->rect = startRect;
					// Create text
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {0, 0, 0});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);
					// read in font
					// use font to create texture
					// create start rect text texture and assign to rect
				}
				else if ((*b)->name == "settings")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = settingsRect;
				}
				else if ((*b)->name == "quit")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = quitRect;
				}
				++b;
			}
			(*activeMenu).set = true;
			// std::cout << "Now set" << std::endl;
		}
		// Rendering
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRectF(renderer, &(start->rect));
		SDL_RenderCopyF(renderer, start->text, NULL, &(start->rect));
		SDL_RenderFillRectF(renderer, &(settings->rect));
		SDL_RenderFillRectF(renderer, &(mquit->rect));
	}

	// position buttons
	// render buttons
	else if ((*activeMenu).name == Start.name)
	{
		// std::cout << "Start menu is active" << std::endl;
		float newplayerby = my + initdist;
		float selectplayerby = newplayerby + bh + ydist;
		float highscoreby = selectplayerby + bh + ydist;
		float backby = highscoreby + bh + ydist;

		if (!(*activeMenu).set)
		{
			// std::cout << "Not set" << std::endl;
			//  start,settings,quit
			SDL_FRect newplayerRect = {bx, newplayerby, bw, bh};
			SDL_FRect selectplayerRect = {bx, selectplayerby, bw, bh};
			SDL_FRect highscoreRect = {bx, highscoreby, bw, bh};
			SDL_FRect backRect = {bx, backby, bw, bh};
			//(*activeMenu).buttons[0].
			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "New Player")
				{
					// std::cout << "In start" << std::endl;

					(*b)->rect = newplayerRect;
				}
				else if ((*b)->name == "Select Player")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = selectplayerRect;
				}
				else if ((*b)->name == "High Score")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = highscoreRect;
				}
				else if ((*b)->name == "Back")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = backRect;
				}
				++b;
			}
			(*activeMenu).set = true;
			// std::cout << "Now set" << std::endl;
		}
		// Rendering
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRectF(renderer, &(newPlayer->rect));
		SDL_RenderFillRectF(renderer, &(selectPlayer->rect));
		SDL_RenderFillRectF(renderer, &(highScore->rect));
		SDL_RenderFillRectF(renderer, &(back->rect));
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
			//(*activeMenu).buttons[0].
			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "Play")
				{
					// std::cout << "In start" << std::endl;

					(*b)->rect = playRect;
				}
				else if ((*b)->name == "Settings")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = settingsRect;
				}
				else if ((*b)->name == "Back")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = backRect;
				}
				++b;
			}
			(*activeMenu).set = true;
			// std::cout << "Now set" << std::endl;
		}
		// Rendering
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRectF(renderer, &(play->rect));
		SDL_RenderFillRectF(renderer, &(msettings->rect));
		SDL_RenderFillRectF(renderer, &(pback->rect));
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
			// if there is a mouse motion we check in the active menus buttons for which
			// button the mouse's coordinates is in,then we set the isactive flag which triggers
			// a color change
			// so using the mouse in play function we can check which button the mouse is in

		case SDL_MOUSEBUTTONDOWN:
			// std::cout << "Mouse clicker" << std::endl;
			//&& HomeScreen::mouse_in_play(mouse_x, mouse_y, play_rect)
			if (events.button.button == SDL_BUTTON_LEFT)
			{
				inButton(true);
				// if mouse left button is clicked.
				// check for active menu
				// if active menu is main menu then we check which button in its buttons was the mouse in
				// then we trigger the buttons selected flag and change the menus active state to the
				// subsequent one.
				// Ex if start was clicked, we toggle the main menu to false and start to true
				// std::cout << "Start game clicked" << std::endl;
				// ismounted = false;
			}
		}
	}
}

void HomeScreen::inButton(bool isClicked)
{
	// Check if mouse coords is in active menus buttons
	if ((*activeMenu).name == mainM.name)
	{
		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			// toggle isactive to false
			if (mouse_in_play(mouse_x, mouse_y, (*b)->rect))
			{
				// toggle isactive to true
				// std::cout << "In button: " << (*b)->name << std::endl;
				// if isclicked is true
				if (isClicked)
				{
					std::cout << (*b)->name << " -- Clicked" << std::endl;
					if ((*b)->name == "start")
					{
						// std::cout << "In start" << std::endl
						activeMenu = &Start;
						std::cout << "To start screen" << std::endl;
						break;
					}
					else if ((*b)->name == "settings")
					{
						// std::cout << "In settings" << std::endl;
					}
					else if ((*b)->name == "quit")
					{
						// std::cout << "In quit" << std::endl;
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
			if (mouse_in_play(mouse_x, mouse_y, (*b)->rect))
			{
				// std::cout << "In button: " << (*b)->name << std::endl;
				if (isClicked)
				{
					std::cout << (*b)->name << " -- Clicked" << std::endl;
					if ((*b)->name == "New Player")
					{
						// std::cout << "In start" << std::endl;
					}
					else if ((*b)->name == "Select Player")
					{
						// std::cout << "In settings" << std::endl;
					}
					else if ((*b)->name == "High Score")
					{
						// std::cout << "In quit" << std::endl;
					}
					else if ((*b)->name == "Back")
					{
						// std::cout << "In quit" << std::endl;
						activeMenu = &mainM;
						std::cout << "Back to Main Menu" << std::endl;
						break;
					}
				}
			}
			++b;
		}
	}
	if ((*activeMenu).name == Play.name)
	{
		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			if (mouse_in_play(mouse_x, mouse_y, (*b)->rect))
			{
				std::cout << "In button: " << (*b)->name << std::endl;
				if (isClicked)
				{
					std::cout << (*b)->name << " -- Clicked" << std::endl;
				}
			}
			++b;
		}
	}
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

HomeScreen::HomeScreen(SDL_Renderer *renderer, TTF_Font *font)
{
	screentexture = textm.loadTexture("textures/amongus2.png", renderer);
	selffont = font;
	activeMenu = &mainM;
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