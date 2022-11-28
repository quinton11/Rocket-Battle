#include "HomeScreen.h"
#include "iostream"

// SDL_Texture* HomeScreen::screentexture = textm.loadTexture("textures/universe.png", renderer);
void HomeScreen::render(SDL_Renderer *renderer, int screenW, int screenH)
{
	// SDL_RenderClear(renderer);
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
			// std::cout << "After event checker" << std::endl;

			// Render Image to window
			SDL_RenderCopy(renderer, screentexture, NULL, NULL);
			// SDL_RenderCopy(renderer, play, NULL, &play_rect);
			/*
			Have a pointer to current mounted sub-screen
			if no mounted sub screen, pointer to sub screen object would have
			a false ismounted flag, if false then renderMenu else render mounted sub screen
			 */
			// std::cout << "Before render menu" << std::endl;

			renderMenu(renderer, screenW, screenH);
			// std::cout << "After render menu" << std::endl;

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
			//(*activeMenu).buttons[0].
			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "start")
				{
					// std::cout << "In start" << std::endl;

					(*b)->rect = startRect;
					// Create text
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				else if ((*b)->name == "settings")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = settingsRect;
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				else if ((*b)->name == "quit")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = quitRect;
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
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
		// std::cout << "Start menu is active" << std::endl;
		float newplayerby = my + initdist;
		float selectplayerby = newplayerby + bh + ydist;
		float highscoreby = selectplayerby + bh + ydist;
		float backby = highscoreby + bh + ydist;
		// std::cout << "Start Menu" << std::endl;
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
					// std::cout << "In start" a<< std::endl;

					(*b)->rect = newplayerRect;
					// Create text
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				else if ((*b)->name == "Select Player")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = selectplayerRect;
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				else if ((*b)->name == "High Score")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = highscoreRect;
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				else if ((*b)->name == "Back")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = backRect;
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				++b;
			}
			(*activeMenu).set = true;
			// std::cout << "Now set" << std::endl;
		}
		// Rendering
		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			if ((*b)->name == "New Player")
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
			//(*activeMenu).buttons[0].
			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "Play")
				{
					// std::cout << "In start" << std::endl;

					(*b)->rect = playRect;
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				else if ((*b)->name == "Settings")
				{
					// std::cout << "In settings" << std::endl;

					(*b)->rect = settingsRect;
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				else if ((*b)->name == "Back")
				{
					// std::cout << "In quit" << std::endl;
					(*b)->rect = backRect;
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
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
						std::cout << "To settings" << std::endl;
						// subScreen->setName("Settings");
						// subScreen->setIsMounted(true);
						mS.setName("Settings");
						mS.isMtd = true;
						break;
						// std::cout << "In settings" << std::endl;
					}
					else if ((*b)->name == "quit")
					{
						// std::cout << "In quit" << std::endl;
						ismounted = false;
						quit = true;
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
					std::cout << (*b)->name << " -- Clicked" << std::endl;
					if ((*b)->name == "New Player")
					{
						// std::cout << "In start" << std::endl;
						// subScreen->setName("New Player");
						// subScreen->setIsMounted(true);
						mS.setName("New Player");
						mS.isMtd = true;
						break;
					}
					else if ((*b)->name == "Select Player")
					{
						// std::cout << "In settings" << std::endl;
						// subScreen->setName("Select Player");
						// subScreen->setIsMounted(true);
						mS.setName("Select Player");
						mS.isMtd = true;
						break;
					}
					else if ((*b)->name == "High Score")
					{
						// std::cout << "In quit" << std::endl;
						std::cout << "Before mS setname" << std::endl;
						mS.name = "High Score";
						std::cout << "After mS setname" << std::endl;

						mS.isMtd = true;

						break;
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
	else if ((*activeMenu).name == Play.name)
	{
		for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
		{
			(*b)->isActive = false;

			if (mouse_in_play(mouse_x, mouse_y, (*b)->rect))
			{
				(*b)->isActive = true;

				std::cout << "In button: " << (*b)->name << std::endl;
				if (isClicked)
				{
					std::cout << (*b)->name << " -- Clicked" << std::endl;
					if ((*b)->name == "Play")
					{
						// std::cout << "In start" << std::endl;
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
					}
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
	SDL_Texture *play = textm.loadTexture("textures/gamepad.png", renderer);

	selffont = font;
	std::cout << "Inside HomeScreen" << std::endl;
	//*subScreen = SubScreen(font);
	std::cout << "After subscreen init" << std::endl;
	MinScreen ms = MinScreen();
	mS = ms;
	mS.setfont(font);
	activeMenu = &mainM;
	std::cout << "After active menu" << std::endl;
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

bool MinScreen::mouse_in_play(int &x, int &y, SDL_FRect &rect)
{
	return (x >= rect.x) && (y >= rect.y) &&
		   (x < rect.x + rect.w) && (y < rect.y + rect.h);
}

void MinScreen::setName(std::string n) { name = n; }
void MinScreen::setfont(TTF_Font *f) { font = f; }
void MinScreen::eventChecker(bool &im, bool &quit)
{
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
		case SDL_QUIT:
			std::cout << "SDL QUIT event" << std::endl;
			im = false;
			quit = true;

		case SDL_MOUSEMOTION:
			mx = events.motion.x;
			my = events.motion.y;
			inButton(false);

		case SDL_MOUSEBUTTONDOWN:
			if (events.button.button == SDL_BUTTON_LEFT)
			{
				std::cout << "Left Click in Sub Screen: " << name << std::endl;
				// mouse_in_play(true);
				inButton(true);
				// call inbutton function
				// Per the name of the menu, it checks if a button has been clicked
			}
		}
	}
}

void MinScreen::inButton(bool isClicked)
{
	// check if mouse is in button
	// If mouse is in back button
	isActive = false;
	if (mouse_in_play(mx, my, backButton))
	{
		isActive = true;
		// hover
		if (isClicked)
		{
			std::cout << "Back Button clicked" << std::endl;
			isMtd = false;
			isActive = false;
		}
	}
	// need to have locations of each button
	// common button is the back button
	// then we have the create player button
	// then select player buttons where user is shown a list of players and highscore
	// also implement highlight on hover
}
void MinScreen::render(SDL_Renderer *r, int sW, int sH)
{
	// event checker
	// eventChecker(im, quit);
	//  render necessaries based on name
	if (name == "New Player")
	{
		// render new player screen
		renderNewPlayer(r, sW, sH);
	}
	else if (name == "Select Player")
	{
		// render select player screen
		renderSelectPlayer(r, sW, sH);
	}
	else if (name == "High Score")
	{
		// render High Score screen
		renderHS(r, sW, sH);
	}
	else if (name == "Settings")
	{
		renderSettings(r, sW, sH);
	}
	SDL_RenderPresent(r);
}
void MinScreen::renderNewPlayer(SDL_Renderer *r, int sW, int sH)
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen
	SDL_FRect backbutton = {20, 20, 50, 30};

	if (!backTextSet)
	{
		SDL_Texture *texture;
		std::string text = "Back";
		SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
		texture = SDL_CreateTextureFromSurface(r, surf);
		SDL_FreeSurface(surf);
		SDL_Texture *backt = texture;

		// hover
		surf = TTF_RenderText_Blended(font, text.c_str(), {255, 0, 0});
		texture = SDL_CreateTextureFromSurface(r, surf);
		SDL_FreeSurface(surf);
		backtext = backt;
		backtextH = texture;
		backTextSet = true;
		backButton = backbutton;
	}
	if (isActive)
	{
		SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
	}
	else
	{
		SDL_RenderCopyF(r, backtext, nullptr, &backButton);
	}
}
void MinScreen::renderSelectPlayer(SDL_Renderer *r, int sW, int sH)
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen
	// a back button at the top left corner
	// back button
	// x=20,y=20,w=50,h=30
	SDL_FRect backbutton = {20, 20, 50, 30};

	if (!backTextSet)
	{
		SDL_Texture *texture;
		std::string text = "Back";
		SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
		texture = SDL_CreateTextureFromSurface(r, surf);
		SDL_FreeSurface(surf);

		// hover
		SDL_Texture *backt = texture;
		surf = TTF_RenderText_Blended(font, text.c_str(), {255, 0, 0});
		texture = SDL_CreateTextureFromSurface(r, surf);
		SDL_FreeSurface(surf);
		backtext = backt;
		backtextH = texture;
		backTextSet = true;
		backButton = backbutton;
	}
	if (isActive)
	{
		SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
	}
	else
	{
		SDL_RenderCopyF(r, backtext, nullptr, &backButton);
	}
	// std::cout << "Render" << std::endl;
}
void MinScreen::renderHS(SDL_Renderer *r, int sW, int sH)
{
	// std::cout << "Render High Scores" << std::endl;
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen
	// a back button at the top left corner
	// back button
	// x=20,y=20,w=50,h=30
	SDL_FRect backbutton = {20, 20, 50, 30};

	if (!backTextSet)
	{
		SDL_Texture *texture;
		std::string text = "Back";
		SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
		texture = SDL_CreateTextureFromSurface(r, surf);
		SDL_FreeSurface(surf);
		SDL_Texture *backt = texture;

		// hover
		surf = TTF_RenderText_Blended(font, text.c_str(), {255, 0, 0});
		texture = SDL_CreateTextureFromSurface(r, surf);
		SDL_FreeSurface(surf);
		backtext = backt;
		backtextH = texture;
		backTextSet = true;
		backButton = backbutton;
	}
	if (isActive)
	{
		SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
	}
	else
	{
		SDL_RenderCopyF(r, backtext, nullptr, &backButton);
	}
}
void MinScreen::renderSettings(SDL_Renderer *r, int sW, int sH)
{
	// std::cout << "Render Settings" << std::endl;
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen
	// a back button at the top left corner
	// back button
	// x=20,y=20,w=50,h=30
	SDL_FRect backbutton = {20, 20, 50, 30};

	if (!backTextSet)
	{
		SDL_Texture *texture;
		std::string text = "Back";
		SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
		texture = SDL_CreateTextureFromSurface(r, surf);
		SDL_FreeSurface(surf);
		SDL_Texture *backt = texture;
		backtext = backt;
		backTextSet = true;
		backButton = backButton;
	}
	if (isActive)
	{
		SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
	}
	else
	{
		SDL_RenderCopyF(r, backtext, nullptr, &backButton);
	}
}
