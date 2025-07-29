/* A Square class with colours and a texture */
#pragma once
#include <SDL2/SDL.h>

#include "Checker.h"
#include "Highlight.h"

class Square
{
public:
	// Define renderer
	static SDL_Renderer* sRenderer;

	// Define currently selected square
	static Square* sSelected;

private:
	// Store location of square on the checkerboard
	int mRow;
	int mCol;

	// Define position and dimensions of square
	SDL_Rect mRect;

	// Define checker
	Checker mChecker;
	
	// Define highlighting
	Highlight mHighlight;

	// Define background colour
	SDL_Color mBackgroundColour;

	// Flag a checker(square) for possible removal
	Square* mCheckerFlagged;

	// Keep a track of which square made the jump to flag the checker
	Square* mPreviousSquare;

public:
	// Constructor
	Square();

	// Set and get location of square on board
	void setLocation(const int row, const int col);
	void getLocation(int* row, int* col);

	// Set postion and dimensions of square;
	void setRectTo(SDL_Rect& rect);

	// Set background colour
	void setBackgroundColourTo(SDL_Color& colour);

	// Set checker and get checker
	void setCheckerTo(CheckerType checkerType);
	CheckerType getChecker();

	// Set highlight
	void setHighlightTo(HighlightType highlightType);
	HighlightType getHighlight();
	
	// Set show outline flag
	void setShowOutlineTo(const bool showOutline);

	// Render everything in that square
	void renderSquare();

	// Check if mouse is inside Square
	bool isMouseInside();

	// Flag and get checker for possible removal
	void flagChecker(Square* checker);
	Square* getCheckerFlagged();

	// Keep a track of which square made the jump to flag the checker
	void setPreviousSquare(Square* square);
	Square* getPreviousSquare();

};