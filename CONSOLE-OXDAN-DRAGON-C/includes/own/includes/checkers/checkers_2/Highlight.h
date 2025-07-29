/* A class to highlight a square*/
#pragma once
#include <SDL2/SDL.h>

// Define highlight types
enum class HighlightType
{
	NONE,
	MOUSE_OVER,
	MOVABLE,
	SELECTED,
	NEXT_POSSIBLE_POSITION,
};

class Highlight
{
public:
	// Define renderer
	static SDL_Renderer* sRenderer;

	// Create a static array to store colours
	static const int sTotalColours = 5;
	static SDL_Color sColourCache[sTotalColours];

private:
	// Define highlight type
	HighlightType mHighlightType;

	// Define colour
	SDL_Color* mColour;

	// Define area to highlight
	SDL_Rect mRect;

public:
	// Constructor
	Highlight();

	// Set area to highliht
	void setRectTo(const SDL_Rect& rect);

	// Set and get highlight
	void setHighlightTo(HighlightType highlightType);
	HighlightType getHighlight();

	// Render highlight
	void renderHighlight();
	
};