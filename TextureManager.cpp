#include "TextureManager.h"
#include "SDL_image.h";
#include "iostream"


SDL_Texture* TextureManager::loadTexture(const char* file, SDL_Renderer* renderer) {
	SDL_RWops* rwop = SDL_RWFromFile(file, "rb");
	SDL_Surface* img_surface = IMG_LoadPNG_RW(rwop);

	if (!img_surface) {
		std::cout << "Image Error: " << IMG_GetError() << std::endl;
	}

	//Creating texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img_surface);
	SDL_FreeSurface(img_surface);

	return texture;
}

TextureManager::TextureManager(){
}

TextureManager::~TextureManager() {
	
}