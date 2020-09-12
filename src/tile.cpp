#include "tile.h"

Tile::Tile(){
    this->tileId = 0;
    this->hasAnimation = false;
    this->tileFrames.push_back(ofPoint(0,0));
    this->annimationTime = 0;
    this->delay = 0;
    this->annimFrame = 0;
}

Tile::Tile(int tileId, int tileSetX, int tileSetY){
    this->tileId = tileId;
    this->hasAnimation = false;
    this->tileFrames.push_back(ofPoint(tileSetX,tileSetY));
    this->annimationTime = 0;
    this->delay = 0;
    this->annimFrame = 0;
}
Tile::Tile(int tileId, int delay, vector<ofPoint> tileFrames){
    this->tileId = tileId;
    this->hasAnimation = true;
    this->tileFrames = tileFrames;
    this->annimationTime = 0;
    this->delay = delay;
    this->annimFrame = 0;
}
Tile::Tile(const Tile &t){
    this->hasAnimation = t.hasAnimation;
    this->tileId = t.tileId;
    this->tileFrames = t.tileFrames;
    this->annimationTime = 0;
    this->delay = t.delay;
    this->annimFrame = t.annimFrame;
}
void Tile::update(){
    if (this->hasAnimation){
        if (this->annimationTime+this->delay<(int)ofGetElapsedTimeMillis()){
            this->annimFrame = this->annimFrame<(int)this->tileFrames.size() ?
                               this->annimFrame + 1 : 0;
        }
    }
}

int Tile::getX(){
    return this->tileFrames.at(annimFrame).x;
}
int Tile::getY(){
    return this->tileFrames.at(annimFrame).y;
}
