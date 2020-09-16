#include "tile.h"

Tile::Tile(){
    this->tileId = -1;
    this->tileFrames.push_back(glm::vec2(0,0));
    this->annimationTime = 0;
    this->annimFrame = 0;
}


Tile::Tile(int tileId, vector<glm::vec2> tileFrames){
    this->tileId = tileId;
    this->tileFrames = tileFrames;
    this->annimationTime = 0;
    this->annimFrame = 0;
}
Tile::Tile(const Tile &t){
    this->tileId = t.tileId;
    this->tileFrames = t.tileFrames;
    this->annimationTime = 0;
    this->annimFrame = t.annimFrame;
}
void Tile::update(){
    if (this->annimationTime+this->tileFrames.at(annimFrame).y<(int)ofGetElapsedTimeMillis()){
        this->annimationTime = ofGetElapsedTimeMillis();
        this->annimFrame = this->annimFrame<(int)this->tileFrames.size()-1 ?
                           this->annimFrame + 1 : 0;
    }
}

int Tile::getFrame(){
    this->update();
    return this->tileFrames.at(annimFrame).x;
}
int Tile::getDelay(){
    this->update();
    return this->tileFrames.at(annimFrame).y;
}

int Tile::getTileId(){
    return this->tileId;
}
