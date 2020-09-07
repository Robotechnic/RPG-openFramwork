#include "entity.h"

entity::entity(int x, int y, string spriteUrl,string name)
{
    this->x = x;
    this->y = y;
    this->spriteUrl = spriteUrl;
    this->imageSprite.load(spriteUrl);
    this->name = name;

}

entity::entity(const entity &entity){
    this->x = entity.x;
    this->y = entity.y;
}

void entity::draw(ofTrueTypeFont playerFonFace){
    playerFonFace.drawString(this->name,this->x,this->y-64-playerFonFace.getSize());

    this->imageSprite.drawSubsection(this->x,this->y,64,64,0,0);
}
