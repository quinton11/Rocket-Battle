#include "HomeScreen.h"
#include "iostream"

// SDL_Texture* HomeScreen::screentexture = textm.loadTexture("textures/universe.png", renderer);
void HomeScreen::render(SDL_Renderer *renderer, int screenW, int screenH)
{
	SDL_RenderClear(renderer);

	SDL_Texture *play = textm.loadTexture("textures/gamepad.png", renderer);
	while (ismounted)
	{
		// Check events
		// if (subScreen->getIsMounted())
		//{
		//
		//	subScreen->render(renderer, ismounted, quit, screenW, screenH);
		//}
		// else
		//{
		HomeScreen::eventchecker();
		// Render Image to window
		SDL_RenderCopy(renderer, screentexture, NULL, NULL);
		// SDL_RenderCopy(renderer, play, NULL, &play_rect);
		/*
		Have a pointer to current mounted sub-screen
		if no mounted sub screen, pointer to sub screen object would have
		a false ismounted flag, if false then renderMenu else render mounted sub screen
		 */
		renderMenu(renderer, screenW, screenH);
		SDL_RenderPresent(renderer);
		//}
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
					// query texture for width and height
					/* int tw;
					int th;
					SDL_QueryTexture(nullptr, nullptr, nullptr, &tw, &th);
					int tx = ((*b)->rect.x + (*b)->rect.w / 2) - tw / 2;
					int ty = (*b)->rect.y + 2;
					(*b)->trect = {tx, ty, tw, th}; */

					// populate text rect
					//  read in font
					//  use font to create texture
					//  create start rect text texture and assign to rect
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
		/* SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRectF(renderer, &(start->rect));
		// SDL_RenderCopy(renderer, start->text, NULL, &(start->trect));
		SDL_RenderCopyF(renderer, start->text, nullptr, &(start->rect)); */
		/* SDL_RenderFillRectF(renderer, &(settings->rect));
		SDL_RenderCopyF(renderer, settings->text, NULL, &(settings->rect)); */

		/* SDL_RenderFillRectF(renderer, &(mquit->rect));
		SDL_RenderCopyF(renderer, mquit->text, NULL, &(mquit->rect)); */
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
		/* SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRectF(renderer, &(newPlayer->rect));
		SDL_RenderCopyF(renderer, newPlayer->text, nullptr, &(newPlayer->rect)); */

		/* SDL_RenderFillRectF(renderer, &(selectPlayer->rect));
		SDL_RenderCopyF(renderer, selectPlayer->text, nullptr, &(selectPlayer->rect)); */

		/* SDL_RenderFillRectF(renderer, &(highScore->rect));
		SDL_RenderCopyF(renderer, highScore->text, nullptr, &(highScore->rect)); */

		/* SDL_RenderFillRectF(renderer, &(back->rect));
		SDL_RenderCopyF(renderer, back->text, nullptr, &(back->rect)); */
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
		/* SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRectF(renderer, &(play->rect));
		SDL_RenderCopyF(renderer, play->text, nullptr, &(play->rect)); */

		/* SDL_RenderFillRectF(renderer, &(msettings->rect));
		SDL_RenderCopyF(renderer, msettings->text, nullptr, &(msettings->rect)); */

		/* SDL_RenderFillRectF(renderer, &(pback->rect));
		SDL_RenderCopyF(renderer, pback->text, nullptr, &(pback->rect)); */
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
						break;
					}
					else if ((*b)->name == "Select Player")
					{
						// std::cout << "In settings" << std::endl;
						// subScreen->setName("Select Player");
						// subScreen->setIsMounted(true);
						break;
					}
					else if ((*b)->name == "High Score")
					{
						// std::cout << "In quit" << std::endl;
						// subScreen->setName("High Score");
						// subScreen->setIsMounted(true);
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
						// subScreen->setName("Settings");
						// subScreen->setIsMounted(true);
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
	selffont = font;
	//*subScreen = SubScreen(selffont);
	//MinScreen ms = MinScreen();
	//mS = &ms;
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

void MinScreen::setName(std::string n) { name = n; }
void MinScreen::setfont(TTF_Font *f) { font = f; }
void MinScreen::eventChecker(bool &im, bool &quit) {}
void MinScreen::render(SDL_Renderer *r, bool &im, bool &quit, int sW, int sH) {}
void MinScreen::renderNewPlayer(SDL_Renderer *r, int sW, int sH)
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen
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
	}
	SDL_FRect backbutton = {20, 20, 50, 30};
	SDL_RenderCopyF(r, backtext, nullptr, &backbutton);
}
void MinScreen::renderSelectPlayer(SDL_Renderer *r, int sW, int sH)
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen
	// a back button at the top left corner
	// back button
	// x=20,y=20,w=50,h=30
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
	}
	SDL_FRect backbutton = {20, 20, 50, 30};
	SDL_RenderCopyF(r, backtext, nullptr, &backbutton);
}
void MinScreen::renderHighScores(SDL_Renderer *r, int sW, int sH)
{
	/* SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen
	// a back button at the top left corner
	// back button
	// x=20,y=20,w=50,h=30
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
	}
	SDL_FRect backbutton = {20, 20, 50, 30};
	SDL_RenderCopyF(r, backtext, nullptr, &backbutton); */
}
void MinScreen::renderSettings(SDL_Renderer *r, int sW, int sH) {}
