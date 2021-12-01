#pragma once
#include "SDL.h"

//For texture manager, on one instance of object, be able to load textures to be used by rendering
class TextureManager {

public:
	static SDL_Texture* loadTexture(const char* file, SDL_Renderer* renderer);

	TextureManager();
	~TextureManager();
};