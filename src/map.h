#ifndef MAP_H
#define MAP_H

#include <ofImage.h>
#include <ofXml.h>

#include <ofGraphics.h>
#include <ofVec2f.h>

#include <string>
#include <map>


using namespace std;


class Map
{
public:
    Map();
    bool loadMap(string map);
    void draw(int x, int y,int width, int height);
    void updateAnimation();
    ofVec2f idToPosition(int id);

private:
    ofImage tileSetImage;

    int width, height,tilesWidth,tilesHieght,columns,tileSetImageWidth,tilesetImageHeight,tilesCount;

    bool createSpetialTileSetMap();

    //tile id
        //id of each frame
    map <int, vector<int>> spetialTiles;
    map <int, int*> tempStore;
    //layers
        //tileSet
            //tiles
    vector<vector<vector<int*>>> tiles;

    ofXml mapLoader,tilesLoader;

};

#endif // MAP_H
