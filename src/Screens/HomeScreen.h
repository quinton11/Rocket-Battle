#pragma once
#include "Screen.h"
#include "..\GameManager\TextureManager.h"
#include "..\GameManager\FileManager.h"
#include <string>
#include "list"
#include "SDL_ttf.h"
#include "MinScreen.h"


class HomeScreen : public Screen
{

public:
	TextureManager textm;
	static bool quit;
	static bool ismounted;


	// Main menu
	Button *start = new Button{"start", false, false};
	Button *settings = new Button{"settings", false, false};
	Button *mquit = new Button{"quit", false, false};
	Menu mainM = {"Main-Menu", {start, settings, mquit}, true, false};

	// Start menu
	Button *startButton = new Button{"Arcade", false, false};
	Button *newPlayer = new Button{"New Player", false, false};
	Button *selectPlayer = new Button{"Select Player", false, false};
	Button *highScore = new Button{"High Score", false, false};
	Button *back = new Button{"Back", false, false};
	Menu Start = {"Start-Menu", {startButton, newPlayer, selectPlayer, highScore, back}, false, false};

	// Play Menu
	Button *play = new Button{"Play", false, false};
	Button *msettings = new Button{"Settings", false, false};
	Button *pback = new Button{"Back", false, false};
	Menu Play = {"Play-Menu", {play, msettings, pback}, false, false};

private:
	std::list<Button> *activeButtons;
	Menu *activeMenu;
	SDL_Texture *screentexture = nullptr;
	SDL_Texture *playbutton = nullptr;
	SDL_Event events;
	SDL_FRect play_rect = {250, 350, 70, 70};
	int mouse_x, mouse_y = 0;
	TTF_Font *selffont;
	MinScreen mS;

public:
	void render(SDL_Renderer *renderer, int screenW, int screenH);
	void renderMenu(SDL_Renderer *renderer, int screenW, int screenH);
	void eventchecker();

	bool getismounted();
	bool getisquit();
	void setismounted(bool);
	void release();
	bool mouse_in_play(int &x, int &y, SDL_FRect &rect);
	std::pair<SDL_Texture*,SDL_Texture*> getTexturePair(SDL_Renderer* r,std::string nm);
    std::pair<SDL_Texture *, SDL_Texture *> getTextPairR(SDL_Renderer *r, std::string nm, SDL_FRect &dest);


	HomeScreen(SDL_Renderer *renderer, TTF_Font *font);
	

	HomeScreen();
	~HomeScreen();

private:
	void inButton(bool isClicked);
};
