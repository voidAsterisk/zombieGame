#ifndef MAINMENU_HPP
#define MAINMENU_HPP



class MainMenu
{
public:
	MainMenu(Engine* _engine)
	{
		engine = _engine;//a pointer to engine is required to use the rendering, audio and setting functions
		currentMenuButton = newGameButton;
		textScale = 5;//the characters are 10x10 pixels by default, this is the amount they are scaled by
		topRightX = 100;//the top right coordinates of the main menu text
		topRightY = 100;
		waittime = 1000 / engine->settings->getFPS();//1000/fps would be the ms that one frame should take to do its logic and render if it does this faster the remaining time is delayed using SDL_Delay
		framestarttime = 0;
		
		engine->renderer->findTextureInVector(ASCII);//used so that the texture iterator is currently pointing to the ascii tileset
		
		//i have not tested it but the drawing of the text on the main menu should work with any tileset it "should" take minimal changes to the code
		//this assigns rectangles so that hovering the mouse over the text would select the button as if you were using your keyboard
		newGameRect.x = topRightX; 
		newGameRect.y = topRightY;//the next line is the the reason for using findTextureInVector(ASCII) is used to get the parameters of the ascii tileset
		newGameRect.h = textScale * (*engine->renderer->iterator)->source.h;
		newGameRect.w = textScale * (*engine->renderer->iterator)->source.w * strlen(newGameText);

		settingsRect.x = topRightX;
		settingsRect.y = topRightY + textScale * (*engine->renderer->iterator)->source.h * 1;
		settingsRect.h = textScale * (*engine->renderer->iterator)->source.h;
		settingsRect.w = textScale * (*engine->renderer->iterator)->source.w * strlen(settingsText);

		highscoreRect.x = topRightX;
		highscoreRect.y = topRightY + textScale * (*engine->renderer->iterator)->source.h * 2;
		highscoreRect.h = textScale * (*engine->renderer->iterator)->source.h;
		highscoreRect.w = textScale * (*engine->renderer->iterator)->source.w * strlen(highscoreText);

		quitRect.x = topRightX;
		quitRect.y = topRightY + textScale * (*engine->renderer->iterator)->source.h * 3;
		quitRect.h = textScale * (*engine->renderer->iterator)->source.h;
		quitRect.w = textScale * (*engine->renderer->iterator)->source.w * strlen(quitText);

		//the full size of the main menu text
		fullRect.x = topRightX;
		fullRect.y = topRightY;
		fullRect.h = textScale * (*engine->renderer->iterator)->source.h * 4;
		fullRect.w = textScale * (*engine->renderer->iterator)->source.w * strlen(quitText);
	}

	~MainMenu()
	{

	}

private:
	int textScale;
	int topRightX;
	int topRightY;
	
	Engine* engine;

	Uint32 waittime;
	Uint32 framestarttime;
	Sint32 delaytime;

	SDL_Rect fullRect;

	SDL_Rect newGameRect;
	SDL_Rect settingsRect;
	SDL_Rect highscoreRect;
	SDL_Rect quitRect;

	const char* newGameText =	" New Game ";
	const char* settingsText =	" Settings ";
	const char* highscoreText = "Highscores";
	const char* quitText =		"   Quit   ";

	SDL_Point mouse_position;//mouse position represented as its x and y coordinates

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
	inline void drawMenu()
	{		
		engine->renderer->clear();
		
		//draws the ">" so the user know which button is currently selected
		destination.x = topRightX - (*engine->renderer->iterator)->source.w * textScale;
		destination.y = topRightY + currentMenuButton * (*engine->renderer->iterator)->source.h * textScale;
		engine->renderer->drawText(">", &destination, textScale);

		//draws the menu text, this could be premade in a surface and coverted to a single texture but it is a non-issue right now, this sort of optimization will be used for the map when gameplay starts
		destination.x = topRightX;
		destination.y = topRightY;
		engine->renderer->drawText(newGameText, &destination, textScale);
		engine->renderer->drawText(settingsText, &destination, textScale);
		engine->renderer->drawText(highscoreText, &destination, textScale);
		engine->renderer->drawText(quitText, &destination, textScale);

		engine->renderer->present();
	}

	inline void userInput()
	{
		while (SDL_PollEvent(engine->e))//cycles through all the events in the event buffer
		{
			switch (engine->e->type)
			{
			case SDL_MOUSEMOTION:
				SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
				if (pointInRect(&mouse_position, &fullRect))//first checks if the mouse pointer is on any of the four buttons
				{
					if (pointInRect(&mouse_position, &newGameRect))
					{
						currentMenuButton = newGameButton;
					}
						else if (pointInRect(&mouse_position, &settingsRect))
						{
							currentMenuButton = settingsButton;
						}
							else if (pointInRect(&mouse_position, &highscoreRect))
							{
								currentMenuButton = highscoresButton;
							}
								else if (pointInRect(&mouse_position, &quitRect))
								{
									currentMenuButton = quitButton;
								}
				}
				break;
			case SDL_QUIT:
				*engine->state = quitState;
				break;
			case SDL_KEYDOWN:
				if (engine->e->key.keysym.sym == SDLK_RETURN && currentMenuButton == quitButton)
				{
					*engine->state = quitState;
					break;
				}
				if (engine->e->key.keysym.sym == SDLK_UP)
				{
					if (currentMenuButton != newGameButton)
					{//using casting we can go through the 4 button states
						currentMenuButton = (CurrentMenuButton)((int)currentMenuButton - 1);
						break;
					}
					else
					{
						currentMenuButton = (CurrentMenuButton)3;
						break;
					}
				}
				if (engine->e->key.keysym.sym == SDLK_DOWN)
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
				if (pointInRect(&mouse_position, &fullRect))//first checks if the mouse pointer is on any of the four buttons
				{
					if (engine->e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &newGameRect))
					{
						*engine->state = gameplayState;
					}
					else /*if (engine->e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &settingsRect))
					//not currently used since both settings and highscores are not implemented
					{
						*engine->state = settingsState;
					}
					else if (engine->e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &highscoreRect))
					{
						*engine->state = highscoreState;
					}
					else*/ if (engine->e->button.button == SDL_BUTTON_LEFT && pointInRect(&mouse_position, &quitRect))
					{
						*engine->state = quitState;
						break;
					}
				}
				break;
			default: continue;
			}
		}
	}

	inline void updateMainMenu()
	{
		this->userInput();
		this->drawMenu();

		engine->audio->play(engine->settings->getVolume(), 50);//currently only plays one soundtrack on a loop

		delaytime = waittime - (SDL_GetTicks() - framestarttime);//this is semi redundant because of vsync
		if (delaytime > 0)
			SDL_Delay((Uint32)delaytime);
		framestarttime = SDL_GetTicks();
	}
};

#endif