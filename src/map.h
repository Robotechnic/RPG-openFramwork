#ifndef MAP_H
#define MAP_H

#include <ofImage.h>
#include <ofXml.h>

#include <ofGraphics.h>
#include <ofVec2f.h>
#include <ofRectangle.h>
#include <ofVboMesh.h>

#include <string>
#include <map>

#include "zone.h"


using namespace std;


class Map
{
public:
    Map();
    bool loadMap(string map);
    void draw(int x, int y,int width, int height);
    void updateAnimation();
    bool calcDeath(int x, int y);
    ofVec2f idToPosition(int id);

    ofVec2f getSpawn(){return this->spawn;};

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

    ofVec2f spawn;
    ofRectangle end;
    vector <Zone> deathZones;

    ofXml mapLoader,tilesLoader;

};

#endif // MAP_H
