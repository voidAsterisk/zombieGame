#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "UI.h"


class Player : public Sprite {
private:
	const int maxHealth = 300;
	int timeSinceLastHit = 0;

public:
	void Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime) override;
	
	Player(Sprite* templatesprite);
	Player(std::string filename, SDL_Renderer* ren);

};

#endif


