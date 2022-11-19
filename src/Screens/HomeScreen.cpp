#include "HomeScreen.h"
#include "iostream"

// SDL_Texture* HomeScreen::screentexture = textm.loadTexture("textures/universe.png", renderer);
void HomeScreen::render(SDL_Renderer *renderer)
{

	SDL_Texture *play = textm.loadTexture("textures/gamepad.png", renderer);
	while (ismounted)
	{
		// Check events
		HomeScreen::eventchecker();
		// Render Image to window
		SDL_RenderCopy(renderer, screentexture, NULL, NULL);
		SDL_RenderCopy(renderer, play, NULL, &play_rect);
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

void HomeScreen::renderMenu(SDL_Renderer *renderer)
{
	// using screenwidth and screenheight calculate the x,y,w and h of the container
	// that will be a rect, render the rect.
	// Then we check which menu is active
	// if active menu pointer is not pointing to the active menu we point to it
	// then we point the activeButtons to its buttons
	// since its active we create their rects according to the structure
	// since its fixed we need not create it multiple times, we can create it and store in memory
	// Each button has same width height and x coordinates, y however differs depending on which button
	// follows which.
	// we create their rects in order, then their colours and render them
}

void HomeScreen::eventchecker()
{
	SDL_PollEvent(&events);
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
		// if there is a mouse motion we check in the active menus buttons for which
		// button the mouse's coordinates is in,then we set the isactive flag which triggers
		// a color change
		// so using the mouse in play function we can check which button the mouse is in

	case SDL_MOUSEBUTTONDOWN:
		// std::cout << "Mouse clicker" << std::endl;
		if (events.button.button == SDL_BUTTON_LEFT && HomeScreen::mouse_in_play(mouse_x, mouse_y, play_rect))
		{
			// if mouse left button is clicked.
			// check for active menu
			// if active menu is main menu then we check which button in its buttons was the mouse in
			// then we trigger the buttons selected flag and change the menus active state to the
			// subsequent one.
			// Ex if start was clicked, we toggle the main menu to false and start to true
			std::cout << "Start game clicked" << std::endl;
			ismounted = false;
		}
	}
}

// Check if mouse is on play button
bool HomeScreen::mouse_in_play(int &x, int &y, SDL_Rect &rect)
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

HomeScreen::HomeScreen(SDL_Renderer *renderer)
{
	screentexture = textm.loadTexture("textures/amongus2.png", renderer);
}

HomeScreen::HomeScreen() {}

// Destructor releasing pointers
HomeScreen::~HomeScreen()
{
	// delete screentexture;
	// delete events;

	screentexture = NULL;
}