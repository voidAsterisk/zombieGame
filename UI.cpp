/* TODO: Render HUD. */
#include "UI.h"


void UI::AddKill()
{
	killcount++;
}
int UI::getkillcount()
{
	return killcount;
}

void UI::Render(std::shared_ptr< SDL_Renderer > ren)
{
<<<<<<< HEAD
	auto ss = std::stringstream (std::stringstream::in | std::stringstream::out);

=======
	std::stringstream ss (std::stringstream::in | std::stringstream::out);
/*
>>>>>>> parent of 7bd50a5... magazine update for rapid fire mode
	ss << "KILLS: " << this->getkillcount();

	RenderText(ren, ss.str(), 10, 10);

	ss.str(std::string());

	ss << "FIRE MODE: " << fireMode;
	RenderText(ren, ss.str(), 10, 25);

	ss.str(std::string());
*/

	ss << "FIRE MODE: " << fireMode;
	RenderText(ren, ss.str(), 10, 10);

	/* Draw health bar */
	auto h = 15;
	auto x = 0;
	auto y = SCRH - h;

	/* Background */
	SDL_SetRenderDrawColor( ren.get(), 55, 55, 55, 255 );
	auto r = SDL_Rect{ x, y, this->maxplayerhealth, h };
	SDL_RenderFillRect(ren.get(), &r);
	SDL_SetRenderDrawColor( ren.get(), 0, 0, 0, 255 );

	/* Bar */
	SDL_SetRenderDrawColor( ren.get(), 255, 0, 0, 255 );
	r = { x + 5, y + 5, this->playerHealth - 5, h - 5};
	SDL_RenderFillRect(ren.get(), &r);
	SDL_SetRenderDrawColor( ren.get(), 0, 0, 0, 255 );
}

int UI::RenderText (std::shared_ptr< SDL_Renderer > ren, std::string text, int x, int y)
{

	auto font = std::shared_ptr< TTF_Font >(
		TTF_OpenFont("font.ttf", 12), 
		[](TTF_Font* font_){TTF_CloseFont(font_); });

	if (font.get() == NULL)
	{
		SDL_Log("Font is null: %s", SDL_GetError());
	}

	auto col = SDL_Color{ 255, 255, 255, 255 };

	auto surf = std::shared_ptr< SDL_Surface >(
		TTF_RenderText_Solid(font.get(), (const char*)text.c_str(), col),
		[](SDL_Surface* surf){SDL_FreeSurface(surf); });

	auto mytext = std::shared_ptr< SDL_Texture >(
		SDL_CreateTextureFromSurface(ren.get(), surf.get()),
		[](SDL_Texture* mytext){SDL_DestroyTexture(mytext); });

	auto w = 0, h = 0;

	SDL_QueryTexture(mytext.get(), NULL, NULL, &w, &h);

	auto r = SDL_Rect{ x, y, w, h };

	SDL_RenderCopy(ren.get(), mytext.get(), NULL, &r);;

	return 0;
}
