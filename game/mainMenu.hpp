#ifndef MAINMENU_HPP
#define MAINMENU_HPP

class MainMenu
{
public:
	MainMenu(Renderer* _renderer, SDL_Event* _e, GameState* _state, Settings* _settings, Audio* _audio)
	{
		renderer = _renderer;
		e = _e;
		state = _state;
		settings = _settings;
		audio = _audio;
		currentMenuButton = newGameButton;
		textScale = 5;
		topRightX = 100;
		topRightY = 100;
		waittime = 1000 / settings->getFPS();
		framestarttime = 0;
		
//vareetu ielikt ciklaa lai buutu smukaak bet izveerts ir performance boost un jau viss ir uzrakstiits :D
		newGameRect.x = topRightX; 
		newGameRect.y = topRightY + textScale * renderer->ascii.source.h * 0;
		newGameRect.h = textScale * renderer->ascii.source.h;
		newGameRect.w = textScale * renderer->ascii.source.w * strlen(newGameText);

		settingsRect.x = topRightX;
		settingsRect.y = topRightY + textScale * renderer->ascii.source.h * 1;
		settingsRect.h = textScale * renderer->ascii.source.h;
		settingsRect.w = textScale * renderer->ascii.source.w * strlen(settingsText);

		highscoreRect.x = topRightX;
		highscoreRect.y = topRightY + textScale * renderer->ascii.source.h * 2;
		highscoreRect.h = textScale * renderer->ascii.source.h;
		highscoreRect.w = textScale * renderer->ascii.source.w * strlen(highscoreText);

		quitRect.x = topRightX;
		quitRect.y = topRightY + textScale * renderer->ascii.source.h * 3;
		quitRect.h = textScale * renderer->ascii.source.h;
		quitRect.w = textScale * renderer->ascii.source.w * strlen(quitText);
	}

	~MainMenu()
	{

	}

private:
	int textScale;
	int topRightX;
	int topRightY;
	
	Renderer* renderer;
	SDL_Event* e;
	GameState* state;
	Settings* settings;
	Audio* audio;

	Uint32 waittime;
	Uint32 framestarttime;
	Sint32 delaytime;

	SDL_Rect newGameRect;
	SDL_Rect settingsRect;
	SDL_Rect highscoreRect;
	SDL_Rect quitRect;

	const char* newGameText =	" New Game ";
	const char* settingsText =	" Settings ";
	const char* highscoreText = "Highscores";
	const char* quitText =		"   Quit   ";

	SDL_Point mouse_position;

	SDL_Rect destination;
	
	typedef enum
	{
		newGameButton,
		settingsButton,
		highscoresButton,
		quitButton
	} CurrentMenuButton;

	CurrentMenuButton currentMenuButton;

public:
	void drawMenu()
	{		
		renderer->clear();

		destination.x = topRightX - renderer->ascii.source.w * textScale;
		destination.y = topRightY + currentMenuButton * renderer->ascii.source.h * textScale;
		renderer->drawText(">", &destination, textScale);

		destination.x = topRightX;
		destination.y = topRightY;
		renderer->drawText(newGameText, &destination, textScale);
		renderer->drawText(settingsText, &destination, textScale);
		renderer->drawText(highscoreText, &destination, textScale);
		renderer->drawText(quitText, &destination, textScale);

		renderer->present();
	}

	void userInput()
	{
		while (SDL_PollEvent(e))
		{
			switch (e->type)
			{
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
				if (pointInRect(&mouse_position, &newGameRect) == true)
				{
					currentMenuButton = newGameButton;
				}
					else if (pointInRect(&mouse_position, &settingsRect) == true)
					{
						currentMenuButton = settingsButton;
					}
						else if (pointInRect(&mouse_position, &highscoreRect) == true)
						{
							currentMenuButton = highscoresButton;
						}
							else if (pointInRect(&mouse_position, &quitRect) == true)
							{
								currentMenuButton = quitButton;
							}
				break;
			case SDL_QUIT:
				*state = quitState;
				break;
			case SDL_KEYDOWN:
				if (e->key.keysym.sym == SDLK_RETURN && currentMenuButton == quitButton)
				{
					*state = quitState;
					break;
				}
				if (e->key.keysym.sym == SDLK_UP)
				{
					if (currentMenuButton != newGameButton)
					{
						currentMenuButton = (CurrentMenuButton)((int)currentMenuButton - 1);
						break;
					}
					else
					{
						currentMenuButton = (CurrentMenuButton)3;
						break;
					}
				}
				if (e->key.keysym.sym == SDLK_DOWN)
				{
					if (currentMenuButton != quitButton)
					{
						currentMenuButton = (CurrentMenuButton)((int)currentMenuButton + 1);
						break;
					}
					else
					{
						currentMenuButton = (CurrentMenuButton)0;
						break;
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				//if (e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &newGameRect))
				//{
				//	*state = gameplayState;
				//break;
				//}
				//if (e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &settingsRect))
				//{
				//	*state = settingsState;
				//break;
				//}
				//if (e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &highscoreRect))
				//{
				//	*state = highscoreState;
				//break;
				//}
				if (e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &quitRect))
				{
					*state = quitState;
					break;
				}
				break;


			default: continue;
			}
		}
	}

	void updateMainMenu()
	{
		this->userInput();
		this->drawMenu();

		audio->play(settings->getVolume(), 50);

		delaytime = waittime - (SDL_GetTicks() - framestarttime);
		if (delaytime > 0)
			SDL_Delay((Uint32)delaytime);
		framestarttime = SDL_GetTicks();
	}
};

#endif