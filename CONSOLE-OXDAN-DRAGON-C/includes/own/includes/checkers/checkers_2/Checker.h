/* A class to represent a checker */
#pragma once
#include <SDL2/SDL.h>

// Define checker types
enum class CheckerType
{
	NONE,
	RED,
	BLACK,
	KING_RED,
	KING_BLACK,
};

class Checker
{
public:
	// Define renderer
	static SDL_Renderer* sRenderer;

	// Create a static array to store the checker textures
	static const int sTotalTextures = 5;
	static SDL_Texture* sTextureCache[sTotalTextures];

	// Define checker outline texture
	static SDL_Texture* sOutline;

private:
	// Define type of checker
	CheckerType mCheckerType;

	// Define checker texture and its parameters
	SDL_Rect mRect;
	SDL_Texture* mTexture;

	// Define outline dimension, positions, and a flag
	SDL_Rect mOutlineRect;
	bool mShowOutline;

public:
	// Constructor
	Checker();

	// Set checker type and get checker
	void setCheckerTo(CheckerType checkerType);
	CheckerType getChecker();

	// Center checker and outline texture on square
	void centerTextureOn(const SDL_Rect& squareRect);

	// Set show outline flag
	void setShowOutlineTo(const bool showOutline);

	// Render checker
	void renderChecker();
	
};

