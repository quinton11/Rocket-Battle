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
			//(*activeMenu).buttons[0].
			for (std::list<Button *>::iterator b = (*activeMenu).buttons.begin(); b != (*activeMenu).buttons.end();)
			{
				if ((*b)->name == "Start-Button")
				{
					// std::cout << "In start" a<< std::endl;

					(*b)->rect = startbuttonRect;
					// Create text
					SDL_Surface *surf = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 255, 255});
					(*b)->text = SDL_CreateTextureFromSurface(renderer, surf);
					SDL_FreeSurface(surf);

					// hover
					SDL_Surface *surfh = TTF_RenderText_Blended(selffont, ((*b)->name).c_str(), {255, 0, 0});
					(*b)->hovertext = SDL_CreateTextureFromSurface(renderer, surfh);
					SDL_FreeSurface(surfh);
				}
				else if ((*b)->name == "New Player")
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
			if ((*b)->name == "Start-Button")
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
					std::cout << (*b)->name << " -- Clicked" << std::endl;
					if ((*b)->name == "Start-Button")
					{

						activeMenu = &Play;
						std::cout << "To play screen" << std::endl;
						break;
					}
					else if ((*b)->name == "New Player")
					{
						// std::cout << "In start" << std::endl;
						// subScreen->setName("New Player");
						// subScreen->setIsMounted(true);
						mS.setName("New Player");
						mS.isMtd = true;
						// SDL_StartTextInput();
						break;
					}
					else if ((*b)->name == "Select Player")
					{
						// std::cout << "In settings" << std::endl;
						// subScreen->setName("Select Player");
						// subScreen->setIsMounted(true);
						mS.setName("Select Player");
						mS.isMtd = true;
						mS.matchPlayers();
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

				if (isClicked)
				{
					std::cout << (*b)->name << " -- Clicked" << std::endl;
					if ((*b)->name == "Play")
					{
						// std::cout << "In start" << std::endl;
						ismounted = false;
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

bool MinScreen::mouse_in_play(int &x, int &y, SDL_FRect &rect)
{
	return (x >= rect.x) && (y >= rect.y) &&
		   (x < rect.x + rect.w) && (y < rect.y + rect.h);
}

void MinScreen::setName(std::string n) { name = n; }
void MinScreen::setfont(TTF_Font *f) { font = f; }
void MinScreen::eventChecker(bool &im, bool &quit)
{
	int leng;
	while (SDL_PollEvent(&events))
	{
		switch (events.type)
		{
		case SDL_QUIT:
			std::cout << "SDL QUIT event" << std::endl;
			im = false;
			quit = true;
			break;

		case SDL_MOUSEMOTION:
			mx = events.motion.x;
			my = events.motion.y;
			inButton(false);
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (events.button.button == SDL_BUTTON_LEFT)
			{
				inButton(true);
			}
			break;

		case SDL_TEXTINPUT:
			if (name == "New Player")
			{
				// add to text input
				textInput += events.text.text;
				// std::cout << textInput << std::endl;
			}
			break;
		case SDL_KEYDOWN:
			if (name == "New Player")
			{
				switch (events.key.keysym.sym)
				{
				case SDLK_SPACE:
					// std::cout << "Space Bar hit" << std::endl;
					break;

				case SDLK_BACKSPACE:
					std::cout << "Back Space hit" << std::endl;
					leng = textInput.size();
					////std::cout << leng << std::endl;

					if (leng > 0)
					{
						textInput.pop_back();
					}
					break;

				case SDLK_RETURN:
					std::cout << "Enter hit" << std::endl;
					std::cout << textInput << std::endl;
					addPlayer();
					movetoplay();
					// textInput = "";
					//  create new player and move to play screen
					break;
				}
			}
			break;
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
			// std::cout << "Back Button clicked" << std::endl;
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

void MinScreen::addPlayer()
{
	// check if textname is not empty
	// if so then add it to the map of players
	// clear text
	if (textInput != "")
	{
		FileManager::writeHSM(textInput, 0);
		FileManager::currentPlayer = textInput;
		FileManager::currentScore = 0;
		textInput = "";
		playerSelected = true;
		return;
	}

	// if empty return and do nothing
	return;
}

void MinScreen::movetoplay()
{
	isMtd = false;
}

void MinScreen::setBackText(SDL_Renderer *r)
{
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
}

void MinScreen::renderTitle(SDL_Renderer *r, int sW, int sH)
{
	SDL_Surface *temps;
	SDL_FRect paget;

	temps = TTF_RenderText_Blended(font, name.c_str(), {255, 255, 255});
	if (temps)
	{
		titleImage = SDL_CreateTextureFromSurface(r, temps);
		paget.w = temps->w;
		paget.h = temps->h;
		paget.x = (float)(sW / 2) - paget.w / 2;
		paget.y = 40;
		SDL_FreeSurface(temps);
		temps = NULL;
	}
	SDL_RenderCopyF(r, titleImage, nullptr, &paget);
}

void MinScreen::renderInputBox(SDL_Renderer *r, int sW, int sH)
{
	SDL_FRect container;
	SDL_Surface *temps;
	SDL_FRect tinp;
	container.w = (float)(sW)-100;
	container.h = 50;
	container.x = (float)(sW / 2) - container.w / 2;
	container.y = 200;

	temps = TTF_RenderText_Blended(font, textInput.c_str(), {0, 0, 0});
	if (temps)
	{
		textImage = SDL_CreateTextureFromSurface(r, temps);
		tinp.w = temps->w;
		tinp.h = temps->h;
		tinp.x = (float)(sW / 2) - tinp.w / 2;
		tinp.y = 200;
		SDL_FreeSurface(temps);
		temps = NULL;
	}

	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
	SDL_RenderFillRectF(r, &container);
	SDL_RenderCopyF(r, textImage, nullptr, &tinp);
}
void MinScreen::renderNewPlayer(SDL_Renderer *r, int sW, int sH)
{

	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen
	SDL_FRect backbutton = {20, 20, 50, 30};

	setBackText(r);

	if (isActive)
	{
		SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
	}
	else
	{
		SDL_RenderCopyF(r, backtext, nullptr, &backButton);
	}
	// render page title at middle top
	renderTitle(r, sW, sH);
	renderInputBox(r, sW, sH);
	// after inputting,push name with highscore of 0 to the playerScores map when user has
	// created player
}
void MinScreen::renderSelectPlayer(SDL_Renderer *r, int sW, int sH)
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen

	setBackText(r);

	if (isActive)
	{
		SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
	}
	else
	{
		SDL_RenderCopyF(r, backtext, nullptr, &backButton);
	}
	renderTitle(r, sW, sH);
	// render list of players
	//list of players to create buttons

	// if size of playerScores is 0, render no player
	// else render all players
}
void MinScreen::renderHS(SDL_Renderer *r, int sW, int sH)
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen

	setBackText(r);

	if (isActive)
	{
		SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
	}
	else
	{
		SDL_RenderCopyF(r, backtext, nullptr, &backButton);
	}
	renderTitle(r, sW, sH);
	// if size of playerScores map is 0 render none
	// else render players and their scores
}
void MinScreen::renderSettings(SDL_Renderer *r, int sW, int sH)
{
	// std::cout << "Render Settings" << std::endl;
	SDL_SetRenderDrawColor(r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(r, NULL); // fill screen

	setBackText(r);

	if (isActive)
	{
		SDL_RenderCopyF(r, backtextH, nullptr, &backButton);
	}
	else
	{
		SDL_RenderCopyF(r, backtext, nullptr, &backButton);
	}
	renderTitle(r, sW, sH);
}

// Updates players list with FileManager::playerScores map
void MinScreen::matchPlayers()
{
	int sizeps = FileManager::playerScores.size();
	int sizep = players.size();
	std::string nm;
	if (sizeps == 0)
	{
		std::cout << "Zero players" << std::endl;
	}
	if (sizeps != sizep)
	{
		std::map<std::string, int>::iterator it;
		for (it = FileManager::playerScores.begin(); it != FileManager::playerScores.end(); it++)
		{
			nm = it->first;
			players.push_back(nm);
		}
	}
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