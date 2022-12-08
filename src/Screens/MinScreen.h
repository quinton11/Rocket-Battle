#pragma once
#include "Screen.h"
#include <string>
#include "list"
#include "SDL_ttf.h"
#include "..\GameManager\FileManager.h"

struct Button
{
	std::string name;
	bool isActive;
	bool isSelected;
	SDL_FRect rect;
	SDL_FRect dest;
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
	std::list<Button> playerButtons;
	Button *selectedB = nullptr;
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
	void setSelectedPButton(Button &b);
	void matchPlayerButtons(SDL_Renderer *r);
	void matchPlayerScoreDisplay(SDL_Renderer *r, int sW, int sH);
	void addPlayer();
	void movetoplay();
	void renderPlayersScroll(SDL_Renderer *r, float offset, int sW, int sH);
	std::pair<SDL_Texture *, SDL_Texture *> buttonText(SDL_Renderer *r, std::string nm, SDL_FRect &dest);
	std::pair<SDL_Texture *, SDL_Texture *> displayText(SDL_Renderer *r, std::string nm,std::string score, SDL_FRect &dest);

private:
	void renderNewPlayer(SDL_Renderer *r, int sW, int sH);
    void renderBackButton(SDL_Renderer *r);
	void renderSelectPlayer(SDL_Renderer *r, int sW, int sH);
	void renderHS(SDL_Renderer *r, int sW, int sH);
	void renderSettings(SDL_Renderer *r, int sW, int sH);
	void inButton(bool isClicked);
};