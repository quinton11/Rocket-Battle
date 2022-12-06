#pragma once
#include "Screen.h"
#include "..\GameManager\TextureManager.h"
#include "..\GameManager\FileManager.h"
#include <string>
#include "list"
#include "SDL_ttf.h"

struct Button
{
	std::string name;
	bool isActive;
	bool isSelected;
	SDL_FRect rect;
	SDL_Texture *text;
	SDL_Texture *hovertext;
};

struct Menu
{
	std::string name;
	std::list<Button *> buttons;
	bool active;
	bool set;
};

struct MinScreen
{
	std::string name;
	int mx;
	int my;
	bool isMtd = false; // is mounted
	bool isActive = false;
	std::list<std::string> players;
	TTF_Font *font;
	SDL_Texture *backtext;
	SDL_Texture *backtextH;
	SDL_Texture *titleImage;
	SDL_Texture *textImage;
	std::string textInput;
	SDL_Event events;
	SDL_FRect backButton;
	SDL_FRect createPlayer;
	bool backTextSet = false;
	bool playerSelected = false;
	void setName(std::string n);
	void setfont(TTF_Font *f);
	void eventChecker(bool &im, bool &quit);
	void render(SDL_Renderer *r, int sW, int sH);
	void renderTitle(SDL_Renderer *r, int sW, int sH);
	void setBackText(SDL_Renderer *r);
	void renderInputBox(SDL_Renderer *r, int sW, int sH);
	bool mouse_in_play(int &x, int &y, SDL_FRect &rect);
	void matchPlayers();
	void addPlayer();
	void movetoplay();

private:
	void renderNewPlayer(SDL_Renderer *r, int sW, int sH);
	void renderSelectPlayer(SDL_Renderer *r, int sW, int sH);
	void renderHS(SDL_Renderer *r, int sW, int sH);
	void renderSettings(SDL_Renderer *r, int sW, int sH);
	void inButton(bool isClicked);
};

class HomeScreen : public Screen
{

public:
	TextureManager textm;
	// Main menu
	Button *start = new Button{"start", false, false};
	Button *settings = new Button{"settings", false, false};
	Button *mquit = new Button{"quit", false, false};
	Menu mainM = {"Main-Menu", {start, settings, mquit}, true, false};

	// Start menu
	Button *startButton = new Button{"Start-Button", false, false};
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
	bool ismounted = true;
	std::list<Button> *activeButtons;
	Menu *activeMenu;
	bool quit = false;
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

	HomeScreen(SDL_Renderer *renderer, TTF_Font *font);
	// HomeScreen(SDL_Renderer *renderer);

	HomeScreen();
	~HomeScreen();

private:
	void inButton(bool isClicked);
};
