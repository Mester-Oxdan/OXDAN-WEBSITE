/* A game of Checkers (2-players) */
#include <iostream>
#include <SDL2/SDL.h>

#include "includes/checkers/checkers_2/Square.h"
#include "all_diclarations.h"

// Define game state
static enum class GameState
{
	OUTLINE_CURRENT_PLAYER,
	SELECTING,
	SELECTED,
	MOVING,
};

// Define winning player or draw
static enum class Winner
{
	RED,
	BLACK,
	DRAW,
};

// Get index of a 1D 8 x 8 grid
static inline int getIndex(const int row, const int col)
{
	return 8 * row + col;
}

// Check out of bounds of 8 x 8 grid
static inline bool isOutOfBounds(const int row, const int col)
{
	if (row < 0 || col < 0 || row > 7 || col > 7) return true;
	else return false;
}

// Load texture and remove white background
static SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath)
{
	SDL_Texture* texture = nullptr;

	// Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(filePath);
	if (loadedSurface == nullptr)
	{
		//std::cout << "SDL could not load image into surface! Error: " << SDL_GetError() << std::endl;
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		cout << "(!SDL could not load image into surface! Error: " << SDL_GetError() << "!)\n";
		printf("\033[0;37m");
	}
	else
	{
		// Color key image (remove background/white)
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));

		// Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == nullptr)
		{
			//std::cout << "SDL could not create texture from surface! Error: " << SDL_GetError() << std::endl;
			printf("\033[0;31m");
			printf("\n");
			printf("(!ERROR!)");
			printf("\033[0;37m");
			printf(" = ");
			printf("\033[0;32m");
			cout << "(!SDL could not create texture from surface! Error: " << SDL_GetError() << "!)\n";
			printf("\033[0;37m");
		}

		// Free surface
		SDL_FreeSurface(loadedSurface);
	}

	return texture;
}

// Return prime checker
static CheckerType primeChecker(CheckerType checker)
{
	if (checker == CheckerType::RED || checker == CheckerType::KING_RED) return CheckerType::RED;
	else if (checker == CheckerType::BLACK || checker == CheckerType::KING_BLACK) return CheckerType::BLACK;
	else return checker;
}

// Return the opposite prime checker
static CheckerType oppositeChecker(CheckerType checker)
{
	if (checker == CheckerType::RED || checker == CheckerType::KING_RED) return CheckerType::BLACK;
	if (checker == CheckerType::BLACK || checker == CheckerType::KING_BLACK) return CheckerType::RED;
}

// Return true if arguments are opposite checkers
static bool areOppositeCheckers(CheckerType checker1, CheckerType checker2)
{
	if (checker1 == CheckerType::NONE || checker2 == CheckerType::NONE) return false;
	else if (oppositeChecker(checker1) != oppositeChecker(checker2)) return true;
	else return false;
}

// Define directions
static struct Direction
{
	int deltaRow;
	int deltaCol;
	Direction(int inDeltaRow, int inDeltaCol) : deltaRow(inDeltaRow), deltaCol(inDeltaCol) {}

}northWest(-1, -1), northEast(-1, 1), southWest(1, -1), southEast(1, 1);

// Use recursion to check in a specified direction
static void checkDirection(Square grid[], const Direction& direction, const CheckerType checker, const int row, const int col, const bool jumped)
{
	int nextRow = row + direction.deltaRow;
	int nextCol = col + direction.deltaCol;
	// Check square at direction is not out of bounds
	if (!isOutOfBounds(nextRow, nextCol))
	{
		Square* squareAtDirection = &grid[getIndex(nextRow, nextCol)];
		// If square at direction is a checker owned by the opponent
		if (areOppositeCheckers(checker, squareAtDirection->getChecker()))
		{
			int nextRow2 = row + 2 * direction.deltaRow;
			int nextCol2 = col + 2 * direction.deltaCol;
			// If the square after is not out of bounds
			if (!isOutOfBounds(nextRow2, nextCol2))
			{
				Square* nextSquareAtDirection = &grid[getIndex(nextRow2, nextCol2)];
				// If the next square at direction is empty and not highlighted as next possible position
				if (nextSquareAtDirection->getChecker() == CheckerType::NONE && nextSquareAtDirection->getHighlight() != HighlightType::NEXT_POSSIBLE_POSITION)
				{
					//std::cout << nextRow2 << ", " << nextCol2 << std::endl;

					// Set hightlight to next possible position
					nextSquareAtDirection->setHighlightTo(HighlightType::NEXT_POSSIBLE_POSITION);

					// Flag checker for possible removal
					nextSquareAtDirection->flagChecker(squareAtDirection);

					// Store the square would occur from
					nextSquareAtDirection->setPreviousSquare(&grid[getIndex(row, col)]);

					// Set possible directions
					Direction directions[4] = { northWest, northEast, southWest, southEast };

					// Recursively check the squares depending on the checker
					// If Red checker
					if (checker == CheckerType::RED)
					{
						// Check north west and north east
						for (int i = 0; i < 2; ++i) checkDirection(grid, directions[i], checker, nextRow2, nextCol2, true);
					}
					// else if black checker
					else if (checker == CheckerType::BLACK)
					{
						// Check south west and south east
						for (int i = 2; i < 4; ++i) checkDirection(grid, directions[i], checker, nextRow2, nextCol2, true);
					}
					// Else must be king checkers
					else
					{
						// Check all directions
						for (int i = 0; i < 4; ++i) checkDirection(grid, directions[i], checker, nextRow2, nextCol2, true);
					}
				}

				// else if next direction at square is the starting position (king checkers can come back to original position)
			}
		}
		// Else if square at direction is empty and no jumps have occured
		else if (squareAtDirection->getChecker() == CheckerType::NONE && !jumped)
		{
			squareAtDirection->setHighlightTo(HighlightType::NEXT_POSSIBLE_POSITION);
		}
	}

}

void handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:

			SDL_Quit();
			check_start_start();
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) {

				SDL_Quit();
				check_start_start();
			}
			break;
		default:
			break;
		}
	}
}

void checkers_2_start()
{
	// Define window dimensions
	const int windowWidth = 650;
	const int windowHeight = windowWidth;

	// Initalise SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		//std::cout << "SDL could not intialise! Error: " << SDL_GetError() << std::endl;
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		cout << "(!SDL could not intialise! Error: " << SDL_GetError() << "!)\n";
		printf("\033[0;37m");
	}
	handleEvents();
	// Create window
	SDL_Window* window = SDL_CreateWindow("Checkers for 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		//std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		cout << "(!SDL could not create window! Error: " << SDL_GetError() << "!)\n";
		printf("\033[0;37m");
	}

	// Create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr)
	{
		//std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
		printf("\033[0;31m");
		printf("\n");
		printf("(!ERROR!)");
		printf("\033[0;37m");
		printf(" = ");
		printf("\033[0;32m");
		cout << "(!SDL could not create renderer! Error: " << SDL_GetError() << "!)\n";
		printf("\033[0;37m");
	}

	// Set checker outline texture and remove white background
	//Checker::sOutline = loadTexture(renderer, "assets/Outline.bmp");

	// Load checker textures and remove white background
	//Checker::sTextureCache[(int)CheckerType::NONE] = loadTexture(renderer, "assets/Empty.bmp");
	string str1 = oxdan_dragon_c + "/includes/own/assets/RedChecker.bmp";
	string str2 = oxdan_dragon_c + "/includes/own/assets/BlackChecker.bmp";
	string str3 = oxdan_dragon_c + "/includes/own/assets/KingRedChecker.bmp";
	string str4 = oxdan_dragon_c + "/includes/own/assets/KingBlackChecker.bmp";
	Checker::sTextureCache[(int)CheckerType::RED] = loadTexture(renderer, str1.c_str());
	Checker::sTextureCache[(int)CheckerType::BLACK] = loadTexture(renderer, str2.c_str());
	Checker::sTextureCache[(int)CheckerType::KING_RED] = loadTexture(renderer, str3.c_str());
	Checker::sTextureCache[(int)CheckerType::KING_BLACK] = loadTexture(renderer, str4.c_str());

	// Define highlights (RGBA)
	Highlight::sColourCache[(int)HighlightType::NONE] = { 0, 0, 0, 0 };
	Highlight::sColourCache[(int)HighlightType::MOUSE_OVER] = { 94, 152, 235, 150 }; // blue
	Highlight::sColourCache[(int)HighlightType::MOVABLE] = { 255, 255, 255, 150 }; // white
	Highlight::sColourCache[(int)HighlightType::SELECTED] = { 94, 152, 235, 150 }; // blue
	Highlight::sColourCache[(int)HighlightType::NEXT_POSSIBLE_POSITION] = { 41, 242, 45, 120 }; // green

	// Set all the renderers
	Checker::sRenderer = renderer;
	Highlight::sRenderer = renderer;
	Square::sRenderer = renderer;

	// Create 8 x 8 grid of squares
	const int rows = 8;
	const int cols = 8;
	const int totalSquares = rows * cols;
	Square checkerboard[totalSquares];

	// Set two different coloured backgrounds (1 for each square and alternating at each square)
	SDL_Color backgrounds[2];
	backgrounds[0] = { 133, 71, 0, 255 };
	backgrounds[1] = { 230, 186, 127, 255 };

	// Define borders and derive the dimensions of squares
	const int borderThickness = 5;
	const int numberOfBorders = cols + 1;
	const int squareWidth = (windowWidth - numberOfBorders * borderThickness) / cols;
	const int squareHeight = squareWidth;

	// Define counters to keep track of checker placements
	int blackCounter = 12;
	int redCounter = 12;
	int flipCounter = 1;
	int index = 0;

	// Set all square starting positions, dimensions, checker placements, and background colours
	int squareStartY = borderThickness;
	for (int row = 0; row < rows; ++row)
	{
		int squareStartX = borderThickness;
		for (int col = 0; col < cols; ++col)
		{
			// Set location of square
			checkerboard[index].setLocation(row, col);

			// Alternate background colours
			flipCounter = 1 - flipCounter;
			checkerboard[index].setBackgroundColourTo(backgrounds[flipCounter]);

			// Set starting position and dimensions
			SDL_Rect rect = { squareStartX, squareStartY, squareWidth, squareHeight };
			checkerboard[index].setRectTo(rect);

			// Set black checker for top half of the board
			if (blackCounter > 0 && flipCounter)
			{
				checkerboard[index].setCheckerTo(CheckerType::BLACK);
				--blackCounter;
			}
			// Set red checker for bottom half of the board
			if (index > 39 && redCounter > 0 && flipCounter)
			{
				checkerboard[index].setCheckerTo(CheckerType::RED);
				--redCounter;
			}
			squareStartX += squareWidth + borderThickness;

			// Increment index
			++index;
		}
		flipCounter = 1 - flipCounter;
		squareStartY += squareHeight + borderThickness;
	}


	// Game loop variables
	bool stop = false;
	SDL_Event event;
	CheckerType currentPlayer = CheckerType::RED;
	GameState gameState = GameState::OUTLINE_CURRENT_PLAYER;
	bool render = true;
	Winner winner = Winner::DRAW;

	// Define counters to keep track of checkers removed
	int blackCheckers = 12;
	int redCheckers = 12;

	// Game loop
	while (!stop)
	{
		// Handle events
		while (SDL_PollEvent(&event) != 0)
		{
			// Handle quiting
			if (event.type == SDL_QUIT)
			{
				stop = true;
			}
			// Handle mouse events
			for (int i = 0; i < totalSquares; ++i)
			{
				// Moving state
				if (gameState == GameState::MOVING)
				{
					if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						// If square is highlighted to be a possible position to move current selected checker to
						if (checkerboard[i].getHighlight() == HighlightType::NEXT_POSSIBLE_POSITION)
						{
							if (checkerboard[i].isMouseInside())
							{
								// Get checker flagged
								Square* checkerFlagged = checkerboard[i].getCheckerFlagged();

								// Get previous square where the jump occured
								Square* previousSquare = checkerboard[i].getPreviousSquare();

								// Back track through the pointers of checkers flagged
								while (checkerFlagged != nullptr)
								{
									// Remove checker
									checkerFlagged->setCheckerTo(CheckerType::NONE);

									// Decrement number of checkers for opposite player
									if (currentPlayer == CheckerType::RED) --blackCheckers;
									else --redCheckers;

									// Get next checker flagged from previous square
									checkerFlagged = previousSquare->getCheckerFlagged();

									// Get new previous square
									previousSquare = previousSquare->getPreviousSquare();
								}

								// Check winner
								if (redCheckers == 0)
								{
									winner = Winner::BLACK;
									stop = true;
								}
								else if (blackCheckers == 0)
								{
									winner = Winner::RED;
									stop = true;
								}

								// Remove all flags and pointers to previous squares
								for (int i = 0; i < totalSquares; ++i)
								{
									checkerboard[i].flagChecker(nullptr);
									checkerboard[i].setPreviousSquare(nullptr);
								}

								// Get currently selected checker
								CheckerType checker = Square::sSelected->getChecker();

								// If red checker reaches other side of the board then turn it into a king red checker
								if (i > 0 && i < 8 && checker == CheckerType::RED)
								{
									checkerboard[i].setCheckerTo(CheckerType::KING_RED);
								}
								// If black checker reaches other side of the board then turn it into a king black checker
								else if (i > 55 && i < 64 && checker == CheckerType::BLACK)
								{
									checkerboard[i].setCheckerTo(CheckerType::KING_BLACK);
								}
								// Else set it to the current checker
								else
								{
									checkerboard[i].setCheckerTo(checker);
								}

								// Set the currently selected checker to none
								Square::sSelected->setCheckerTo(CheckerType::NONE);

								// Switch player
								currentPlayer = oppositeChecker(currentPlayer);

								// Clear all previous highlighting
								for (int i = 0; i < totalSquares; ++i)
								{
									checkerboard[i].setHighlightTo(HighlightType::NONE);
								}

								// Set game state to outline current player
								gameState = GameState::OUTLINE_CURRENT_PLAYER;

								// Set render
								render = true;

							}
						}
					}
				}
				// Selecting state or already moving
				if (gameState == GameState::SELECTING || gameState == GameState::MOVING)
				{
					if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						// If checker is player or its king varient
						if ((checkerboard[i].getChecker() == currentPlayer || checkerboard[i].getChecker() == (CheckerType)((int)currentPlayer + 2)))
						{
							if (checkerboard[i].isMouseInside())
							{
								if (Square::sSelected != &checkerboard[i])
								{
									Square::sSelected = &checkerboard[i];
									gameState = GameState::SELECTED;
								}
							}
						}
					}
				}
			}
		}

		// If selecting state
		if (gameState == GameState::OUTLINE_CURRENT_PLAYER)
		{
			// Add outline to the current players' checkers
			for (int i = 0; i < totalSquares; ++i)
			{
				if (primeChecker(checkerboard[i].getChecker()) == currentPlayer)
				{
					checkerboard[i].setShowOutlineTo(true);
				}
				else
				{
					checkerboard[i].setShowOutlineTo(false);
				}
			}

			// Set render
			render = true;

			// Change game state to selecting
			gameState = GameState::SELECTING;
		}

		// If a square has been selected
		if (gameState == GameState::SELECTED)
		{
			// Clear all previous highlighting
			for (int i = 0; i < totalSquares; ++i)
			{
				checkerboard[i].setHighlightTo(HighlightType::NONE);
			}

			// Highlight the currently selected square
			Square::sSelected->setHighlightTo(HighlightType::SELECTED);

			// Get location of currently selected square
			int row;
			int col;
			Square::sSelected->getLocation(&row, &col);

			// Get currently selected checker
			CheckerType checker = Square::sSelected->getChecker();

			// Set possible directions
			Direction directions[4] = { northWest, northEast, southWest, southEast };

			// If red checker
			if (checker == CheckerType::RED)
			{
				// Check north west and north east
				for (int i = 0; i < 2; ++i) checkDirection(checkerboard, directions[i], checker, row, col, false);
			}
			// If black checker
			else if (checker == CheckerType::BLACK)
			{
				// Check south west and south east
				for (int i = 2; i < 4; ++i) checkDirection(checkerboard, directions[i], checker, row, col, false);
			}
			// Else must be king checkers
			else
			{
				// Check all directions
				for (int i = 0; i < 4; ++i) checkDirection(checkerboard, directions[i], checker, row, col, false);
			}

			// Set game state to moving
			gameState = GameState::MOVING;

			// Set render flag
			render = true;
		}

		// Render only when a checker has moved or highlighting needs to be shown
		if (render)
		{
			// Clear screen to black
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);

			// Render checkerboard
			for (int i = 0; i < totalSquares; ++i)
			{
				checkerboard[i].renderSquare();
			}

			// Update screen from backbuffer and clear backbuffer
			SDL_RenderPresent(renderer);

			// Reset render flag
			render = false;
		}

		// Slow down program
		SDL_Delay(10);

	}

	// Display winner to console
	if (winner == Winner::RED) std::cout << "\n\033[0;31m!RED \033[0;33mWIN\033[0;37m!" << std::endl;
	else if (winner == Winner::BLACK) std::cout << "\n!BLACK \033[0;33mWIN\033[0;37m!" << std::endl;
	else std::cout << "\n!\033[0;33mDRAW\033[0;37m!" << std::endl;

	// Free outline texture
	SDL_DestroyTexture(Checker::sOutline);
	Checker::sOutline = nullptr;

	// Free highlight textures
	for (int i = 0; i < Checker::sTotalTextures; ++i)
	{
		SDL_DestroyTexture(Checker::sTextureCache[i]);
		Checker::sTextureCache[i] = nullptr;
	}

	// Destroy renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	// Quit SDL
	SDL_Quit();
	check_start_start();

}