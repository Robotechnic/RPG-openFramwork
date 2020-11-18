#include "map.h"

Map::Map()
{

}

bool Map::loadMap(string map){
    filesystem::path mapPath(map);

    if(this->mapLoader.load(mapPath)){ //try to load the map
        //load the tile map
        this->mapLoader = this->mapLoader.getChild("map");
        if (!this->mapLoader){ //verify if map exist
            ofLogError()<<"Wrong xml format";
            return false;
        }
        //get width and height of the map
        this->height = this->mapLoader.getAttribute("width").getIntValue();
        this->width = this->mapLoader.getAttribute("height").getIntValue();
        //get the width and height of tiles
        this->tilesWidth = this->mapLoader.getAttribute("tilewidth").getIntValue();
        this->tilesHieght = this->mapLoader.getAttribute("tileheight").getIntValue();
        if (this->height == 0 || this->width == 0 || this->tilesWidth == 0 || this->tilesHieght == 0){
            ofLogError()<<"Wrong xml map atributes";
            return false;
        }


        //veriffy if the source of tileset is valid
        ofXml xmlTileSetReference = this->mapLoader.getChild("tileset");
        string tileSetPathString = xmlTileSetReference.getAttribute("source").getValue();
        if (tileSetPathString == ""){
            ofLogError()<<"Wrong xml tileset atributes";
            return false;
        }

        //verify if tile set description can be oppen
        //only one tile set supported for the moment
        //ofLogWarning()<<tileSetPathString.substr(3,tileSetPathString.size()-1);
        filesystem::path tileSetPath(tileSetPathString.substr(3,tileSetPathString.size()-1));
        if(this->tilesLoader.load(tileSetPath)){
            this->tilesLoader = this->tilesLoader.getChild("tileset");
            //getAttributes of tilset to verify informations
            this->columns = this->tilesLoader.getAttribute("columns").getIntValue();
            if (this->columns == 0){
                ofLogError()<<"Wrong xml attributes";
                return false;
            }

            if (this->tilesWidth != this->tilesLoader.getAttribute("tilewidth").getIntValue() ||
                this->tilesHieght != this->tilesLoader.getAttribute("tileheight").getIntValue()){
                ofLogError()<<"Wrong tiles width and height";
                return false;
            }

            this->tilesCount = this->tilesLoader.getAttribute("tilecount").getIntValue();
            if (this->tilesCount == 0){
                ofLogError()<<"Wrong xml tilescount atribute";
                return false;
            }

            ofXml tileSetImageSource = this->tilesLoader.getChild("image");
            if(!tileSetImageSource){
                ofLogError()<<"Wrong xml tileset format";
                return false;
            }

            //verify if path of tile exist
            string tilesetImagePath = tileSetImageSource.getAttribute("source").getValue();
            if (tilesetImagePath == ""){
                ofLogError()<<"Wrong xml tileset atributes";
                return false;
            }
            tilesetImagePath = tileSetPath.remove_filename().generic_string() + "/" + tilesetImagePath;


            //ofLogWarning()<<tilesetImagePath;

            //load image
            if (this->tileSetImage.load(tilesetImagePath)){
                if (this->tileSetImage.getWidth() == tileSetImageSource.getAttribute("width").getIntValue() ||
                        this->tileSetImage.getHeight() == tileSetImageSource.getAttribute("height").getIntValue()){
                    if(!this->createSpetialTileSetMap()){
                        return false;
                    }
                } else {
                    ofLogError()<<"Wrong image size";
                    return false;
                }

            } else {
                 ofLogError()<<"Wrong image path";
                 return false;
            }

            //get all layers of the map
            auto mapData = this->mapLoader.getChildren("layer");
            int id;
            for (ofXml layer : mapData){
                ofXml data = layer.getChild("data");
                if (data){
                    tiles.push_back(vector<vector<int*>>()); //add layer to tiles vector

                    if (data.getAttribute("encoding").getValue() == "csv") //verify if encoding is csv
                    {
                        //split data and store it in vector
                        string mapStringData = data.getValue();
                        mapStringData = mapStringData.substr(1,mapStringData.size()-2);
                        vector<string> mapLines = ofSplitString(mapStringData,"\n");
                        for (string linesTileString : mapLines){
                            vector <int*> tilesLines;
                            linesTileString = linesTileString.substr(0,linesTileString.size()-2);
                            vector <string> tilesColumn = ofSplitString(linesTileString,",");
                            for (string columnTile : tilesColumn){
                                id = ofToInt(columnTile);
                                if (this->spetialTiles.find(id) != this->spetialTiles.end()){
                                    tilesLines.push_back(&this->spetialTiles.at(id).at(0));
                                } else {
                                    if (this->tempStore.find(id) != this->tempStore.end()){
                                        tilesLines.push_back(this->tempStore.at(id));
                                    } else {
                                        int *tmp = new int(id);
                                        this->tempStore[id] = tmp;
                                        tilesLines.push_back(tmp);
                                    }
                                }
                            }
                            this->tiles.at(this->tiles.size()-1).push_back(tilesLines);
                        }
                    } else {
                        ofLogError()<<"Wrong data encoding";
                        return false;
                    }
                }
            }

            auto objectGroups  = this->mapLoader.getChildren("objectgroup");

            for (ofXml objectGroup : objectGroups){
                string name = objectGroup.getAttribute("name").getValue();
                if (name != ""){
                    for (ofXml object : objectGroup.getChildren("object")) {
                        string objName = object.getAttribute("name").getValue();
                        if (name == "startStopPoint"){
                        if (objName != ""){

                            if (objName == "spawn"){
                                float spawnX = object.getAttribute("x").getFloatValue();
                                float spawnY = object.getAttribute("y").getFloatValue();

                                if (!spawnX || !spawnY){
                                    ofLogError()<<"Wrong xml atribute (spawn coordinates)";
                                    return false;
                                }
                                this->spawn.x = spawnX-400;
                                this->spawn.y = spawnY-200;
                            } else if (name == "end"){
                                float endX = object.getAttribute("x").getFloatValue();
                                float endY = object.getAttribute("y").getFloatValue();
                                float width = object.getAttribute("width").getFloatValue();
                                float height = object.getAttribute("height").getFloatValue();

                                if (!endX || !endY || !width || !height){
                                    ofLogError()<<"Wrong xml atribute (end coordinates)";
                                    return false;
                                }
                                this->end.x = endX-400;
                                this->end.y = endY-200;
                                this->end.width = width;
                                this->end.height = height;
                            }}}
                            else if (name == "death"){
                                float polyX = object.getAttribute("x").getFloatValue();
                                float polyY = object.getAttribute("y").getFloatValue();

                                if (!polyX || !polyY){
                                    ofLogError()<<"Wrong xml atribute (x,y of polygon)";
                                    return false;
                                }

                                ofXml polygon = object.getChild("polygon");
                                if (!polygon){
                                    ofLogError()<<"Polygon don't exist";
                                    return false;
                                }
                                string points = polygon.getAttribute("points").getValue();
                                if (points == ""){
                                    ofLogError()<<"Wrong xml atribute (points)";
                                    return false;
                                }

                                vector<string> pos = ofSplitString(points, " ");
                                Zone z ({});
                                for (string p : pos){
                                    vector<string> relativePos = ofSplitString(p,",");
                                    float x = ofToFloat(relativePos.at(0)) + polyX ;
                                    float y = ofToFloat(relativePos.at(1)) + polyY ;

                                    z.addPoint(ofVec2f(x,y));
                                }
                                this->deathZones.push_back(z);
                            }
                        else {
                            ofLogError()<<"Wrong xml data (object name)";
                            return false;
                        }
                    }
                } else {
                    ofLogError()<<"Wrong xml data (objectgroup name)";
                    return false;
                }
            }
            //everithing loaded !
            return true;

        } else {
            ofLogError()<<"Tileset does not exist";
        }
    }
    else{
        ofLogError()<<"Map does not exist";
    }
    return false;
}

