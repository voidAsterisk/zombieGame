#include "bullet.h"

void Bullet::Update(UI* ui, std::vector<Sprite*>* entlist, double deltaTime,
		std::vector<Sprite*>* spawnList, std::map<std::string, Sprite*>*sprites)
{
	Sprite::Update(ui, entlist, deltaTime, spawnList, sprites);
	locationVec = locationVec + velocityVec * deltaTime;

	for (std::vector<Sprite*>::iterator it = entlist->begin(); it != entlist->end(); it++)
	{

		if (strcmp((*it)->name.c_str(), "zombie") == 0)
		{
			SDL_Rect r;
			r = this->GetRect();

			SDL_Rect r2;
			r2 =(*it)->GetRect();

			bool intersect = SDL_HasIntersection( &r, &r2 );

			if (intersect)
			{			
				if ((*it)->healthPoints > 0)
				{
					this->destroyed = true;
				}
				(*it)->healthPoints -= 1;
				break;
			}
		}
	}
}


void Bullet::Render(SDL_Renderer* ren)
{
	SDL_Rect r = { (int)this->locationVec.x, (int)this->locationVec.y,
		(int)this->w * (int)this->scale, (int)this->h  * (int)this->scale};
	SDL_RenderCopyEx(ren, this->texture, &src, &r, angle, NULL, SDL_FLIP_NONE);
}

Bullet::Bullet(Sprite* templatesprite, Vector location, Vector direction): Sprite(templatesprite)  
{
	this->locationVec.x = location.x;
	this->locationVec.y = location.y;
	this->directionVec = direction;

	angle = directionVec.angle();

	directionVec.normalize();
	maxVelocity = 59;
	directionVec *= maxVelocity;
	accelerationVec = directionVec;

	velocityVec = velocityVec + accelerationVec;
	velocityVec.limit(maxVelocity);

	this->scale = 1;
	this->persistent = false;
	
}

Bullet::Bullet(std::string filename, SDL_Renderer* ren): Sprite(filename, ren)
{

}

