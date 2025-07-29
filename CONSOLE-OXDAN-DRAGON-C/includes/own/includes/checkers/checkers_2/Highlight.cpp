#include "Highlight.h"

SDL_Renderer* Highlight::sRenderer = nullptr;
SDL_Color Highlight::sColourCache[sTotalColours];

Highlight::Highlight()
	:mHighlightType(HighlightType::NONE), mColour(&sColourCache[(int)mHighlightType]), mRect({0, 0, 0, 0})
{

}

void Highlight::setRectTo(const SDL_Rect& rect)
{
	mRect = rect;
}

void Highlight::setHighlightTo(HighlightType highlightType)
{
	mHighlightType = highlightType;
	mColour = &sColourCache[(int)highlightType];
}

HighlightType Highlight::getHighlight()
{
	return mHighlightType;
}

void Highlight::renderHighlight()
{
	// Only render highlight if square is not empty
	if (mHighlightType != HighlightType::NONE)
	{
		SDL_SetRenderDrawBlendMode(sRenderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(sRenderer, mColour->r, mColour->g, mColour->b, mColour->a);
		SDL_RenderFillRect(sRenderer, &mRect);
	}

}
