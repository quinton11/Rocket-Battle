#include "TextureManager.h"
#include "SDL_image.h"
#include "iostream"

TTF_Font *TextureManager::font = nullptr;
SDL_Texture *TextureManager::loadTexture(std::string file, SDL_Renderer *renderer)
{
	/*SDL_RWops* rwop = SDL_RWFromFile(file, "rb");
	SDL_Surface* img_surface = IMG_LoadPNG_RW(rwop);

	if (!img_surface) {
		std::cout << "Image Error: " << IMG_GetError() << std::endl;
	}

	//Creating texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img_surface);
	SDL_FreeSurface(img_surface);

	return texture;*/
	// SDL_Texture *play = textm.loadTexture("textures/gamepad.png", renderer);
	// std::cout << "Before loading texture" << std::endl;
	SDL_Texture *texture = nullptr;
	// std::cout << "After null text init" << std::endl;

	SDL_Surface *img_surface = IMG_Load(file.c_str());
	// std::cout << "After loading texture" << std::endl;

	if (img_surface == NULL)
		std::cout << "Unable to load image " << file.c_str() << " SDL Image ERROR: " << IMG_GetError();
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, img_surface);
		SDL_FreeSurface(img_surface);
	}
	return texture;
}

TextureManager::TextureManager()
{
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		std::cout << "SDL Image could not be initialized! SDL Image Error: " << IMG_GetError();
	};
}
TextureManager::TextureManager(std::string fname)
{
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		std::cout << "SDL Image could not be initialized! SDL Image Error: " << IMG_GetError();
	};
	font = TTF_OpenFont(fname.c_str(), 25);
}

TextureManager::~TextureManager()
{
}