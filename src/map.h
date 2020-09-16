#ifndef MAP_H
#define MAP_H

#include <ofImage.h>
#include <ofXml.h>

#include <ofGraphics.h>

#include <string>
#include <map>

#include "tile.h"

using namespace std;


class Map
{
public:
    Map();
    bool loadMap(string map);
    void draw(int x, int y,int width, int height);

private:
    ofImage tileSetImage;

    int width, height,tilesWidth,tilesHieght,columns,tileSetImageWidth,tilesetImageHeight;

    bool createTileSetMap();

    map <int, Tile> annimTileSet;
    //layers
        //tileSet
            //tiles
    vector<vector<vector<int>>> tiles;

    ofXml mapLoader,tilesLoader;

};

#endif // MAP_H
