#ifndef Tile_H
#define Tile_H

#include <SDL.h>
#include "sprite.h"
#include "UI.h"

class Tile: public Sprite {

private:

public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites) override;
	void Render(SDL_Renderer* ren) override;
	SDL_Rect GetRect() override;	
	Tile(Sprite* templatesprite) ;
	Tile(std::string filename, SDL_Renderer* ren);
};

#endif
