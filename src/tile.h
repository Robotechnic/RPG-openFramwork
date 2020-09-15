#ifndef TILE_H
#define TILE_H

#include <ofTimer.h>
#include <glm/vec2.hpp>

#include <vector>

using namespace std;

class Tile
{
public:
    Tile();
    Tile(int tileId); //tile wihout annimation
    Tile(int tileId, int delay, vector<int> tileFrames); //tile with annimation (multiples frames
    Tile(const Tile& t);

    void update();

    int getX();
    int getY();
    int getTileId();

private:
    bool hasAnimation;
    int annimationTime;
    int tileId;
    int delay;
    int annimFrame;
    vector<int> tileFrames;
};

#endif // TILE_H