ofVec2f Map::idToPosition(int id){
    ofVec2f pos;
    pos.y = floor(id/this->columns)*this->tilesHieght;
    pos.x = ((id-1)%this->columns)*this->tilesWidth;
    return pos;
}

bool Map::createSpetialTileSetMap(){
    //first get tiles
    auto tiles = this->tilesLoader.getChildren("tile");
    //lad all tiles in map tileSet
    for (ofXml tileDescriptor : tiles){
        if (tileDescriptor.getChild("animation")){ // if tile have annimation
            int id = tileDescriptor.getAttribute("id").getIntValue();

            vector<int> framesVec;
            framesVec.push_back(id); //curent tile
            framesVec.push_back(4); //current index
            framesVec.push_back(ofGetElapsedTimeMillis()); //last update
            framesVec.push_back(500); //delay between all tiles

            for (ofXml frame : tileDescriptor.getChild("animation").getChildren("frame")){
                int tileId = frame.getAttribute("tileid").getIntValue();
                int durration = frame.getAttribute("duration").getIntValue();
                if (tileId == 0 || durration == 0){
                    ofLogError()<<"Wrong frame xml attributes";
                    return false;
                }
                framesVec.push_back(tileId);
            }


            this->spetialTiles.insert(make_pair(id,framesVec));
        }

    }
    return true;
}


