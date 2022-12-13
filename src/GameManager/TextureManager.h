#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "iostream"

//For texture manager, on one instance of object, be able to load textures to be used by rendering
class TextureManager {

public:
	static SDL_Texture* loadTexture(std::string file, SDL_Renderer* renderer);
	static TTF_Font* font;
	/*const char**/

	TextureManager();
	TextureManager(std::string fname);
	~TextureManager();
};