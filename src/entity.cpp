#include "entity.h"


entity::entity(int x, int y, string spriteUrl, string name, bool displayName, int maxLife)
{
    this->x = x;
    this->y = y;
    this->displayName = displayName;
    this->maxLife = maxLife;
    this->life = maxLife;

    //sprite
    this->spriteUrl = spriteUrl;
    this->imageSprite.load(spriteUrl);
    this->name = name;

    //default animation state
    this->annimState = 1;
    this->annimDirection = 0;
    this->annimStateDirection = 0;
    this->annimTime = ofGetElapsedTimeMillis();
}

entity::entity(const entity &e){
    this->x = e.x;
    this->y = e.y;
}

void entity::draw(ofTrueTypeFont playerFonFace){
    //debug x y pos
//    ofSetColor(255,0,0);
//    ofDrawCircle(this->x, this->y, 1);

    //get annimation state and reset if necesary
    if (this->annimTime + MAX_ANNIM_TIME < (int)ofGetElapsedTimeMillis()){
        this->annimState = DEFAULT_ANNIM_STATE;
    }

    //get width of name
    ofRectangle box = playerFonFace.getStringBoundingBox(this->name,this->x,this->y);

    //draw player
    ofSetColor(255);
    if (displayName)
        playerFonFace.drawString(this->name,this->x-(box.width-SPRITE_SIZE)/2,this->y-box.height/2);
    this->imageSprite.drawSubsection(this->x,this->y,SPRITE_SIZE,SPRITE_SIZE,(annimState)*SPRITE_SIZE,(annimDirection)*SPRITE_SIZE);
}

//direction constants
const direction entity::UP = 3;
const direction entity::DOWN = 0;
const direction entity::LEFT = 1;
const direction entity::RIGHT = 2;

void entity::move(direction entityDirection){
    this->annimDirection = entityDirection;

    //play animation every ANNIM_DELAY milliseconds
    if (this->annimTime+ANNIM_DELAY<(int)ofGetElapsedTimeMillis()){
        this->annimTime = ofGetElapsedTimeMillis();
        if (annimStateDirection == 0){
            this->annimState ++;
            if (this->annimState >= 2){
                this->annimStateDirection = 1;
            }
        } else {
            this->annimState --;
            if (this->annimState <= 0){
                this->annimStateDirection = 0;
            }
        }
        //debug
        cout<<this->annimTime<<" "<<this->annimState<<" "<<this->annimStateDirection<<endl;
    }

    //change entity coordinates
    switch (entityDirection){
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case RIGHT:
            x++;
            break;
        case LEFT:
            x--;
            break;
    }
}
