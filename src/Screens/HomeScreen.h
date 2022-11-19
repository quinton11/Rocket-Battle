#pragma once
#include "Screen.h"
#include "..\GameManager\TextureManager.h"
#include <string>
#include "list"

struct Button
{
	std::string name;
	bool isActive;
	bool isSelected;
};

struct Menu
{
	std::string name;
	std::list<Button> buttons;
	bool active;
};

class HomeScreen : public Screen
{

public:
	TextureManager textm;
	// Main menu
	Button start = {"start", false, false};
	Button settings = {"settings", false, false};
	Button mquit = {"quit", false, false};
	Menu main = {"Main-Menu", {start, settings, mquit}, true};

	// Start menu
	Button newPlayer = {"New Player", false, false};
	Button selectPlayer = {"Select Player", false, false};
	Button highScore = {"High Score", false, false};
	Button back = {"Back", false, false};
	Menu Start = {"Start-Menu", {newPlayer, selectPlayer, highScore, back}, false};

	// Play Menu
	Button play = {"Play", false, false};
	Button msettings = {"Settings", false, false};
	Button pback = {"Back", false, false};
	Menu Play = {"Play-Menu", {play, msettings, pback}, false};

private:
	bool ismounted = true;
	std::list<Button> *activeButtons;
	Menu *activeMenu;
	bool quit = false;
	SDL_Texture *screentexture = nullptr;
	SDL_Event events;
	SDL_Rect play_rect = {250, 350, 70, 70};
	int mouse_x, mouse_y = 0;

public:
	void render(SDL_Renderer *renderer);
	void renderMenu(SDL_Renderer *renderer);
	void eventchecker();

	bool getismounted();
	bool getisquit();
	void setismounted(bool);
	bool mouse_in_play(int &x, int &y, SDL_Rect &rect);

	HomeScreen(SDL_Renderer *renderer);
	HomeScreen();
	~HomeScreen();
};
