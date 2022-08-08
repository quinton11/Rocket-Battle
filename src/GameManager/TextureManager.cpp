#include "TextureManager.h"
#include "SDL_image.h"
#include "iostream"


SDL_Texture* TextureManager::loadTexture(std::string file, SDL_Renderer* renderer) {
	/*SDL_RWops* rwop = SDL_RWFromFile(file, "rb");
	SDL_Surface* img_surface = IMG_LoadPNG_RW(rwop);

	if (!img_surface) {
		std::cout << "Image Error: " << IMG_GetError() << std::endl;
	}

	//Creating texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img_surface);
	SDL_FreeSurface(img_surface);

	return texture;*/
	SDL_Texture* texture = NULL;
	SDL_Surface* img_surface = IMG_Load(file.c_str());

	if (img_surface == NULL)
		std::cout << "Unable to load image " << file.c_str() << " SDL Image ERROR: " << IMG_GetError();
	else {
		texture = SDL_CreateTextureFromSurface(renderer, img_surface);
		SDL_FreeSurface(img_surface);
	}
	return texture;
}

TextureManager::TextureManager(){
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {
		std::cout << "SDL Image could not be initialized! SDL Image Error: " << IMG_GetError();
	};
}

TextureManager::~TextureManager() {
	
}