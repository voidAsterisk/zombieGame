#ifndef SPRITE_H
#define SPRITE_H


#include <SDL.h>
#include <SDL_ttf.h>


#include <string>
#include <vector>
#include <map>
#include <memory>

#include "vector.h"
#include "UI.h"

class Sprite {

protected:
	virtual void setDirection(Vector direction);// virtual because zombie is lacking textures and using the
	//full aglo will make the zombies dissapear under certain conditions so zombie has an override to 
	//setDirection(Vector direction)

public:
	SDL_Texture* texture;
	Vector locationVec;
	double w = 1;
	double h = 1;
	int plane; // 0 - bg, 1 - items, 2 - ui 
	double velocity;

	Vector velocityVec;
	Vector accelerationVec;
	Vector directionVec;
	float maxVelocity;

	bool destroyed;

	int healthPoints;
	int maxHealth;

	std::string name;

	int rows = 1;
	int cols = 1;
	int scale = 2;
	int framewidth;
	int frameheight;
	double framecount = 0;
	unsigned char direction = 0;
	bool persistent = true;
	SDL_Rect src;

	void AnimateStep(int direction, double deltaTime);
	void FreezeStep(int direction);

	SDL_Rect GetRect();

	virtual void Render(std::shared_ptr< SDL_Renderer > ren);
	virtual void Render(std::shared_ptr< SDL_Renderer > ren, Vector offset);

	virtual void Update(double deltaTime, std::shared_ptr<UI> ui,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > entlist,
		std::shared_ptr< std::vector< std::shared_ptr< Sprite > > > spawnlist,
		std::shared_ptr< std::map < std::string, std::shared_ptr< Sprite > > > sprites);


	Sprite(std::shared_ptr< Sprite > templatesprite);
	Sprite(std::string filename, std::shared_ptr< SDL_Renderer > ren);

};

#endif

