#ifndef TILE_H
#define TILE_H

#include <ofTimer.h>
#include <ofPoint.h>

#include <vector>

using namespace std;

class Tile
{
public:
    Tile();
    Tile(int tileId,int tileSetX,int tileSetY); //tile wihout annimation
    Tile(int tileId, int delay, vector<ofPoint> tileFrames); //tile with annimation (multiples frames
    Tile(const Tile& t);

    void update();

    int getX();
    int getY();

private:
    bool hasAnimation;
    int annimationTime;
    int tileId;
    int delay;
    int annimFrame;
    vector<ofPoint> tileFrames;
};

#endif // TILE_H