void Map::draw(int x, int y, int width, int height){

    int xMin = (x/this->tilesWidth);
    xMin = xMin<0 ? 0 : xMin;
    int yMin = (y/this->tilesHieght);
    yMin = yMin<0 ? 0 : yMin;
    int xMax = (width/this->tilesWidth)+1;
    xMax = xMax>this->width ? this->width : xMax;
    int yMax = (height/this->tilesHieght)+1;
    yMax = yMax>this->height ? this->height : yMax;


    //draw layer by layers
   // cout<<"draw "<<ofGetElapsedTimeMillis()<<endl;
    ofVec2f pos;
    this->tileSetImage.bind();
    for (vector<vector<int*>> layer : this->tiles)
    {
        ofVboMesh mesh;
        for (int yV = yMin; yV<yMax && yV<(int)layer.size(); yV++)
            for (int xV = xMin; xV < xMax && xV<(int)layer.at(yV).size(); ++xV) {
                if (layer.at(yV).at(xV) != 0){
                    pos = this->idToPosition(*layer.at(yV).at(xV));
                    mesh.addVertex({xV*this->tilesWidth,yV*this->tilesWidth,0});
                    mesh.addVertex({xV*this->tilesWidth+this->tilesWidth,yV*this->tilesWidth,0});
                    mesh.addVertex({xV*this->tilesWidth+this->tilesWidth,yV*this->tilesHieght+this->tilesHieght,0});

                    mesh.addVertex({xV*this->tilesWidth,yV*this->tilesWidth,0});
                    mesh.addVertex({xV*this->tilesWidth+this->tilesWidth,yV*this->tilesHieght+this->tilesHieght,0});
                    mesh.addVertex({xV*this->tilesWidth,yV*this->tilesWidth+this->tilesHieght,0});

                    mesh.addTexCoord({pos.x,pos.y});
                    mesh.addTexCoord({pos.x+this->tilesWidth,pos.y});
                    mesh.addTexCoord({pos.x+this->tilesWidth,pos.y+this->tilesHieght});

                    mesh.addTexCoord({pos.x,pos.y});
                    mesh.addTexCoord({pos.x+this->tilesWidth,pos.y+this->tilesHieght});
                    mesh.addTexCoord({pos.x,pos.y+this->tilesHieght});

                }
            }

        mesh.draw();
    }
    this->tileSetImage.unbind();
    //cout<<"end "<<ofGetElapsedTimeMillis()<<" Total Tiles:"<<(xMax-xMin)*(yMax-yMin)<<endl;
}

void Map::updateAnimation(){
    for (auto &tile : this->spetialTiles){
        int frame = tile.second.at(1);
        int &last = tile.second.at(2);
        int delay = tile.second.at(3);
        if (last + delay < (int)ofGetElapsedTimeMillis()){
            last = ofGetElapsedTimeMillis();
            frame = frame<(int)tile.second.size()-1 ? frame + 1 : 4;
            tile.second.at(0) = tile.second.at(frame);
            tile.second.at(1) = frame;
        }
    }
}

bool Map::calcDeath(int x, int y){
    for (Zone z : this->deathZones){
        if (z.inZone(ofVec2f(x,y))){
            return true;
        }
    }
    return false;
}
