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
    Tile(int tileId, vector<glm::vec2> tileFrames); //tile with annimation (multiples frames)
    Tile(const Tile& t);

    void update();

    int getFrame();
    int getDelay();
    int getTileId();

private:
    int annimationTime;
    int tileId;
    int annimFrame;
    vector<glm::vec2> tileFrames;
};

#endif // TILE_H
